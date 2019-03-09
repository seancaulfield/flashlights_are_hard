/*
 * wattsup.ino
 *
 * My own crappy version using a Polulu current sensor on a 328p feather with a
 * SparkFun OLED display. Runs off the battery supplied (assumed to be Li-ion).
 * No more than 5.5V!
 *
 * Author: Sean Caulfield <sean@yak.net>
 * License: GPLv2.0
 *
 */

#include <Arduino.h>
#include <Wire.h>
#include <SFE_MicroOLED.h>

const int       PIN_VSENSE   = A2;
const int       PIN_ISENSE   = A3;
const uint16_t  ADC_BITS     = (1<<10);
const float     ADC_REF_V    = 3.3;
const float     ADC_REF_I    = 3.3;
const float     VSENSE_R1    = 32570.0;
const float     VSENSE_R2    = 8070.0;
const float     V_COEFF      = (VSENSE_R1 + VSENSE_R2) / VSENSE_R2;
const float     I_COEFF      = 1.0 / 0.066;
const float     I_MIDDLE_V   = ADC_REF_I / 2;
const int       LOOP_DELAY   = 500;
const int       PIN_OLED_RST = -1;
const bool      DC_JUMPER    = true;

MicroOLED oled(PIN_OLED_RST, DC_JUMPER);

float reading2voltage(uint16_t reading, float vref) {
  return (((float)reading) / ADC_BITS) * vref;
}

float reading2current(uint16_t reading) {
  float v = reading2voltage(reading, ADC_REF_I);
  float offset = v - I_MIDDLE_V;
  return offset * I_COEFF;
}

void displayValues(float v, float i) {
  oled.clear(PAGE);
  
  oled.setCursor(0, 0);
  oled.print(v*1000.0, 0);
  oled.setCursor(44, 0);
  oled.print(F("mV"));

  oled.setCursor(0, 20);
  oled.print(i*1000.0, 0);
  oled.setCursor(44, 20);
  oled.print(F("mA"));

  oled.display();
}

void setup() {
  pinMode(PIN_VSENSE, INPUT);
  pinMode(PIN_ISENSE, INPUT);
  Wire.begin();
  oled.begin();
  oled.setFontType(1);
  displayValues(0.0, 0.0);
  Serial.begin(115200);
}

uint16_t v_reading = 0;
uint16_t i_reading = 0;
float voltage = 0.0;
float current = 0.0;

void loop() {

  //analogReference(INTERNAL);
  //delayMicroseconds(100);
  v_reading = analogRead(PIN_VSENSE);

  //analogReference(DEFAULT);
  //delayMicroseconds(100);
  i_reading = analogRead(PIN_ISENSE);
  
  Serial.print(v_reading);
  Serial.print(F(","));
  Serial.println(i_reading);

  voltage = reading2voltage(v_reading, ADC_REF_V) * V_COEFF;
  current = reading2current(i_reading);

  displayValues(voltage, current);

  delay(LOOP_DELAY);
}
