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

  NoiseSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case NOISE:
      globalSpeed = 9;
      globalWidth = 3;
      break;
    default:
      break;
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case NOISE:
      _noise.setSpeedFromRange(globalSpeed, 1, 10);
      _noise.setScaleFromRange(globalWidth, 1, 10);
      _noise.setStretchX(
          _mapTimerToValue(_noisePrev.getStretchX(), _noiseNext.getStretchX())
      );
      _noise.setStretchY(
          _mapTimerToValue(_noisePrev.getStretchY(), _noiseNext.getStretchY())
      );

      if (_timer.complete()) {
        _noisePrev = _noise;
        _noiseNext.setRandomValues();
        _timer.reset();
      }

      _noise.show();
      break;
    default:
      break;
    }
  }
};
