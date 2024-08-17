#define MAX_WAVES 3

class WaveSubPattern : public SubPattern {
private:
  Wave _waves[MAX_WAVES];
  uint8_t _numWaves = MAX_WAVES;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t SINE_WAVE = 0;

  WaveSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case SINE_WAVE:
      _numWaves = 3;
      for (int i = 0; i < _numWaves; i++) {
        _waves[i].setHeight(
            mapf(random(1, 11), 1, 11, Wave::HEIGHT.MIN, Wave::HEIGHT.MAX)
        );
        _waves[i].setLength(
            mapf(random(1, 11), 1, 11, Wave::LENGTH.MIN, Wave::LENGTH.MAX)
        );
        _waves[i].setWidth(
            mapf(random(1, 11), 1, 11, Wave::WIDTH.MIN, Wave::WIDTH.MAX)
        );
      }
      break;
    default:
      break;
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case SINE_WAVE: {
      for (int i = 0; i < _numWaves; i++) {
        _waves[i].setColor(palette.mapToColor(i, 0, _numWaves));
        _waves[i].show();
      }
      break;
    }
    default:
      break;
    }
  }
};
