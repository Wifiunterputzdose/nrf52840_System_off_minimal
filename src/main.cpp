
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

#define WAKE_PIN D0   // << change Pin Number for waking up from system off

void enterSystemOff() {
  Serial.println("System off");
  Serial.flush();
  delay(100);  

  // Wakeup-Pin as Input with Pullup
  pinMode(WAKE_PIN, INPUT_PULLUP);

  // nRF52840 registry for Wakeup trough GPIO LOW
  NRF_GPIO->PIN_CNF[g_ADigitalPinMap[WAKE_PIN]] |= 
      (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);

  delay(10);

  // System OFF aktivieren
  NRF_POWER->SYSTEMOFF = 1;

  // wartet hier bis Reset
  while (1);
}


void setup() {
  Serial.begin(115200);
  delay(2000);   
  Serial.println("System On");

  pinMode(LED_GREEN, OUTPUT);
}

void loop() {


    // blink 3 times before sleep
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_GREEN, LOW);   
    delay(1000);
    Serial.println("System Off");
    digitalWrite(LED_GREEN, HIGH);  
    delay(1000);
  }
 
 enterSystemOff();

}