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
int yValue[NUM_LEDS_TOTAL];
int yMax = 0;

struct Button {
  int pin;
  bool pressed;
};

struct Tube {
  CRGB *leds;
  int *yValue;
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

  // set pointer to starting point in array for each tube
  int offset = 0;
  for (int i = 0; i < NUM_TUBES; i++) {
    Tube tube = {&leds[offset], &yValue[offset], NUM_LEDS[i]};
    tubes[NUM_TUBES - 1 - i] = tube;
    offset += tube.length;
  }

  // calculate y values
  for (int i = 0; i < NUM_TUBES; i++) {
    for (int j = 0; j < tubes[i].length; j++) {
      float halfwayIndex = float(tubes[i].length - 1) / 2;
      tubes[i].yValue[j] = (halfwayIndex - j) * 2;
      yMax = tubes[i].yValue[j] > yMax ? tubes[i].yValue[j] : yMax;
    }
  }
}

void loop() {
  FastLED.clear();

  checkButtonPressed();

  int line = beatsin8(30, 0, yMax * 2);
  line -= yMax;

  for (int i = 0; i < NUM_TUBES; i++) {
    for (int j = 0; j < tubes[i].length; j++) {
      int hue = map(tubes[i].yValue[j], -yMax, yMax, 255, 0);
      if (abs(line - tubes[i].yValue[j]) < 2) {
        tubes[i].leds[j] = CHSV(hue, 200, BRIGHTNESS);
      }
    }
  }

  FastLED.setBrightness(120);
  FastLED.show();
}
