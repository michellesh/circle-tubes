#include <FastLED.h>

#define LED_TYPE NEOPIXEL
#define COLOR_ORDER GRB
#define BRIGHTNESS 255

#define LED_PIN 32
#define BUTTON_PIN 4

#define NUM_TUBES 23
#define NUM_LEDS_TOTAL 401

int NUM_LEDS[] = {4,  11, 14, 15, 18, 19, 20, 21, 22, 23, 22, 23,
                  22, 23, 22, 21, 20, 19, 18, 15, 14, 11, 4};

CRGB leds[NUM_LEDS_TOTAL];

struct Button {
  int pin;
  bool pressed;
};

struct Tube {
  CRGB *leds;
  int length;
};

Button button = {BUTTON_PIN};
Tube tubes[NUM_TUBES];

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(button.pin, INPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS_TOTAL);
  FastLED.setBrightness(BRIGHTNESS);

  int offset = 0;
  for (int i = 0; i < NUM_TUBES; i++) {
    Tube tube = {&leds[offset], NUM_LEDS[i]};
    tubes[NUM_TUBES - 1 - i] = tube;
    offset += tube.length;
  }
}

void loop() {
  FastLED.clear();

  checkButtonPressed();

  for (int i = 0; i < NUM_TUBES; i++) {
    int hue = map(i, 0, NUM_TUBES, 255, 0);
    for (int j = 0; j < tubes[i].length; j++) {
      tubes[i].leds[j] = CHSV(hue, 200, BRIGHTNESS);
    }
  }

  FastLED.setBrightness(150);
  FastLED.show();
}
