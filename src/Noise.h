class Noise : public Pattern {
private:
  float _speed = SPEED.DFLT;
  float _scale = SCALE.DFLT;
  uint8_t _colorIndex = 0;

public:
  static constexpr Range SPEED = {3, 20, 10}; // 4.89
  static constexpr Range SCALE = {1, 20, 5};  // 15.78
  static constexpr Range STRETCH = {0.5, 2.0, 1.0};
  static constexpr Range SHIFT = {0, 1.0, 0};

  float stretchX = 1;        // float(beatsin8(30, 5, 20)) / 10;
  float stretchY = 1;        // float(beatsin8(30, 5, 20)) / 10;
  float shiftVertical = 0;   // float(beatsin8(30, 0, 10)) / 10;
  float shiftHorizontal = 1; // float(beatsin8(30, 0, 10)) / 10;

  float getSpeed() { return _speed; }

  float getScale() { return _scale; }

  void setSpeed(float x) { _speed = x; }

  void setScale(float x) { _scale = x; }

  void setRandomValues() {
    stretchX = randomFloat(STRETCH.MIN, STRETCH.MAX);
    stretchY = randomFloat(STRETCH.MIN, STRETCH.MAX);
  }

  void setSpeedFromRange(float value, float from, float to) {
    _speed = mapf(value, from, to, SPEED.MAX, SPEED.MIN);
  }

  void setScaleFromRange(float value, float from, float to) {
    _scale = mapf(value, from, to, SCALE.MAX, SCALE.MIN);
  }

  void show() {
    float time = millis() / _speed; // millis()/10 good

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        float x = float(i) * stretchX;
        float y = float(tubes[i].yValue[j]) * stretchY;
        float noiseValue = inoise8(
            x * _scale + (time * shiftHorizontal),
            y * _scale + (time * shiftVertical), time
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