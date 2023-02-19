# Exploring the OPT1101 and CJMCU Board

As a first step, let's get the OPT101 board working and read in some light measurements so we can better evaluate its sensitivity.

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

Here is the complete testing code:

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

## Interpreting Results



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
