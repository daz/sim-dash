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
bool configMode = false;

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
  bool newSwitchState = (digitalRead(SWITCH_PIN) == HIGH);
  uint16_t dialValue = analogRead(DIAL_PIN);


  switchState = newSwitchState;

  if (switchState) {
    color.hue = 0;
    color.saturation = 255;
    color.value = map(dialValue, 0, 1023, 0, LED_MAX_BRIGHTNESS);
  } else {
    color.setHSV(0, 255, 0);
  }

  for (size_t i = 0; i < LED_NUM_LEDS; i++) {
    leds[i] = color;
  }
}
