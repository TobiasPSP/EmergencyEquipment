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
  
  // map analog input value (range 0-1023) to a value between 0 and 100
  value = map(value, 0, 1024, 0, 100);
  
  Serial.println(value);
}
```

