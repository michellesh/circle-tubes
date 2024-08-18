#define NUM_PARTICLES 50
struct XY {
  float x;
  float y;
};
XY _particles[NUM_PARTICLES];

class Noise : public Pattern {
private:
  float _speed = SPEED.DFLT;
  float _scale = SCALE.DFLT;
  uint8_t _colorIndex = 0;

public:
  static constexpr Range SPEED = {3, 20, 10};
  static constexpr Range SCALE = {1, 20, 5};

  Range rangeStretch = {0.5, 2.0, 1.0};
  Range rangeShift = {0, 1.0, 0};

  float _stretchVertical = 1;   // float(beatsin8(30, 5, 20)) / 10;
  float _stretchHorizontal = 1; // float(beatsin8(30, 5, 20)) / 10;
  float _shiftVertical = 0;     // float(beatsin8(30, 0, 10)) / 10;
  float _shiftHorizontal = 1;   // float(beatsin8(30, 0, 10)) / 10;

  float getSpeed() { return _speed; }

  float getScale() { return _scale; }

  void setSpeed(float x) { _speed = x; }

  void setScale(float x) { _scale = x; }

  void setColorIndex(uint8_t x) { _colorIndex = x; }

  void show() {
    float time = millis() / _speed; // millis()/10 good

    // TODO
    // Add variables that slowly transitio over time for:
    //
    // int x = i * stretchVertical; // somevalue 0.5-2
    // int y = tubes[i].yValue[j] * stretchHorizontal;
    //
    //   float shiftHorizontal = time * (somevalue 0-1)
    //   float shiftVertical = time * (somevalue 0-1)
    //   inoise8(x * _scale + shiftHorizontal,
    //           y * _scale + shiftVertical,
    //           time);

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        float x = float(i) * _stretchVertical;
        float y = float(tubes[i].yValue[j]) * _stretchHorizontal;
        float noiseValue = inoise8(
            x * _scale + (time * _shiftHorizontal),
            y * _scale + (time * _shiftVertical), time
        );
        uint8_t colorIndex =
            map(noiseValue, 0, 120, 0,
                100); // use smaller portion of the color palette
        CRGB color = palette.colorFromPalette(colorIndex);
        uint8_t brightnessValue =
            sin8(noiseValue) * 1.5; // increase brightness contrast
        tubes[i].leds[j] = color.nscale8(brightnessValue);
      }
    }
  }

  void fire() {
    float time = millis();

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        int x = i;
        int y = YMAX - tubes[i].yValue[j];
        uint8_t colorIndex = qsub8(
            inoise8(x * 60, y * 60 + time, time / 3),
            abs8(y - YMAX) * 255 / YMAX
        );
        tubes[i].leds[j] = palette.colorFromPalette(colorIndex);
        tubes[i].leds[j].nscale8(colorIndex);
      }
    }
  }
};