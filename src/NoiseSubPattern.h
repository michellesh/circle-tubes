class NoiseSubPattern : public SubPattern {
private:
  Noise _noise;
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
