const int button1Pin = 2;
const int led1Pin =  13;  

int butRead;


void setup(void) {
  Serial.begin(9600);   
  pinMode(led1Pin, OUTPUT);
  pinMode(button1Pin, INPUT);
}
 
void loop(void) {
  butRead = digitalRead(button1Pin);  


  if (butRead == HIGH) {
    digitalWrite(led1Pin,HIGH);
    Serial.println("Turn On");
  }else{
    digitalWrite(led1Pin,LOW);
    Serial.println("Turn Off");
  }
 
  delay(1000);
}
