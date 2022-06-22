
int relayOn = 2;
int relayHigh = 3;


void setup() {

  pinMode(relayOn, OUTPUT);
  pinMode(relayHigh, OUTPUT);
  digitalWrite(relayOn, LOW);
  digitalWrite(relayHigh, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayOn, HIGH);
  delay(1000);
  digitalWrite(relayHigh, HIGH);
  delay(1000);
  digitalWrite(relayHigh, LOW);
  delay(1000);
  digitalWrite(relayOn, LOW);
  delay(1000);
}
