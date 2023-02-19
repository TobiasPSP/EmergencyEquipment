# Automatically Detecting Light Patterns

This is part 3 of my series about decoding light patterns of emergency lights.

After being able to read emergency light emissions and calculate the ON and OFF phases, now we are going to add code to automatically determine the length of a light pattern.

OPT101 is delivering an endless series of ON and OFF states that resemble an endless series of light patterns. To correctly visualize a pattern, we need to know the number of ON and OFF segments a given light pattern consists of until it repeats the pattern.

## Reviewing the Concept

For the details about calculating brightness levels and turning them into timed parts please refer to the previous parts.

To be able to analyze the light pattern, the function *loop()* stores the light readings in an array **pattern[]**. By default, it will read 80 values until it starts the analyzing part.

You can change the number of stored values via **patternSize**. A smaller number will yield faster results however the number should always be at least twice the number of suspected pattern parts. A higher number will provide more reliable results.

Once the readings are collected, a pattern is identified:

* **Testing Pattern Sizes**: An outer loop tests for possible pattern sizes in the range of 2 to 20. A 2-part pattern would be a simple ON-OFF-blink whereas a 20-part pattern would consist of 20 individual ON- and OFF-phases. If your patterns are even more complex, you can increase **maxPattern**. Make sure you also increase the size of the recorded values via **patternSize** to at least double that size.
* **Identifying Repetitive Values**: An inner loop then tests each pattern size by checking whether the recorded values repeat correctly. If a mismatch is found, the inner loop exists, and the outer loop starts to test the next higher pattern size.

This way, the shortest possible pattern size is identified, provided there is a pattern present. 

Since individual readings have a slight variance of +-2ms, when comparing repetitive values, the code uses an allowance of +-2ms to identify matching values.

```c++
// sensorpin
#define sensor A2
#define patternSize 80   // number of brightness readings recorded before analysis starts

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

void setup() {
  // set up serial monitor baud rate
  // make sure this matches the settings in your serial monitor:
  Serial.begin(115200);

  // define analog in pin receiving the OPT101 brightness readings:
  pinMode (sensor, INPUT);

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
        duration = duration * -1.0;
      }

      // store current reading in array:
      pattern[patternIndex] = duration;
      patternIndex++;
    }
  }

  // is the recording done and all (patternSize) raw values have been recorded to the array?
  if (patternIndex > patternSize)
  {
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

      // output all recorded pattern groups
      for (int g = 0; g < groups; g++)
      {
        Serial.print("<");
        Serial.print(matchPattern);
        Serial.print(">: ");

        // output the actual pattern group values, beginning at the index pointing
        // to the largest number:
        for (int u = 0; u < matchPattern; u++)
        {
          int currentIndex = arrayOffset + (g * matchPattern) + u;
          Serial.print("[");
          Serial.print(pattern[currentIndex]);
          Serial.print("]");
        }
        Serial.println("");
      }
    }
    else
    {
      Serial.println("No match found, try adjusting the light source.");
    }

    // reset variables for next measurement cycle:
    active = false;
    isBright = false;
    duration = 0;
    patternIndex = 0;
    currentClock = millis();
  }
}
```

Once you uploaded the code, open the serial monitor, then point an emergency light (or any light emitter with a pattern) to OPT101.

It may take a few seconds to record 80 values. Once all 80 values are recorded, the data is analyzed and the result returned. If a pattern was detected, the output may look similar to this:

```
<8>: [187][-153][45][-17][24][-16][24][-17]
<8>: [187][-153][45][-17][23][-18][23][-17]
<8>: [187][-153][45][-17][24][-16][25][-16]
<8>: [186][-154][45][-16][25][-16][24][-16]
<8>: [188][-152][46][-17][23][-17][24][-17]
<8>: [186][-154][45][-16][25][-16][23][-17]
<8>: [187][-154][45][-16][24][-16][25][-16]
<8>: [187][-153][45][-17][24][-17][23][-16]
<8>: [187][-153][45][-17][23][-18][23][-16]
<8>: [188][-152][45][-18][23][-17][23][-18]
<8>: [186][-154][45][-16][25][-16][24][-16]
<8>: [187][-153][45][-18][23][-16][25][-16]
<8>: [187][-153][45][-17][24][-17][23][-17]
<8>: [187][-154][45][-16][24][-16][25][-16]
<8>: [186][-154][45][-16][25][-16][24][-16]
<8>: [188][-153][45][-17][23][-17][24][-17]
```

The first number is the number of identified parts, in this case 8 parts.

After that, you see the individual timings for the light pattern. Negative values are OFF phases, and all numbers are in milliseconds. The numbers in the sample above were generated from a *Hänsch Movia D* emergency light.


