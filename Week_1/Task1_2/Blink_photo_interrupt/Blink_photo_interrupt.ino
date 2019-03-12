int photoPin = 0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)   
long duration;
int distance;

void pciSetup(byte pin){
  *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));
  PCIFR |= bit(digitalPinToPCICRbit(pin));
  PCICR |= bit(digitalPinToPCICRbit(pin));
}

ISR(PCINT1_vect){
  digitalWrite(13,digitalRead(A0));
}


void setup(void) {
  Serial.begin(9600);   

  int i;

  for (i=A0; i<=A5;i++){
    digitalWrite(i,HIGH);
  }

  pciSetup(A0);
}
 
void loop(void) {
  
  
}
