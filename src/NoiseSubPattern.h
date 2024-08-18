class NoiseSubPattern : public SubPattern {
private:
  Noise _noise;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t NOISE = 0;
  static const uint8_t FIRE = 1;
  static const uint8_t RIPPLE = 2;
  static const uint8_t PARTICLES = 3;

  NoiseSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case NOISE:
      globalSpeed = 9;
      globalWidth = 1;
      break;
    case FIRE:
    case RIPPLE:
    case PARTICLES:
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
    case RIPPLE:
      _noise.ripple();
      break;
    case PARTICLES:
      _noise.showParticles();
      break;
    default:
      break;
    }
  }
};
