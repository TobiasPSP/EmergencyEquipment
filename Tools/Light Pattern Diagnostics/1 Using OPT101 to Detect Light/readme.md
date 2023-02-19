# Detecting Emergency Light Emissions with OPT1101 and CJMCU Board

As a first step, let's get the OPT101 board working and read in some light measurements so we can evaluate whether or not it is suitable for detecting emergency light patterns and better understand how the OPT101 and light detection actually works.

## Connecting Arduino and OPT101

I connected the board to a *Arduino Nano*: pins **VCC** to +5V, pins **COM** and **-V** to GND. The pin **GND** remains unconnected.

The board returns an analog output at its pins **OUT** and **1MB**. The analog output returns a voltage in the range of *0V* to *5V* and raises in a linear way with the light intensity.

So I connected both of the analog output pins to Arduino **pin 2**. Any analog input pin will do though (provided you adjust the pin setting in the code).

*Note: In this simple example, I am using the board *as-is*: I did not add soldering bridges underneath the OPT101 chip (which can be used to change its sensitivity). For this reason, the analog output is read from both the pins **OUT** and **1M**.*

## Code for Testing

The code below shows the most simplistic setup possible, designed to monitor the OPT101 analog output.

### Mapping Values to 0-100%
Note the use of the function *map()*: Arduinos analog input pins convert any analog signal between 0 and 5V to a digital value in the range of 0 - 1023. 

*map()* maps these values to a custom range. In our scenario, I would like to receive light intensity, so I am not interested in a value of 0 - 1023 but instead would prefer a percentage value between 0 (complete darkness) and 100 (full brightness).

### Mapping Values to Voltage
The actual voltage rerturned by OPT101 could as well be mapped via *map()* however I simply adjusted it via the formula *currentvoltage = currentreading * (maximumVoltage / maximumValue)*. 

*Note: when you do these calculations, make sure you use the correct data types. Instead of 

```c++
voltage= value * (5 / 1023);
```

make sure you write:

```c++
voltage= value * (5.0 / 1023.0);
```

Here is the complete [testing code](./1_Basic/1_Basic.ino):

```c++
// make sure you adjust the pin to the analog input pin you use
// this pin reads the analog output signal from OPT101
#define sensor A2

void setup() {
  // setting the baud rate for the serial monitor
  // make sure you set this baud rate in your serial monitor as well
  // or else output will be garbled
  Serial.begin(115200);
}

void loop() {
  // read sensor value which is a voltage between 0 and 5V
  // voltage relates to light intensity exposed to the opt101 unit
  int value = analogRead(sensor);
  
  // calculate measured voltage
  float voltage= value * (5.0 / 1023.0);
  
  // map analog input value (range 0-1023) to a value between 0 and 100
  int percentage = map(value, 0, 1024, 0, 100);
  
  Serial.print(percentage);
  Serial.print("% (raw value ");
  Serial.print(value);
  Serial.print(", ");
  Serial.print(voltage);
  Serial.println(" mV)");
}
```

Once you have uploaded the code, open the serial monitor to view the readings. Make sure your serial monitor is using the correct baud rate, or adjust the baud rate you prefer in the code.

## Interpreting Results

The readings report **brightness percentage**, **raw reading** and **supplied voltage**. When you move a light source towards the OPT101, the readings should change.

Here are typical readings in a daylight ambient environment (room with window) when I moved the beam of a torch towards the OPT101:

```
11% (raw value 122, 0.60 mV)
11% (raw value 122, 0.60 mV)
12% (raw value 131, 0.64 mV)
12% (raw value 131, 0.64 mV)
12% (raw value 131, 0.64 mV)
13% (raw value 135, 0.66 mV)
13% (raw value 135, 0.66 mV)
13% (raw value 137, 0.67 mV)
13% (raw value 137, 0.67 mV)
13% (raw value 137, 0.67 mV)
13% (raw value 139, 0.68 mV)
13% (raw value 139, 0.68 mV)
13% (raw value 140, 0.68 mV)
13% (raw value 141, 0.69 mV)
13% (raw value 141, 0.69 mV)
13% (raw value 143, 0.70 mV)
14% (raw value 144, 0.70 mV)
14% (raw value 145, 0.71 mV)
14% (raw value 146, 0.71 mV)
14% (raw value 148, 0.72 mV)
14% (raw value 153, 0.75 mV)
15% (raw value 154, 0.75 mV)
15% (raw value 155, 0.76 mV)
16% (raw value 170, 0.83 mV)
16% (raw value 171, 0.84 mV)
16% (raw value 174, 0.85 mV)
17% (raw value 178, 0.87 mV)
17% (raw value 184, 0.90 mV)
18% (raw value 191, 0.93 mV)
19% (raw value 198, 0.97 mV)
20% (raw value 205, 1.00 mV)
20% (raw value 212, 1.04 mV)
21% (raw value 221, 1.08 mV)
22% (raw value 231, 1.13 mV)
23% (raw value 241, 1.18 mV)
24% (raw value 253, 1.24 mV)
26% (raw value 269, 1.31 mV)
28% (raw value 289, 1.41 mV)
32% (raw value 330, 1.61 mV)
39% (raw value 405, 1.98 mV)
58% (raw value 601, 2.94 mV)
84% (raw value 863, 4.22 mV)
84% (raw value 863, 4.22 mV)
84% (raw value 862, 4.21 mV)

```

## OPT101 Sensitivity

By looking at the readings above, it becomes clear that OPT101 (at least in my scenario) does not return voltages in a range of 0-5V. Instead, long before I actually pointed the torch directly onto the OPT101, the reading maxed out at 4.22V.

