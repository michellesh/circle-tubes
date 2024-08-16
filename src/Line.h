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

  float getSpeed() { return /*globalSpeed * */_speedMultiplier; }

  float getWidth() { return globalWidth * _widthMultiplier; }

  void show() {
    for (int i = 0; i < _path.length; i++) {
      //int y = _path.yValue[i] + _position;
      //if (y > YMAX) { y -= YMAX; }
      //int dist = y % int(getWidth() * 2);
      //int dist = _path.yValue[i] - _position;
      //dist = dist % int(getWidth() * 2);
      //if (_id == 7 && i == 7) {
      //  Serial.println(_position);
      //}
      //if (dist < getWidth() && dist > 0) {
      //  int hue = map(_path.yValue[i], 0, YMAX, 255, 0);
      //  _path.leds[i] = CHSV(hue, 200, BRIGHTNESS);
      //}
    }

    _position += getSpeed();
    if (_position > YMAX) {
      _position = -getWidth();
    }
  }
};
