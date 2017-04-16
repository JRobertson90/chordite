const int ledPin =  17;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(0) == LOW
   || digitalRead(1) == LOW
   || digitalRead(2) == LOW
   || digitalRead(3) == LOW
   || digitalRead(4) == LOW
   || digitalRead(5) == LOW
   || digitalRead(6) == LOW
   || digitalRead(7) == LOW
   || digitalRead(8) == LOW
   || digitalRead(9) == LOW
   || digitalRead(10) == LOW
   || digitalRead(16) == LOW
   || digitalRead(14) == LOW
   || digitalRead(15) == LOW
   || digitalRead(18) == LOW
   || digitalRead(19) == LOW
   || digitalRead(20) == LOW
   || digitalRead(21) == LOW
  ) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
  delay(1);
}
