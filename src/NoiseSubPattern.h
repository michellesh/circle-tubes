class NoiseSubPattern : public SubPattern {
private:
  Noise _noise;
  Noise _noiseNext;
  Noise _noisePrev;
  uint8_t _activeSubPattern = 0;
  Timer _timer = {5000}; // timer to randomize new values

  float _mapTimerToValue(float fromValue, float toValue) {
    return mapf(
        millis(), _timer.lastCycleTime,
        _timer.lastCycleTime + _timer.totalCycleTime, fromValue, toValue
    );
  }

public:
  static const uint8_t NOISE = 0;
  static const uint8_t FIRE = 1;

  NoiseSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case NOISE:
      globalSpeed = 9;
      globalWidth = 3; // 1;
      break;
    case FIRE:
      globalSpeed = 9;
      globalWidth = 2;
      globalOffset = 5;
    default:
      break;
    }
  }

  virtual void show() {
    _noise.setSpeedFromRange(globalSpeed, 1, 10);
    _noise.setScaleFromRange(globalWidth, 1, 10);
    //_noise.setSpeed(mapf(globalSpeed, 1, 10, Noise::SPEED.MAX,
    //Noise::SPEED.MIN)
    //);
    //_noise.setScale(mapf(globalWidth, 1, 10, Noise::SCALE.MAX,
    //Noise::SCALE.MIN)
    //);
    switch (_activeSubPattern) {
    case NOISE:
      if (_timer.complete()) {
        _noisePrev = _noise;
        //_noiseNext.stretchX = float(random(50, 200)) / 100;
        //_noiseNext.stretchY = float(random(50, 200)) / 100;
        _noiseNext.setRandomValues();
        _timer.reset();
      }

      _noise.stretchX =
          _mapTimerToValue(_noisePrev.stretchX, _noiseNext.stretchX);
      _noise.stretchY =
          _mapTimerToValue(_noisePrev.stretchY, _noiseNext.stretchY);

      _noise.show();
      break;
    case FIRE:
      _noise.fire();
      break;
    default:
      break;
    }
  }
};
