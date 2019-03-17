const int button1Pin = 2;
const int button2Pin = 3;
const int led1Pin =  13;
const int led2Pin = 12;
 
// variables will change:  
int led1State = LOW;
int led2State = LOW;
 
void setup() {
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(button1Pin), toggleled1, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), toggleled2, FALLING);
}
 
void loop() {

  delay(500);
}

void toggleled1() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State);
  Serial.println("Interrupt Button 1");
}

void toggleled2() {
  Serial.println("Interrupt Button 2");
  led2State = !led2State;
  digitalWrite(led2Pin, led2State);
  
}

