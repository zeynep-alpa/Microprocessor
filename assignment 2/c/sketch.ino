#define ledPin 6
#define relayPin 4
#define buttonPin 2

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // buton LOW olunca aktif olacak
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW);
  }
}
