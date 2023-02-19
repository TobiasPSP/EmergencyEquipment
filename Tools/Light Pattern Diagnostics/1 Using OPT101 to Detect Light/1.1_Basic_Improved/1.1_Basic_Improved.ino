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
