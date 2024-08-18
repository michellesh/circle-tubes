Timer randomizeTimer = {5000};

float _mapTimerToValue(float fromValue, float toValue) {
  return mapf(
      millis(), randomizeTimer.lastCycleTime,
      randomizeTimer.lastCycleTime + randomizeTimer.totalCycleTime, fromValue, toValue
  );
}

class NoiseSubPattern : public SubPattern {
private:
  Noise _noise;
  Noise _noiseNext;
  Noise _noisePrev;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t NOISE = 0;
  static const uint8_t FIRE = 1;

  NoiseSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case NOISE:
      globalSpeed = 9;
      globalWidth = 3;//1;
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
    _noise.setSpeed(
        mapf(globalSpeed, 1, 10, Noise::SPEED.MAX, Noise::SPEED.MIN)
    );
    _noise.setScale(
        mapf(globalWidth, 1, 10, Noise::SCALE.MAX, Noise::SCALE.MIN)
    );
    switch (_activeSubPattern) {
    case NOISE:
      if (randomizeTimer.complete()) {
        _noisePrev = _noise;
        _noiseNext._stretchVertical = float(random(50, 200)) / 100;
        Serial.print("_stretchVertical: ");
        Serial.println(_noiseNext._stretchVertical);
        _noiseNext._stretchHorizontal = float(random(50, 200)) / 100;
        Serial.print("_stretchHorizontal: ");
        Serial.println(_noiseNext._stretchHorizontal);
        _noiseNext._shiftVertical = float(random(0, 100)) / 100;
        Serial.print("_shiftVertical: ");
        Serial.println(_noiseNext._shiftVertical);
        _noiseNext._shiftHorizontal = float(random(0, 100)) / 100;
        Serial.print("_shiftHorizontal: ");
        Serial.println(_noiseNext._shiftHorizontal);
        randomizeTimer.reset();
      }

      _noise._stretchVertical = _mapTimerToValue(_noisePrev._stretchVertical, _noiseNext._stretchVertical);
      _noise._stretchHorizontal = _mapTimerToValue(_noisePrev._stretchHorizontal, _noiseNext._stretchHorizontal);
      //_noise._shiftVertical = _mapTimerToValue(_noisePrev._shiftVertical, _noiseNext._shiftVertical);
      //_noise._shiftHorizontal = _mapTimerToValue(_noisePrev._shiftHorizontal, _noiseNext._shiftHorizontal);

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
