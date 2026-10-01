//данный код возвращает в сериал монитор счетчик по дефолту на нуле стоит покрутить вправо как он будет увеличива 


// с1 - считывает движение
int pinS1 = 2;

// с2 - сторона движения
int pinS2 = 3;

// (человеческий каунтер) + значит вправо, - значит влево 
int counter = 0;

// технический счетчик переходов энкодера (можно для крайней оптимиизации работать сразу с ней а не с человеческим каунтером на самом деле не такой он и уж роботский)
int encoderCounter = 0;

// предыдущее состояние энкодера
int oldState;

void setup() {
    Serial.begin(9600);

    pinMode(pinS1, INPUT_PULLUP);
    pinMode(pinS2, INPUT_PULLUP);

    bool s1 = digitalRead(pinS1);
    bool s2 = digitalRead(pinS2);

    oldState = (s1 << 1) | s2;
}

void loop() {
    encoder();
}

void encoder() {
    bool s1 = digitalRead(pinS1);
    bool s2 = digitalRead(pinS2);
//сдвиг в двоичное значение чтобы уменьшить вопросы 
    int currentState = (s1 << 1) | s2;
//алгоритм рид ми
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
        counter--;
        encoderCounter = 0;
        Serial.println(counter);
    }

    if (encoderCounter <= -4) {
        counter++;
        encoderCounter = 0;
        Serial.println(counter);
    }
}
