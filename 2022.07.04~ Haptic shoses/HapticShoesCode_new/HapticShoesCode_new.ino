int fsrAnalogPin1 = 0; // FSR is connected to analog 0
int fsrAnalogPin2 = A1;
int Vivepin1 = 9;      // connect Red LED to pin 11 (PWM pin)
int Vivepin2 = 10; 
int fsrReading1;      // the analog reading from the FSR resistor divider
int fsrReading2;      // the analog reading from the FSR resistor divider
int vibe1;
int vibe2;
int air1;
int air2;

const int SOLENOID1 =6;
const int SOLENOID2 =7;
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(Vivepin1, OUTPUT);
  pinMode (SOLENOID1, OUTPUT);
  pinMode (SOLENOID2, OUTPUT);
}
 
void loop(void) {
  fsrReading1 = analogRead(fsrAnalogPin1);
  Serial.print("Analog reading1 = ");
  Serial.println(fsrReading1);

  fsrReading2 = analogRead(fsrAnalogPin2);
  Serial.print("Analog reading2 = ");
  Serial.println(fsrReading2);
  
  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map!\
  
  vibe1 = map(fsrReading1, 0, 1023, 0, 255);
  vibe2 = map(fsrReading1, 0, 1023, 0, 255);
  
  if(fsrReading1 != 0)
  {
    tone(9,vibe1/150);
  }
  if(fsrReading1 == 0)
  {
    noTone(9);
  }
  
  air1 = map(fsrReading2, 0, 1023, 0, 255);
  air2 = map(fsrReading2, 0, 1023, 0, 255);
  // LED gets brighter the harder you press
  digitalWrite(Vivepin1, vibe1);
  digitalWrite(Vivepin2, vibe2);
  digitalWrite(SOLENOID1, air1);
  digitalWrite(SOLENOID2, air2);
   
  if(fsrReading2 >= 50)
  {
    numericTouched();
  }
  else if(fsrReading2==0)
  {
    numericReleased();
  }

}
void numericTouched()
{
  digitalWrite(SOLENOID1, LOW); //closed
  digitalWrite(SOLENOID2, HIGH); //open
  delay(200);
  //digitalWrite(SOLENOID1, LOW); //open
  //digitalWrite(SOLENOID2, LOW); //closed
  //delay(50);
}
void numericReleased()
{
  digitalWrite(SOLENOID1, HIGH); //open
  digitalWrite(SOLENOID2, HIGH); //open
  //delay(200);
}
void numeric()
{
  digitalWrite(SOLENOID2, HIGH);
  delay(200);
  digitalWrite(SOLENOID2, LOW);  
}
