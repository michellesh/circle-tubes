class Wave : public Pattern {
private:
  int _height = HEIGHT.DFLT;
  int _speed = SPEED.DFLT;
  float _length = LENGTH.DFLT;
  int _width = WIDTH.DFLT;
  CRGB _color;

public:
  static constexpr Range HEIGHT = {5, 18, 10};
  static constexpr Range SPEED = {1, 5, 2};
  static constexpr Range LENGTH = {0.2, 0.5, 0.3};
  static constexpr Range WIDTH = {1, 6, 3};

  void setHeight(int x) { _height = x; }

  void setSpeed(int x) { _speed = x; }

  void setLength(float x) { _length = x; }

  void setWidth(int x) { _width = x; }

  void setColor(CRGB x) { _color = x; }

  float getValue(int tubeIndex) {
    float offset = tubeIndex * _length;
    return mapf(
        sin((ticks * _speed) + offset), -1, 1, YMAX / 2 - _height,
        YMAX / 2 + _height
    );
  }

  void show() {
    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        float position = getValue(i);
        float dist = abs(position - tubes[i].yValue[j]);
        if (dist < _width) {
          tubes[i].leds[j] = _color;
          tubes[i].leds[j].nscale8(mapf(dist, 0, _width, 255, 0));
        }
      }
    }
  }
};
