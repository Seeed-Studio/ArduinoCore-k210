#include <Arduino.h>
#include <Ticker.h>

// attach a LED to pPIO 21
#define LED_PIN 21

Ticker blinker;


int blink() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  blinker.attach(100, blink);
}

void loop() {
  
}
