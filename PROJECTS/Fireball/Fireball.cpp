const byte BtnPins[] = {2, 7, 8};
const byte LedPins[] = {3, 5, 6, 9, 10, 11};
int EnSpeed = 1000;
byte index = 0;
int step = 1;
unsigned long Speed = 0;
byte Brightness = 255;
byte PinDT = 4;
byte PinCLK = 12;
int EnIndex1[] = {125, 250, 375, 500, 625, 750, 875, 1000};
int EnIndex;
unsigned long Before = 0;
void setup() {
  pinMode(PinDT, INPUT_PULLUP);
  pinMode(PinCLK, INPUT_PULLUP);

  Serial.begin(9600);
  for (byte i = 0; i < 3; i++) {
    pinMode(BtnPins[i], INPUT_PULLUP);
  }
  for (byte i = 0; i < 6; i++) {
    pinMode(LedPins[i], OUTPUT);
  }
  delay(20);

  for (byte i = 0; i < 6; i++) {
    digitalWrite(LedPins[i], HIGH);
    delay(1000);
    digitalWrite(LedPins[i], LOW);
  }

  digitalWrite(LedPins[3], HIGH);

  while (BtnIsPressed(BtnPins[0]) == 0);

  digitalWrite(LedPins[3], LOW);
  digitalWrite(LedPins[0], HIGH);
  delay(1000);
}


void Fireball() {
  if (millis() - Speed >= EnIndex1[EnIndex]) {
    Speed = millis();

    if (index >= 5) {
      step = -1;
    } else if (index <= 0) {
      step = 1;
    }

    index += step;

    for (byte i = 0; i < 6; i++) {
      digitalWrite(LedPins[i], LOW);
    }
    analogWrite(LedPins[index], Brightness);
  }
}

void Fireshow() {
      for (byte i = 0; i < 6; i++) {
      analogWrite(LedPins[i], Brightness);
    }
    digitalWrite(LedPins[index], LOW);
  delay(5);
  while (BtnIsPressed(BtnPins[2]) == 0);
  for (byte i = 0; i < 6; i++) {
    digitalWrite(LedPins[i], LOW);
  }
  delay(100);
  Speed = millis();
  analogWrite(LedPins[index], Brightness);
}

bool BtnIsPressed(byte Btn) {
  static bool LastState = HIGH;
  bool CurrentState = digitalRead(Btn);
  if (CurrentState == 0 && LastState == 1) {
    delay(5);
    CurrentState = digitalRead(Btn);
    if (CurrentState == 0) {
      LastState = CurrentState;
      return 1;
    }
  }
  LastState = CurrentState; 
  return 0;
}

void Encoder() {
  static bool lastCLK = HIGH;
  bool currentCLK = digitalRead(PinCLK);

  if (currentCLK == LOW && lastCLK == HIGH) {
    unsigned long now = millis();
    if (now - Before > 5) {
      Before = now;
      if (digitalRead(PinDT) != currentCLK) {
        EnIndex += 1;
      } else {
        EnIndex -= 1;
      }
      EnIndex = constrain(EnIndex, 0, 7);
    }
  }
  lastCLK = currentCLK;
}




void loop() {
  Fireball();


//Potentiometr and encoder control:
Brightness = analogRead(A5) / 5 + 50;
Encoder();

//BUTTONS CONTROL:
  //btn 2[1]
  if (BtnIsPressed(BtnPins[1])) {
    step = -step;
  }
  //btn 3
  if (BtnIsPressed(BtnPins[2])) {
    Fireshow();
  }
  //btn 1
  if (BtnIsPressed(BtnPins[0])) {
    while (BtnIsPressed(BtnPins[0]) == 0);
    delay(100);
  }
}
