/*

uae of millis() to control multiple mosfets in different frequencies in parallel
*/
#define PINMOSFET        6

// on-off-sequence for pattern1 in milliseconds:
// pattern Movia D (Haensch)
long pattern1[] = { 154,45,16,25,15,25,16,188 };
int pattern1Size = sizeof(pattern1)/4;
long pattern1Timer = 0;        // millis() when pattern part was activated
int pattern1Count = 0;         // index into array pointing at next pattern part
bool pattern1State = false;    // start with lamp turned off
int brightness = 255;

void ResetPattern1()
{
  pattern1Timer = millis(); // millis() when pattern part was activated
  pattern1State = false;    // start with lamp turned off
}

void SwitchLampPattern1(bool state)
{
    
  if (state)
  {
    //digitalWrite(PINMOSFET, HIGH);
    // set led brightness via PWM (must be connected to a PWM pin!)
    // Uno, Nano, Mini 3, 5, 6, 9, 10, 11 490 Hz (pins 5 and 6: 980 Hz)
    // Mega 2 - 13, 44 - 46 490 Hz (pins 4 and 13: 980 Hz)
    // Uno WiFi Rev2, Nano Every 3, 5, 6, 9, 10 976 Hz
    analogWrite(PINMOSFET, brightness);
    
    digitalWrite(LED_BUILTIN, HIGH); 
    
  }
  else
  {
    digitalWrite(PINMOSFET, LOW);
    digitalWrite(LED_BUILTIN, LOW); 
  }
}


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  
  // define output pins:
  pinMode(PINMOSFET, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  ResetPattern1(); 
  // turn lamp on for first part of pattern
  pattern1State = !pattern1State;
  SwitchLampPattern1(pattern1State);
}

// the loop function runs over and over again forever
void loop() {
  long curTimer = millis();
  Serial.print("Arrayindex=");
  Serial.println(pattern1Count);
  
  Serial.print("curTimer=");
  Serial.print(curTimer);
  Serial.print(", waiting for=");
  Serial.print(pattern1[pattern1Count]+pattern1Timer);
  Serial.print(". MaxArraySize=");
  Serial.print(pattern1Size-1);
  
  if (curTimer > pattern1[pattern1Count]+pattern1Timer)
  {
    pattern1Timer = curTimer;
    pattern1Count++;
    Serial.print(". pattern1Count>pattern1Size? ");
    Serial.println(pattern1Count>pattern1Size-1);
    Serial.print("pattern1Count=");
  Serial.print(pattern1Count);
  Serial.print(", pattern1Size=");
  Serial.print(pattern1Size);
  bool endOfCycle=pattern1Count>pattern1Size-1;
  Serial.print(", endOfCycle=");
  Serial.print(endOfCycle);
  
    if (endOfCycle)
    {
      pattern1State = true;
      pattern1Count = 0;
      Serial.print("NEW pattern1Count=");
  Serial.println(pattern1Count);
    }
    else
    {
      pattern1State = !pattern1State;
    }
    SwitchLampPattern1(pattern1State);
  }
}
