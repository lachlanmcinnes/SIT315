const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 8;
const int led1Pin =  PB5;
const int led2Pin = 12;
const int led3Pin = 11;
 
// variables will change:  
int led1State = LOW;
int led2State = LOW;
int led3State = LOW;

//timer interrupt variables:
const int t1_load = 0;
const int t1_comp = 31250;

void pciSetup(byte pin){
  *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin));
  PCIFR |= bit(digitalPinToPCICRbit(pin));
  PCICR |= bit(digitalPinToPCICRbit(pin));
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Hello World!");

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pciSetup(2);
  pciSetup(3);
  pciSetup(8);

  timerSetup();

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
}

ISR(PCINT2_vect){
  led1State = !led1State;
  digitalWrite(led2Pin, led1State);
  Serial.println("Interrupt in pins D0-D7");
}

ISR(PCINT0_vect){
  led3State = !led3State;
  digitalWrite(led3Pin, led3State);
  Serial.println("Interrupt in pins D8-D13");
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = t1_load;
  PORTB ^= (1 << led1Pin);
}

void timerSetup() {
  DDRB |= (1 << led1Pin);

  TCCR1A = 0;

  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  TCNT1 = t1_load;
  OCR1A = t1_comp;

  TIMSK1 = (1 << OCIE1A);

  sei();
}

