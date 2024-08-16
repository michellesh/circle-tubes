class Line : public Pattern {
private:
  uint8_t _id;
  float _speed = SPEED.DFLT;
  float _width = WIDTH.DFLT;
  float _position = 0;
  Path _path;

  uint8_t _getBrightness() {}

public:
  Line(uint8_t id = 0) { _id = id; }

  static constexpr Range SPEED = {0.01, 1, 0.1};
  static constexpr Range WIDTH = {5, 20, 10};

  void setPosition(float x) { _position = x; }

  void setPath(Path path) { _path = path; }

  float getSpeed() { return mapf(globalSpeed, 1, 10, SPEED.MIN, SPEED.MAX); }

  float getWidth() { return mapf(globalWidth, 1, 10, WIDTH.MIN, WIDTH.MAX); }

  void show(float offset = 0) {
    float width = getWidth();
    int numLines = floor((YMAX + width) / (width * 2));
    if (numLines == 0) { numLines = 1; }
    int increment = (YMAX + width) / numLines;

    for (int p = 0; p < numLines; p++) {
      float linePosition = (p * increment) + _position + offset;
      if (linePosition > YMAX + width) { linePosition -= YMAX + width; }
      for (int j = 0; j < _path.length; j++) {
        float dist = linePosition - _path.yValue[j];
        if (dist <= width && dist >= 0) {
          _path.leds[j] = CRGB::Blue;
          _path.leds[j].nscale8(mirrorFade(mapf(dist, 0, width, 255, 0)));
        }
      }
    }

    _position += getSpeed() * (globalReverse ? -1 : 1);
    if (_position > YMAX + width) {
      _position = 0;
    } else if (_position < 0) {
      _position = YMAX + width;
    }
  }
};
