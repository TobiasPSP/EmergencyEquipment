// sensorpin
#define sensor A2

int threshold = 90;       // anything *above* this value will be considered BRIGHT
// the range is 0-99, so by specifyinng 99, you only accept
// 100% brightness. Note that a value of 100 would never be reached
// because 100 is the max possible value, and it can never be
// greater than 100.
unsigned long  minInterval = 3;  // minimum length of a pattern interval in millisec
// this is a safety measure for inconsistencies. Only when a pattern change
// occurs that is at minimum of minInterval length will this be considered
// a true pattern change
bool active = false;      // currently, the sensor is receiving bright light
bool isBright = false;    // when true, the sensor input is greater than 95% so there is strong light shining on it
long  currentClock = 0;   // the milliseconds recorded at last pattern change
long  duration = 0;       // duration of last pattern
int   count = 0;          // number of readings

void setup() {
  Serial.begin(115200);
  pinMode (sensor, INPUT);

  // set the variable to the current millisecond count
  // we measure duration from here, so anything that occurs in the future will be the
  // time in milliseonds measured from this point in time
  currentClock = millis();
}

void loop() {
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

    if (duration > minInterval)
    {
      currentClock = millis();             // reset the clock
      active = isBright;                   // reset the current mode

      // mark "dark" phases by negating the value
      if (!isBright) {
        duration = duration * -1.0;
      }

      // recorded (previous) pattern was LIGHTED:
      Serial.print("[");
      Serial.print(duration);
      Serial.print("]");
      count++;
    }
  }

  // add a new line after 10 readings:
  if (count > 10)
  {
    count = 0;
    Serial.println("");
  }
}
