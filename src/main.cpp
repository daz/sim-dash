#include <FastLED.h>

#define LED_TYPE           WS2811
#define LED_COLOR_ORDER    GRB
#define LED_MAX_BRIGHTNESS 255
#define LED_NUM_LEDS       120
#define LED_PIN            D2
#define SWITCH_PIN         D3
#define DIAL_PIN           A0

void update();

CHSV color;
CRGB leds[LED_NUM_LEDS];
bool switchState;

void setup() {
  pinMode(SWITCH_PIN, INPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, LED_COLOR_ORDER>(leds, LED_NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(LED_MAX_BRIGHTNESS);
}

void loop() {
  update();
  FastLED.show();
}

void update() {
  static bool firstRun = true;
  bool newSwitchState = (digitalRead(SWITCH_PIN) == HIGH);
  if (!firstRun && newSwitchState == switchState) {
    return;
  }

  firstRun = false;
  switchState = newSwitchState;

  uint8_t brightness = map(analogRead(DIAL_PIN), 0, 1023, 0, LED_MAX_BRIGHTNESS);

  if (switchState) {
    color.setHSV(0, 255, brightness);
  } else {
    color.setHSV(0, 255, brightness);
  }

  for (size_t i = 0; i < LED_NUM_LEDS; i++) {
    leds[i] = color;
  }
}
