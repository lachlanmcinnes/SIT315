int sensPin = 2;
int led = 6;
int ledState = LOW;


void setup()  {
  Serial.begin(9600);
  pinMode(sensPin,INPUT_PULLUP);
  pinMode(led, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(sensPin),toggle,CHANGE);
}
void loop()  {
    delay(2000);
}

void toggle() {
  ledState = !ledState;
  digitalWrite(led,ledState);
  Serial.println(ledState);
}

