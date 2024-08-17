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
      _noise.show();
      break;
    default:
      break;
    }
  }
};
