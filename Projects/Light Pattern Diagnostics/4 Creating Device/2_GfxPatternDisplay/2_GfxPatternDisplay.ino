#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define sensor A2
#define LedLightDetect 12
#define LedProcessing 11


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define patternSize 60   // number of brightness readings recorded before analysis starts

int threshold = 90;       // anything *above* this value will be considered BRIGHT
// the range is 0-99, so by specifyinng 99, you only accept
// 100% brightness. Note that a value of 100 would never be reached
// because 100 is the max possible value, and it can never be
// greater than 100.
long  minInterval = 3;  // minimum length of a pattern interval in millisec
// this is a safety measure for inconsistencies. Only when a pattern change
// occurs that is at minimum of minInterval length will this be considered
// a true pattern change
byte patternIndex = 0;      // current pattern element

bool active = false;      // sensor has received bright light
bool isBright = false;    // when true, the sensor input is greater than threshold so there is strong light shining on it
long  currentClock = 0;   // the milliseconds recorded at last pattern change
long  duration = 0;       // duration of last pattern
bool isInit = true;       // true when no OPT101 results have been taken yet


void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(F("READY."));

  display.setTextSize(1);

  display.setCursor(0, 30);
  display.println(F("Point detector to"));
  display.setCursor(0, 38);
  display.println(F("light source."));


  display.display();


  // set up serial monitor baud rate
  // make sure this matches the settings in your serial monitor:
  Serial.begin(115200);

  // define analog in pin receiving the OPT101 brightness readings:
  pinMode (sensor, INPUT);

  // pin to control detected light
  // lights up when OPT101 detected a ON phase
  pinMode(LedLightDetect, OUTPUT);
  pinMode(LedProcessing, OUTPUT);

  digitalWrite(LedProcessing, LOW);
  digitalWrite(LedLightDetect, LOW);

  // set the variable to the current millisecond count
  // we measure duration from here, so anything that occurs in the future will be the
  // time in milliseonds measured from this point in time
  currentClock = millis();

}

