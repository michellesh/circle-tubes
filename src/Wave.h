class Wave : public Pattern {
private:
  float _height = HEIGHT.DFLT;
  float _speed = SPEED.DFLT;
  float _length = LENGTH.DFLT;
  float _width = WIDTH.DFLT;
  uint8_t _colorIndex = 0;

public:
  static constexpr Range HEIGHT = {5, 18, 10};
  static constexpr Range SPEED = {1, 5, 2};
  static constexpr Range LENGTH = {0.1, 0.8, 0.3};
  static constexpr Range WIDTH = {1, 10, 3};

  void setRandomValues() {
    _height = mapf(random(1, 11), 1, 11, HEIGHT.MIN, HEIGHT.MAX);
    _length = mapf(random(1, 11), 1, 11, LENGTH.MIN, LENGTH.MAX);
    _width = mapf(random(1, 11), 1, 11, WIDTH.MIN, WIDTH.MAX);
    _colorIndex = random(255);
  }

  float getHeight() { return _height; }

  float getSpeed() { return _speed; }

  float getLength() { return _length; }

  float getWidth() { return _width; }

  uint8_t getColorIndex() { return _colorIndex; }

  void setHeight(float x) { _height = x; }

  void setSpeed(float x) { _speed = x; }

  void setLength(float x) { _length = x; }

  void setWidth(float x) { _width = x; }

  void setColorIndex(uint8_t x) { _colorIndex = x; }

  float getValue(int tubeIndex) {
    float offset = tubeIndex * _length;
    return mapf(
        sin((ticks * _speed) + offset), -1, 1, YMAX / 2 - _height,
        YMAX / 2 + _height
    );
  }

  void show() {
    for (int i = 0; i < NUM_TUBES; i++) {
      float position = getValue(i);
      position = modf(position, YMAX);
      for (int j = 0; j < tubes[i].length; j++) {
        float dist = abs(position - tubes[i].yValue[j]);
        if (dist < _width) {
          tubes[i].leds[j] = palette.colorFromPalette(_colorIndex);
          tubes[i].leds[j].nscale8(mapf(dist, 0, _width, 255, 0));
        }
      }
    }
  }
};