So apparently, the built-in sensitivity of OPT101 is adjusted to ambient light scenarios. Measuring ultra bright lights is beyond the scope of the default settings. 

### Adjusting the Range
There are options to change the OPT101 sensitivity (both increase and decrease its sensitivity through the use of external resistors and capacitors). Whether or not changing the default sensitivity is needed is yet to be determined.

It has become evident already though that the maximum output is not 5V but rather 4.22V (in my case, there may be variations). So the maximum digital reading is not a value of 1023 but rather one of 863.

So let's adjust the code accordingly.

## Better Code for Testing

By lowering the valid range from 0-1023 to 0-863, readings will be more suitable for testing. In addition, I am no longer outputting the raw readings and voltages, and decided to output light intensity in percent with a float instead of an integer.

Here is the improved [testing code](./1.1_Basic_Improved/1.1_Basic_Improved.ino) that now emits the detected light intensity in real-time as a percentage:

```c++
// make sure you adjust the pin to the analog input pin you use
// this pin reads the analog output signal from OPT101
#define sensor A2

void setup() {
  // setting the baud rate for the serial monitor
  // make sure you set this baud rate in your serial monitor as well
  // or else output will be garbled
  Serial.begin(115200);
}

void loop() {
  // read sensor value which is a voltage between 0 and 5V
  // voltage relates to light intensity exposed to the opt101 unit
  int value = analogRead(sensor);
  
  // calculate measured voltage
  float voltage= value * (5.0 / 1023.0);
  
  // map analog input value (range 0-1023) to a value between 0 and 100
  // turns out the sensor maximum is 4.22V which represents a value of 863,
  // so this is the real range we want to map to 1-100%:
  float percentage = map(value, 0, 863, 0, 100);
  
  Serial.print(percentage);
  Serial.println("%.");
}
```

## Final Evaluation

Since I am going to use this setup to evaluate the flash frequency of emergency lights (and not ambient light scenarios), it's now time to evaluate whether the default sensitivity works for this purpose.

I uploaded the code above and turned on an emergency light close by. It turned out that OPT101 readings initially did not respond much so the default sensitivity is not too high for the purpose. It then turned out that OPT101 picks up light in a fairly focused manner: when I moved the OPT101 in such a way that the emergency light shined more or less horizontally onto OPT101, things started to work.

### Differentiating Light and Dark Patterns (Ambient Scenario)

Below is a sample reading while operating a *Hänsch Movia D* magnetic emergency light in an ambient light scenario: I worked at daylight in an average inside room while operating the emergency light.

```
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
100.00%.
100.00%.
36.00%.
27.00%.
23.00%.
21.00%.
19.00%.
18.00%.
18.00%.
17.00%.
17.00%.
16.00%.
16.00%.
16.00%.
16.00%.
16.00%.
16.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
15.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
61.00%.
35.00%.
27.00%.
23.00%.
20.00%.
19.00%.
18.00%.
18.00%.
17.00%.
17.00%.
16.00%.
16.00%.
```

Keep in mind that the code is sampling light emission in extremely short time intervals (which is the whole point when trying to detect flash patterns). What becomes evident by looking at the readings is that there is a sufficient differentiation between dark and light periods, and that the ambient light is not interfering:

When the emergency light emits a pulse, OPT101 records full brightness (99-100%). When there is no pulse, the reading is clearly distinguishable (typically 15%).

### Differentiating Light and Dark Patterns (Night Scenario)

To better understand the influence of ambient light, I repeated the test in a completely dark room, simulating a night scenario:

```
0.00%.
0.00%.
0.00%.
0.00%.
0.00%.
0.00%.
0.00%.
99.00%.
99.00%.
99.00%.
99.00%.
99.00%.
(...)
99.00%.
99.00%.
99.00%.
100.00%.
23.00%.
10.00%.
6.00%.
4.00%.
3.00%.
2.00%.
2.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
1.00%.
0.00%.
0.00%.
0.00%.
0.00%.
0.00%.
0.00%.
```

It turns out that the reading of around 15% in the previous test for OFF-phases seems to be attributable to ambient light. 

However, when looking at extensive test data in this night scenario, it turned out that the OPT101 is indeed picking up light in a focused fashion: light that shines directly onto the OPT101 chip produces reliable high readings whereas shining light even at slight angles will decrease the readings considerably to a degree where they blend in with ambient light.

## Conclusion

For the purpose of detecting emergency light patterns, the OPT101 and its default sensitivity are well suited:

* Ambient light and no light can be clearly distinguished from emergency light patterns. A reading of *95%* clearly determines a OFF phase, and ambient light produces readings no higher than 60%.
* Response frequency is fast enough (low latency) to take samles in millisecond intervals
* There seems to be no "blinding": even when the OPT101 was exposed to extremely bright light, it will detect darkness reliably in the next cycle, just a millisecond later

Above is true *only* when the light shines directly onto the OPT101. If the emergency light is reaching the OPT101 even at a slight angle, readings can fall into the overlap area and produce brightness readings of 40-70%.

So when analyzing emergency lights, care must be taken to point the OPT101 directly towards the emergency light. 

### Next steps

Now that we know that OPT101 is a great sensor for the task, in the next step we need to reduce the data and interpret ON and OFF phases reliably. The results will build the basis for pattern detection.

When we identify ON and OFF phases in our next step, this will also be the place to conduct a few more tests:

* What is the maximum possible distance between the OPT101 detector and the emergency light to get reliable readings?
* What is the maximum angle for emitted light that still safely produces reliable results?



