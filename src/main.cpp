// clang-format off
#include <Arduino.h>
#include <FastLED.h>

#include "Range.h"
#include "utils.h"

#include "Pattern.h"
#include "SubPattern.h"
// clang-format on

#define LED_TYPE NEOPIXEL
#define COLOR_ORDER GRB
#define BRIGHTNESS 255

#define LED_PIN 32

#define NUM_TUBES 23
#define NUM_LEDS_TOTAL 401

int NUM_LEDS[] = {4,  11, 14, 15, 18, 19, 20, 21, 22, 23, 22, 23,
                  22, 23, 22, 21, 20, 19, 18, 15, 14, 11, 4};

CRGB leds[NUM_LEDS_TOTAL];
int yValue[NUM_LEDS_TOTAL];
int yMax = 0;

struct Path {
  CRGB *leds;
  int *yValue;
  int length;
};

Path tubes[NUM_TUBES];

int globalSpeed = 5;
int globalDensity = 5;
int globalWidth = 5;

// clang-format off
#include "Button.h"

#include "Line.h"
#include "LineSubPattern.h"
// clang-format on

LineSubPattern linePattern(LineSubPattern::REPEATING_LINES);

// clang-format off
SubPattern *activePatterns[] = {
  &linePattern,
};
uint8_t activePatternIndex = 0;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("TEST!");

  setupButton();

  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS_TOTAL);
  FastLED.setBrightness(BRIGHTNESS);

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
      float halfwayIndex = float(tubes[i].length - 1) / 2;
      tubes[i].yValue[j] = (halfwayIndex - j) * -2;
      yMax = tubes[i].yValue[j] > yMax ? tubes[i].yValue[j] : yMax;
    }
  }
}

void loop() {
  FastLED.clear();

  handleButton();

  // If new pattern was selected, setup new pattern
  static int prevActivePatternIndex = -1;
  if (prevActivePatternIndex != activePatternIndex) {
    activePatterns[activePatternIndex]->setup();
    prevActivePatternIndex = activePatternIndex;
  }

  activePatterns[activePatternIndex]->show();

  FastLED.setBrightness(120);
  FastLED.show();
}
