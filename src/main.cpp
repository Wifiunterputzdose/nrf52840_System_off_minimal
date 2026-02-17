
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

void setup() {
  Serial.begin(115200);
  delay(2000);   // USB Zeit geben
  Serial.println("START");
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {

  digitalWrite(LED_GREEN, HIGH); // LED AUS
  Serial.println("RUNNING");
  delay(500);
    digitalWrite(LED_GREEN, LOW);  // LED AN
  delay(500);

}