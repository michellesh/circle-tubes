class Line : public Pattern {
private:
  uint8_t _id;
  float _speedMultiplier = 1.0;
  float _widthMultiplier = 1.0;
  float _densityMultiplier = 1.0;
  float _position = 0;
  Path _path;

  uint8_t _getBrightness() {}

public:
  Line(uint8_t id = 0) { _id = id; }

  void setSpeedMultiplier(float x) { _speedMultiplier = x; }

  void setWidthMultiplier(float x) { _widthMultiplier = x; }

  void setDensityMultiplier(float x) { _densityMultiplier = x; }

  void setPosition(float x) { _position = x; }

  void setPath(Path path) { _path = path; }

  float getSpeed() { return globalSpeed * _speedMultiplier; }

  float getWidth() { return globalWidth * _widthMultiplier; }

  void show() {
    float width = getWidth();
    int numLines = floor((YMAX + width) / (width * 2));
    if (numLines == 0) { numLines = 1; }
    int increment = (YMAX + width) / numLines;

    for (int p = 0; p < numLines; p++) {
      float linePosition = (p * increment) + _position;
      if (linePosition > YMAX + width) { linePosition -= YMAX + width; }
      for (int j = 0; j < _path.length; j++) {
        float dist = linePosition - _path.yValue[j];
        if (dist <= width && dist >= 0) {
          _path.leds[j] = CRGB::Blue;
          _path.leds[j].nscale8(mirrorFade(mapf(dist, 0, width, 255, 0)));
        }
      }
    }

    _position += getSpeed();
    if (_position > YMAX + width) {
      _position = 0;
    }
  }
};
