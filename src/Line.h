class Line : public Pattern {
private:
  uint8_t _id;
  float _speedMultiplier = 1.0;
  float _widthMultiplier = 1.0;
  float _densityMultiplier = 1.0;
  float _position = -yMax;
  Path _path;

  uint8_t _getBrightness() {}

public:
  void setSpeedMultiplier(float x) { _speedMultiplier = x; }

  void setWidthMultiplier(float x) { _widthMultiplier = x; }

  void setDensityMultiplier(float x) { _densityMultiplier = x; }

  void setPosition(float x) { _position = x; }

  void setPath(Path path) { _path = path; }

  float getSpeed() { return /*globalSpeed * */_speedMultiplier; }

  float getWidth() { return globalWidth * _widthMultiplier; }

  void show() {
    for (int i = 0; i < _path.length; i++) {
      float dist = _position - _path.yValue[i];
      if (dist < getWidth() && dist > 0) {
        int hue = map(_path.yValue[i], -yMax, yMax, 255, 0);
        _path.leds[i] = CHSV(hue, 200, BRIGHTNESS);
      }
    }

    _position += getSpeed();
    if (_position > yMax + getWidth()) {
      _position = -yMax;
    }
  }
};
