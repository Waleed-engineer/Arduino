//код выводит в монитор каунтер если каунтер увеличился на 1 значит повернули в право если в - значит в влево антидребезг подтяжка резистора есть



//с1 - считывает движение 
int pinS1 = 2;
//с2 = сторону движения
int pinS2 = 3;
//пинкей - кнопка на энкодере
int pinKey = 4;
//через нее будем выводит в сериал монитор если + значит ручка больше крутилась в право если в - значит лево 0 нейтралка
long counter = 0;
//для понимания изменилось ли состояния энкодера
bool oldStateS1 = 0;

unsigned oldTime = 1;

void setup() {
  // put your setup code here, to run once:
  //настраиваем вывод 
  Serial.begin(9600);
  //резистор чтоб уменьшить дребезг и показания с поля руки(инпут_пуллап вместо инпут)
  pinMode(pinS1, INPUT_PULLUP);
  pinMode(pinS2, INPUT_PULLUP);
  pinMode(pinKey, INPUT_PULLUP);

  
  

}

void loop() {
  //считываем значение с1, с1 у нас это пин считывающий двигаеться ручка или нет а во время двигжения ручкой она выдаст 1 так как есть движения при отсутсвие 0
    bool currentS1 = digitalRead(pinS1);
    // вообще должно быть HIGH\LOW но булево только 0 1 а булево меньше памяти посравнении с инт
    if (oldStateS1 == 1 && currentS1 == 0) {

    
      if (isDebounced()) {
          //начинаем засекать время от самого первого тока чтобы отсечь лишнее (ножка никогда не встает идеально она всегда сделает пару дрожевых движений изза которых выходит 0 1 0 1 0  0 0 0 и чтобы убрать эти лишнии показания нужно дать время ножке встать правильно на позицию)
        oldTime = millis();
      
        bool currentS2 = digitalRead(pinS2);

        if (currentS2) {
          //counter++ то же самое что и counter = counter + 1
            counter++;
        } else {
            counter--;
        }

        Serial.println(counter);
      }
    }

    oldStateS1 = currentS1;
}

//антидребезг
bool isDebounced() {
  unsigned long long currentTime = millis();
  //5 миллисекунд достаточно чтобы ножка встало спокойно на свое место
  if (currentTime - oldTime < 5) {
    return 0;
  }else {
    return 1;
  }
  
}
