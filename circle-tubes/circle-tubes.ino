#include <FastLED.h>

#define LED_TYPE NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS 160
#define BRIGHTNESS 255

#define LED_PIN 13
#define BUTTON_PIN 4

CRGB leds[NUM_LEDS];

struct Button {
  int pin;
  bool pressed;
};

Button button = {BUTTON_PIN};

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(BUTTON_PIN, INPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  FastLED.clear();

  checkButtonPressed();

  for (int i = 0; i < NUM_LEDS; i++) {
    int hue = map(i, 0, NUM_LEDS, 255, 0);
    leds[i] = CHSV(hue, 255, BRIGHTNESS);
  }

  FastLED.show();
}
