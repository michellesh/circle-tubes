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
int YMAX = 44; // (max(NUM_LEDS) - 1) * 2

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
      int yMaxTube = ((tubes[i].length - 1) * 2);
      tubes[i].yValue[j] = (YMAX - yMaxTube) / 2 + (j * 2);
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

  //activePatterns[activePatternIndex]->show();


  int width = 5;
  static float position = 0;
  int numLines = floor((YMAX + width) / (width * 2));
  if (numLines == 0) { numLines = 1; }
  int increment = (YMAX + width) / numLines;

  for (int i = 0; i < NUM_TUBES; i++) {
    for (int p = 0; p < numLines; p++) {
      float linePosition = (p * increment) + position;
      if (linePosition > YMAX + width) { linePosition -= YMAX + width; }
      for (int j = 0; j < tubes[i].length; j++) {
        float dist = linePosition - tubes[i].yValue[j];
        if (dist < width && dist > 0) {
          //int hue = map(_path.yValue[i], 0, YMAX, 255, 0);
          tubes[i].leds[j] = CRGB::Blue;
          tubes[i].leds[j].nscale8(map(dist, 0, width, 255, 0));
        }
      }
    }
  }

  position += 0.1;
  if (position > YMAX + width) {
    position = 0;
  }

  FastLED.setBrightness(120);
  FastLED.show();
}
