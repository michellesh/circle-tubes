// clang-format off
#include <Arduino.h>
#include <FastLED.h>

#include "Range.h"
#include "Timer.h"
#include "utils.h"
#include "Palette.h"

#include "SubPattern.h"
// clang-format on

#define LED_TYPE NEOPIXEL
#define COLOR_ORDER GRB
#define LED_PIN 32

#define NUM_TUBES 23
#define NUM_LEDS_TOTAL 401

int NUM_LEDS[] = {4,  11, 14, 15, 18, 19, 20, 21, 22, 23, 22, 23,
                  22, 23, 22, 21, 20, 19, 18, 15, 14, 11, 4};

CRGB leds[NUM_LEDS_TOTAL];
int yValue[NUM_LEDS_TOTAL];
int YMAX = 44; // (max(NUM_LEDS) - 1) * 2
Palette palette;

struct Path {
  CRGB *leds;
  int *yValue;
  int length;
};

Path tubes[NUM_TUBES];

int globalSpeed = 5;
int globalOffset = 5;
int globalWidth = 5;
bool globalReverse = 0;
uint8_t brightnessIncrement = 50; // 50 for 5x brightness increments
uint8_t globalBrightness =
    (255 / brightnessIncrement) / 2 *
    brightnessIncrement; // set initial brightness to half of max brightness
uint8_t globalFade = 100;

// clang-format off
#include "Button.h"

#include "Noise.h"
#include "NoiseSubPattern.h"
// clang-format on

NoiseSubPattern noise(NoiseSubPattern::NOISE);

SubPattern *activePatterns[] = {&noise};
uint8_t activePatternIndex = 0;

#include "web_server.h"

void setup() {
  Serial.begin(9600);
  delay(500);

  setupButton();

  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS_TOTAL);

  // set pointer to starting point in array for each tube
  int offset = 0;
  for (int i = 0; i < NUM_TUBES; i++) {
    Path path = {&leds[offset], &yValue[offset], NUM_LEDS[i]};
    tubes[NUM_TUBES - 1 - i] = path;
    offset += path.length;
  }

  // calculate y values
  for (int i = 0; i < NUM_TUBES; i++) {
    for (int j = 0; j < tubes[i].length; j++) {
      int yMaxTube = ((tubes[i].length - 1) * 2);
      tubes[i].yValue[j] = (YMAX - yMaxTube) / 2 + (j * 2);
    }
  }

  setupWebServer();
}

void loop() {
  // FastLED.clear();
  fadeToBlackBy(leds, NUM_LEDS_TOTAL, globalFade);
  palette.cycle();

  handleButton();

  // If new pattern was selected, setup new pattern
  static int prevActivePatternIndex = -1;
  if (prevActivePatternIndex != activePatternIndex) {
    activePatterns[activePatternIndex]->setup();
    prevActivePatternIndex = activePatternIndex;
  }

  activePatterns[activePatternIndex]->show();

  FastLED.setBrightness(globalBrightness);
  FastLED.show();
}