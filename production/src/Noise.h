class Noise {
private:
  float _speed = SPEED.DFLT;      // How fast blobs move/evolve
  float _scale = SCALE.DFLT;      // Overall size of noise blobs
  float _stretchX = STRETCH.DFLT; // Stretch pattern in X direction
  float _stretchY = STRETCH.DFLT; // Stretch pattern in Y direction
  float _shiftX = SHIFT.MAX;      // Move pattern over time in X direction
  float _shiftY = SHIFT.MIN;      // Move pattern over time in Y direction

public:
  static constexpr Range SPEED = {3, 20, 10}; // 4.89
  static constexpr Range SCALE = {1, 20, 5};  // 15.78
  static constexpr Range STRETCH = {0.5, 2.0, 1.0};
  static constexpr Range SHIFT = {0, 1.0, 0};

  float getSpeed() { return _speed; }

  float getScale() { return _scale; }

  float getStretchX() { return _stretchX; }

  float getStretchY() { return _stretchY; }

  void setSpeed(float x) { _speed = x; }

  void setScale(float x) { _scale = x; }

  void setStretchX(float x) { _stretchX = x; }

  void setStretchY(float x) { _stretchY = x; }

  void setRandomValues() {
    _stretchX = randomFloat(STRETCH.MIN, STRETCH.MAX);
    _stretchY = randomFloat(STRETCH.MIN, STRETCH.MAX);
  }

  void setSpeedFromRange(float value, float from, float to) {
    _speed = mapf(value, from, to, SPEED.MAX, SPEED.MIN);
  }

  void setScaleFromRange(float value, float from, float to) {
    _scale = mapf(value, from, to, SCALE.MAX, SCALE.MIN);
  }

  void show() {
    float time = millis() / _speed;

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        float x = float(i) * _stretchX;
        float y = float(tubes[i].yValue[j]) * _stretchY;
        float noiseValue = inoise8(
            x * _scale + (time * _shiftX), y * _scale + (time * _shiftY), time
        );

//68 188
        uint8_t colorIndex = noiseValue;
        //uint8_t colorIndex =
        //    map(noiseValue, 0, 120, 0,
        //        100); // use smaller portion of the color palette
        //uint8_t brightnessValue = noiseValue;
        uint8_t brightnessValue =
            sin8(noiseValue) * 1.5; // increase brightness contrast

        //uint8_t colorIndex = noiseValue;
        //uint8_t brightnessValue = sin8(noiseValue);

        CRGB color = palette.colorFromPalette(colorIndex);
        tubes[i].leds[j] = color.nscale8(brightnessValue);
      }
    }
  }
};