// с1 - считывает движение
int pinS1 = 2;

// с2 - сторона движения
int pinS2 = 3;

// пинкей - кнопка на энкодере
int pinKey = 4;

// + значит вправо, - значит влево
int counter = 0;

// технический счетчик переходов энкодера
int encoderCounter = 0;

// предыдущее состояние энкодера
int oldState;

void setup() {
    Serial.begin(9600);

    pinMode(pinS1, INPUT_PULLUP);
    pinMode(pinS2, INPUT_PULLUP);
    pinMode(pinKey, INPUT_PULLUP);

    bool s1 = digitalRead(pinS1);
    bool s2 = digitalRead(pinS2);

    oldState = (s1 << 1) | s2;
}

void loop() {
    bool s1 = digitalRead(pinS1);
    bool s2 = digitalRead(pinS2);

    int currentState = (s1 << 1) | s2;

    if (oldState == 0b00 && currentState == 0b01) {
        encoderCounter++;
    }
    else if (oldState == 0b01 && currentState == 0b11) {
        encoderCounter++;
    }
    else if (oldState == 0b11 && currentState == 0b10) {
        encoderCounter++;
    }
    else if (oldState == 0b10 && currentState == 0b00) {
        encoderCounter++;
    }
    else if (oldState == 0b00 && currentState == 0b10) {
        encoderCounter--;
    }
    else if (oldState == 0b10 && currentState == 0b11) {
        encoderCounter--;
    }
    else if (oldState == 0b11 && currentState == 0b01) {
        encoderCounter--;
    }
    else if (oldState == 0b01 && currentState == 0b00) {
        encoderCounter--;
    }

    oldState = currentState;

    if (encoderCounter >= 4) {
        counter++;
        encoderCounter = 0;
        Serial.println(counter);
    }

    if (encoderCounter <= -4) {
        counter--;
        encoderCounter = 0;
        Serial.println(counter);
    }
}
