class Line : public Pattern {
private:
  uint8_t _id;
  float _speed = SPEED.DFLT;
  float _length = LENGTH.DFLT;
  float _position = -yMax;
  Path _path;

  uint8_t _getBrightness() {}

public:
  static constexpr Range SPEED = {0.1, 10, 1};
  static constexpr Range LENGTH = {1, 10, 5};

  void setSpeed(float speed) { _speed = speed; }

  void setLength(float length) { _length = length; }

  void setPath(Path path) { _path = path; }

  void show() {
    for (int i = 0; i < _path.length; i++) {
      if (abs(_position - _path.yValue[i]) < _length) {
        int hue = map(_path.yValue[i], -yMax, yMax, 255, 0);
        _path.leds[i] = CHSV(hue, 200, BRIGHTNESS);
      }
    }

    _position += _speed;
    if (_position > yMax) {
      _position = -yMax;
    }
  }
};
