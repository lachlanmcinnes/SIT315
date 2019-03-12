int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        // 
void setup(void) {
  Serial.begin(9600);   
  pinMode(LEDpin,OUTPUT);
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading

  if (photocellReading > 100) {
    digitalWrite(11,HIGH);
    Serial.println("Turn On");
  }else{
    digitalWrite(11,LOW);
    Serial.println("Turn Off");
  }
 
  delay(1000);
}
