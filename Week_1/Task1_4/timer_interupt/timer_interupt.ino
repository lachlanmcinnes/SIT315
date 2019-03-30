const int led_pin = PB5;

const int t1_load = 0;
const int t1_comp = 31250;



void setup() {
  // put your setup code here, to run once:

  DDRB |= (1 << led_pin);

  TCCR1A = 0;

  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  TCNT1 = t1_load;
  OCR1A = t1_comp;

  TIMSK1 = (1 << OCIE1A);

  sei();

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);

}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = t1_load;
  PORTB ^= (1 << led_pin);
}

