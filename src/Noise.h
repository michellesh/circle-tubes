class Noise : public Pattern {
private:
  float _speed = SPEED.DFLT;
  float _scale = SCALE.DFLT;
  uint8_t _colorIndex = 0;

public:
  static constexpr Range SPEED = {3, 15, 10};
  static constexpr Range SCALE = {5, 15, 12};

  float getSpeed() { return _speed; }

  float getScale() { return _scale; }

  void setSpeed(float x) { _speed = x; }

  void setScale(float x) { _scale = x; }

  void setColorIndex(uint8_t x) { _colorIndex = x; }

  void show() {
    float time = millis() / _speed; // millis()/10 good

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        int x = i;
        int y = tubes[i].yValue[j];
        float noiseValue = inoise8(x * _scale, y * _scale, time);
        // CRGB color = CHSV(noiseValue * 255, 255, BRIGHTNESS);
        // CRGB color = CHSV(HUE_BLUE, 150, noiseValue * BRIGHTNESS);
        uint8_t brightness = noiseValue * BRIGHTNESS;
        CRGB color = palette.mapToColor(brightness, 0, BRIGHTNESS);
        tubes[i].leds[j] = color.nscale8(brightness);
      }
    }
  }
};