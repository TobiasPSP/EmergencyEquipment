# Identifying Light Patterns

In our second part - after getting the OPT101 to work with Arduino and analyzing raw brightness readings - we'll now consolidate the flood of raw brightness readings emitted by the OPT101.

## Turning Raw Values to Timings

We'd like to know the exact timings of emergency light patterns, so instead of a series of current brightness levels, I'd like to turn these brightness levels into simple "ON" and "OFF" readings.

Next, instead of getting a flood of repetitive "ON" and "OFF" readings, I just want to know how *long* these "ON" and "OFF" phases were.

So here is the plan:

* **Define ON and OFF**: Any brightness above 90% is considered to be "ON", anything else is "OFF". From our previous tests we know that the sensitivity of OPT101 shows brightness levels of >90% when the emergency light is ON, regardless of ambient light conditions.
* **Periods Instead of Readings**: Let's use a variable that remembers the last state - ON or OFF - and changes only when the state changes. This way we know when the light goes from ON to OFF and vice versa.
* **Timings**: Arduino returns the number of elapsed milliseconds in *millis()*. By recording this value at every state change and subtracting the currently elapsed milliseconds from the last state change, we can easily report how long each ON or OFF state was
* **Housekeeping**: to make measurements more reliable, let's define a realistic minimum durations for each light phase, i.e. 3ms. Reason is that whenever the light is turned on or off, there may be transient reflections or other artifacts that could lead to temporary high frequency ON-OFF-ON states.

## The Code

Based on the code created in part 1, here is the [new code](./1_DetectLightAndDark/1_DetectLightAndDark.ino) that incorporates the requirements from above:



```c++
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

```
