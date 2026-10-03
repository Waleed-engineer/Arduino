const int pin2 = 2; //pin that we are going to use
bool armor = 1; //security to avoid infinity ON in Serial Monitor
unsigned long lastreading; 

void setup() {
  Serial.begin(9600);
  pinMode(pin2, INPUT_PULLUP);
  
}

void loop() {
  button();

}

void button() {
  bool DRpin2 = digitalRead(pin2); //DR - digital Read

  if (DRpin2 == LOW) {
    if (armor && millis() - lastreading > 20) {
      Serial.println("ON");
      armor = false;
    }
  } else {
    armor = true;
    lastreading = millis();
  }
}
