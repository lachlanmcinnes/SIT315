const int btn_pin = 2;
const int led_pin = 5;

uint8_t flag = 0;

void setup() {
  DDRD &= ~(1<<btn_pin);
  PORTD |= (1<<led_pin);

  DDRD |= (1<<led_pin);

  EICRA |= (1<<ISC01);

  EICRA &= ~(1<<ISC00);

  EIMSK |= (1<<INT0);

  sei();
}

void loop() {
  delay(500);
}

ISR(INT0_vect){
  PORTD ^= (1<<led_pin);
}