void loop() {

  // array storing the readings
  // this array must be defined within the loop() or else there will be scoping issues
  int pattern[patternSize];

  // read current brightness:
  int value = analogRead(sensor);
  // the sensor returns values up to 4,22V
  // the analog input translates these to a value between 0 and 1023
  // for our purposes, we take the realistic input range of 10-863
  // and map these to values between 0-100 (dark to light)
  value = map(value, 10, 863, 0, 100);

  // determine whether we currently detect a "dark" or "light" moment:
  isBright = value > threshold;

  // do we have a status change (dark to light or vice versa)?
  if (isBright != active)
  {
    // how many millisecs did the last period take?
    // we have a pattern change
    duration = millis() - currentClock;

    // is the current interval long enough to be valid?
    // intervals shorter than minInterval are most likely artifacts
    if (duration > minInterval)
    {
      currentClock = millis();             // reset the clock
      active = isBright;                   // reset the current mode

      // mark "dark" phases by negating the value
      if (!isBright) {
        digitalWrite(LedLightDetect, LOW);
        duration = duration * -1.0;
      }
      else
      {
        digitalWrite(LedLightDetect, HIGH);
      }

      // store current reading in array:
      pattern[patternIndex] = duration;
      patternIndex++;

      // clear display. This can take 40ms so it may interfere with measuring
      // that's why currentclock must be updated before. Then we won't get
      // mismatches at least if the current pattern is >40ms.
      if (isInit)
      {
        isInit = false;
        long before = millis();
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.println(F("MEASURING"));
        display.display();
        long dur = millis() - before;
      }
    }
  }

  // is the recording done and all (patternSize) raw values have been recorded to the array?
  if (patternIndex > patternSize)
  {
    
    digitalWrite(LedProcessing, HIGH);
    digitalWrite(LedLightDetect, LOW);

    // search pattern lengths
    // we assume pattern intervals between 2 and 20
    // a pattern of 2 would be a simple ON-OFF-ON-OFF
    // a pattern of 20 would consist of 14 other states before the original state re-occurs
    int maxPattern = 20;
    int matchPattern = -1;

    // omit the first two readings, then loop through all potential pattern sizes possible:
    for (int offset = 3; offset <= maxPattern; offset++)
    {
      // calculate the last index at which we can still do a full pattern check
      // so this is the length of the array - the current offset - 2
      int lastElement = patternSize - offset - 2;

      // assume the current pattern is valid until proven otherwise:
      bool found = true;

      // again, omit the first two readings
      // check each starting position in the array
      for (int i = 2; i < lastElement; i++)
      {
        // the corresponding value in the next pattern cycle is "offset" bytes away
        int nextOffset = i + offset;

        // allow for +-2ms timing variation
        int maxCompare = pattern[nextOffset] + 2;
        int minCompare = pattern[nextOffset] - 2;

        // if the corresponding next pattern does not match this one, there is a misalignment
        // so the currently assumed pattern length is wrong:
        if ((pattern[i] < minCompare) or (pattern[i] > maxCompare))
        {
          // exit loop by setting iterator at max, then try the next pattern length via the outer loop:
          i = lastElement;
          found = false;
        }
      }

      // if the assumed pattern length matched, we are done and remember
      // the pattern length:
      if (found)
      {
        // this is the correct pattern length:
        matchPattern = offset;

        // exit loop by setting the iterator to max:
        offset = maxPattern + 1;
      }
    }

    // we found a matching pattern
    if (matchPattern > -1)
    {
      // calculate the number of iterations we can do
      // across the raw recorded values
      int rawValues = patternSize - 2;        // disregard first recorded value
      int groups = (rawValues / matchPattern) - 1;  // calculate the number of full groups we have in our recorded values
      // lower by one for safety as we are syncing output between multiple cycles by
      // starting each series with the largest value. This can further shift the index
      // to the right, and we must make sure we are staying within the bounds of our
      // pattern[] array. Else, random numbers will be outputted.

      // stores calculation results:
      int value;
      
      // find the largest element in a pattern so we can align consecutive pattern readings
      // in a way that allows for comparisons
      int largestElement = 0;
      int arrayOffset = 0;
      for (int i = 1; i <= matchPattern; i++)
      {
        if (pattern[i] > largestElement)
        {
          largestElement = pattern[i];
          arrayOffset = i;
        }
      }

      // calculate average and total pattern length
      // found pattern size is in matchpattern

      // used to index in arrays:
      int currentIndex = 0;
      // text output row:
      int row = 0;
      // calculate total pattern length in ms
      int totalMs = 0;

      // clear display:
      display.clearDisplay();
      display.setTextSize(1);

      // initialize array
      int patternResult[matchPattern];
      for (int i = 0; i < matchPattern; i++)
      {
        patternResult[i] = 0;
      }
      
      // take each group...
      for (int g = 0; g < groups; g++)
      {
        // enumerate each group
        for (int u = 0; u < matchPattern; u++)
        {
          currentIndex = arrayOffset + (g * matchPattern) + u;
          patternResult[u] += pattern[currentIndex];
          totalMs += abs(pattern[currentIndex]);
          
        }
      }

      // total pattern length is total length of all samples divided by groups
      int totalPatternLength = totalMs / groups;
      // frequency in Hz is: f = 1 / T where T is in seconds
      float hertz = 1000.0 / totalPatternLength;

      // output stats:
      row = 16;
      display.setCursor(0, row);
      display.print(hertz,1);
      display.print("Hz ");
      display.print(totalPatternLength);
      display.print("ms ");
      display.print(matchPattern);
      display.print("part");

      // output pattern as gfx
      // calculate how many ms are represented by one pixel
      // the display width is 128
      // the pattern duration is totalPatternLength
      // one pixel represents totalPatternLength/128 ms
      float factor = 128.0 / totalPatternLength;
     
      // draw all pattern parts

      // where to start horizontally:
      int x = 0;
      
      for (int u = 0; u < matchPattern; u++)
      {
        int currentvalue = patternResult[u]/groups;
        int width = abs(currentvalue) * factor;
        
        if (currentvalue >0)
        {
          // ON
          display.fillRect(x, 0, width, 5, SSD1306_INVERSE);
          
          
        }
        else
        {
          //display.drawRect(x, 0, width, 5, SSD1306_WHITE);
        }
        x += width;
        
      }
      
      // output average millisec per part
      row = 8;
      display.setCursor(0, row);
      
      for (int u = 0; u < matchPattern; u++)
      {
        float value2 = ((float)patternResult[u])/groups;
        if (value2>0)
        {
          display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        }
        else
        {
          display.setTextColor(SSD1306_WHITE);
        }
        display.print(abs(value2),0);
        Serial.println(value2);
      }

      // output all recorded pattern groups
      row = 25;
      
      for (int g = 0; g < groups; g++)
      {
        display.setCursor(0, row);
        row += 8;
        

        // output the actual pattern group values, beginning at the index pointing
        // to the largest number:
        for (int u = 0; u < matchPattern; u++)
        {
          currentIndex = arrayOffset + (g * matchPattern) + u;
          value=pattern[currentIndex];
          if (value>0)
          {
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
          }
          else
          {
            display.setTextColor(SSD1306_WHITE);
          }
          display.print(abs(value));
        }
      }
      display.display();
    }
    else
    {
      Serial.println("No match found, try adjusting the light source.");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.println("NO PATTERN");
      display.setTextSize(1);
      display.setCursor(0, 30);
      display.println("Adjust light source.");
      display.display();
    }

    // reset variables for next measurement cycle:
    active = false;
    isBright = false;
    duration = 0;
    patternIndex = 0;
    digitalWrite(LedProcessing, LOW);
    currentClock = millis();
  }
}
