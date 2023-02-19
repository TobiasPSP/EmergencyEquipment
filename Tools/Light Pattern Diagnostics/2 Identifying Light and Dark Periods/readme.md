# Identifying Light Patterns

In our second part - after [getting the OPT101 to work](.\1%20Using%20OPT101%20to%20Detect%20Light) with Arduino and analyzing raw brightness readings - we'll now consolidate the flood of raw brightness readings emitted by the OPT101.

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

## Analyzing Results

When uploading and running the code, the serial monitor shows no output at first. That's by design because the code "assumes" we are in a "dark" phase (including ambient light) and is waiting for a light change, i.e. strong light.

When you now with a light source - i.e. a flashlight - point to the OPT101, you'll see the timings appear in serial monitor. 

### Decoding Light Patterns

I turned on a *Hänsch Movia D* emergency light and made sure its light pointed directly onto the OPT101. Note that it is not sufficient to just turn on the light somewhere in the room. The light must directly hit the OPT101.

This is what I got:

```
[19636][-110][46][-16][25][-16][24][-16][188]
[-153][46][-15][25][-15][26][-15][187][-153][46][-15]
[26][-15][25][-16][188][-152][46][-16][24][-17][24]
[-15][188][-152][47][-16][25][-15][24][-17][187][-153]
[46][-15][25][-16][25][-15][189][-151][46][-17][24]
[-15][26][-15][188][-152][47][-15][25][-16][24][-16]
[188][-152][46][-16][25][-15][26][-15][187][-153][46]
```

The first value is very large which is not surprising: this is the time (in milliseconds) that elapsed since you uploaded the sketch and eventually decided to point a bright light source onto the OPT101.

The remaining values decode the light pattern of the *Hänsch Movia D* emergency light that I used. Negative values are "dark" (OFF) phases, and all numbers are milliseconds.

### Manual Analysis

What's encouraging is that the setup is very *specific* and *reliable*. When there is no direct light hitting the OPT101, then there is no output in the serial monitor. And when there is light input, the values seem realistic.

However, at this point we just get timings for ON and OFF phases. We still have to evaluate the readings manually. Since I happen to know that the *Hänsch Movia D* - that I used in this test to generate the readings - works with a 8-part light pattern, I can manually split up the readings in groups of 8, omitting the initial reading of course:

```
[-110][46][-16][25][-16][24][-16][188]
[-153][46][-15][25][-15][26][-15][187]
[-153][46][-15][26][-15][25][-16][188]
[-152][46][-16][24][-17][24][-15][188]
[-152][47][-16][25][-15][24][-17][187]
[-153][46][-15][25][-16][25][-15][189]
[-151][46][-17][24][-15][26][-15][188]
[-152][47][-15][25][-16][24][-16][188]
[-152][46][-16][25][-15][26][-15][187]
```

### Conclusions

The readings clearly show that the OPT101 is able to reliably "decipher" the high frequency light pattern. In fact, the resolution is very high. Even a part of the pattern with a duration of just 15 milliseconds consists of a multitude of single raw readings.

That said, there are variations in the result:

* Invalid first reading: The first reading is a OFF-phase of 110ms. All subsequent readings show 151-153ms for this part of the pattern. The invalid reading is related to how I started the measurement: by turning on the lamp. When the lamp is turned on, apparently it takes a few milliseconds for it to reach full operational status.
* Variations: It is easy to see that the general light pattern was decoded correctly. Individual timings do have variations, though. This is most likely related to the way how we record them. Arduino is fast enough to produce a multitude of readings per pattern, however this is still not enough to reliably hit the exact moment when the light change occurs. When you sum up the timings per pattern in the example above, you'll see that each series takes 482ms, so the variations are related to the times in point when the light change was detected.

For my purposes, the results are good enough as I can manually round values to what makes sense to me. If you do use rounding and would like a realistic light pattern, make sure though that the total of all timings sums up to the total pattern time identified, i.e. in this case 482ms.

## Next Steps

That was a good result which leads to further improvements:

* **Automatic Pattern Recognition**: Currently, we need to manually find out the number of parts a given light pattern comprises. In the example above, I happened to know that it was a 8-part pattern so I could get the readings in order. In the upcoming part 3, Arduino should auto-detect the number of pattern parts
* **Automatic Corrections**: as seen, based on the high frequency of the light patterns and the relatively slow speed of Arduino, we did not always hit the exact time when a pattern change occured, leading to timing variations in the range of 1-2ms per ON-OFF-sequence. So in our next part, we'll try and validate this theory by using a faster Arduino Mega and see if this improves (lowers) variance. Regardless, thanks to the automatic pattern part recognition that we already have on our todo list, we then can ask Arduino to record multiple series of light patterns. Since the overall length per pattern is already precise  enough, we can then use math to polish the individual sequence timings.




