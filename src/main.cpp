#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <SPI.h>
#include <RadioLib.h>

#define WAKE_PIN D0

// Wio-SX1262 (LLCC68)
#define LORA_CS    D4
#define LORA_DIO1  D1
#define LORA_RST   D2
#define LORA_BUSY  D3


LLCC68 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);

// =====================================================

void enterSystemOff() {

  // Sleep mode for SX1262
  radio.standby();
  delay(5);
  radio.sleep();
  delay(5);

  //nrf52840 deep sleep mode
  NRF_POWER->SYSTEMOFF = 1;
  while (1);
}

// =====================================================

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("System On");
  pinMode(LED_GREEN, OUTPUT);

  Serial.println("Before begin()");

  int state = radio.begin(868.0);

  Serial.println("After begin()"); 
  radio.setOutputPower(12);

  Serial.print("State: ");
  Serial.println(state);
}

// =====================================================

void loop() {

  // 3x blinking
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }

  // sending through tx for 5s just to increase current comsumption 
  Serial.println("Start Continuous TX");
  radio.standby();  // prepare LoRa mode
  radio.transmitDirect(); // starting continuous wave
  delay(5000);   

  //Now go to deep sleep
  Serial.println("Going into Deep Sleep System OFF");
  enterSystemOff();
}
