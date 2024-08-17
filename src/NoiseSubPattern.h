class NoiseSubPattern : public SubPattern {
private:
  Noise _noise;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t NOISE = 0;

  NoiseSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case NOISE:
      // setup
      break;
    default:
      break;
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case NOISE:
      _noise.setSpeed(
          mapf(globalSpeed, 1, 10, Noise::SPEED.MAX, Noise::SPEED.MIN)
      );
      _noise.setScale(
          mapf(globalWidth, 1, 10, Noise::SCALE.MAX, Noise::SCALE.MIN)
      );
      _noise.show();
      break;
    default:
      break;
    }
  }
};
