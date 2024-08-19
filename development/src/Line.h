class Line : public Pattern {
private:
  uint8_t _id;
  float _speed = SPEED.DFLT;
  float _width = WIDTH.DFLT;
  float _offset = OFFSET.DFLT;
  float _position = 0;
  Path _path;

public:
  Line(uint8_t id = 0) { _id = id; }

  static constexpr Range SPEED = {0.01, 1, 0.1};
  static constexpr Range WIDTH = {5, 20, 10};
  static constexpr Range OFFSET = {0, 10, 0};

  void setOffset(float x) { _offset = x; }

  void setPath(Path path) { _path = path; }

  float getSpeed() { return mapf(globalSpeed, 1, 10, SPEED.MIN, SPEED.MAX); }

  float getWidth() { return mapf(globalWidth, 1, 10, WIDTH.MIN, WIDTH.MAX); }

  float getOffset() {
    return mapf(globalOffset, 1, 10, OFFSET.MIN, OFFSET.MAX);
  }

  void showRepeat() {
    float width = getWidth();
    int numLines = floor((YMAX + width) / (width * 2));
    if (numLines == 0) {
      numLines = 1;
    }
    int increment = (YMAX + width) / numLines;

    for (int p = 0; p < numLines; p++) {
      float linePosition = (p * increment) + _position + _offset;
      linePosition = modf(linePosition, int(YMAX + width));
      for (int j = 0; j < _path.length; j++) {
        float dist = linePosition - _path.yValue[j];
        if (dist <= width && dist >= 0) {
          _path.leds[j] = palette.mapToColor(_path.yValue[j], 0, YMAX);
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
