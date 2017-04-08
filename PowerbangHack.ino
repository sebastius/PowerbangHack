// Powerbang HACK
// https://revspace.nl/Powerbank
// https://muxtronics.nl/powerbank.html
//
// For ATTiny85
//
// Sebastius Revspace

// To get an AT Tiny programmed use https://github.com/damellis/attiny

#include <TinyWireM.h> // https://github.com/adafruit/TinyWireM
#include <avr/sleep.h>

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)

void setup() {
  TinyWireM.begin();
  adc_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void sleep1s() {
  sleep_enable();
  sleep_cpu();
}

void loop() {
  TinyWireM.beginTransmission(0x6B);
  TinyWireM.write(0x02); // REG02
  TinyWireM.write(0xBC); // 3A charging
  TinyWireM.endTransmission();

  TinyWireM.beginTransmission(0x6B);
  TinyWireM.write(0x05); // REG05
  TinyWireM.write(0b10011110); // 20hrs charging
  TinyWireM.endTransmission();
  
  sleep1s();
}
