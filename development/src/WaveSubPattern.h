#define MAX_WAVES 3

Timer waveTimer;

float mapTimerToValue(float fromValue, float toValue) {
  return mapf(
      millis(), waveTimer.lastCycleTime,
      waveTimer.lastCycleTime + waveTimer.totalCycleTime, fromValue, toValue
  );
}

class WaveSubPattern : public SubPattern {
private:
  Wave _waves[MAX_WAVES];
  uint8_t _numWaves = MAX_WAVES;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t THREE_WAVES = 0;
  static const uint8_t EVOLVING_WAVE = 1;

  WaveSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case THREE_WAVES:
      _numWaves = 3;
      for (int i = 0; i < _numWaves; i++) {
        _waves[i].setRandomValues();
      }
      break;
    case EVOLVING_WAVE:
      _numWaves = 1;
      _waves[0].setRandomValues(); // wave currently being displayed
      _waves[1] = _waves[0];       // for storing previous values
      _waves[2].setRandomValues(); // for storing values to transition to
      waveTimer.totalCycleTime = random(10000, 15000);
      waveTimer.reset();
      break;
    default:
      break;
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case THREE_WAVES:
      for (int i = 0; i < _numWaves; i++) {
        _waves[i].setColorIndex(map(i, 0, _numWaves, 0, 255));
        _waves[i].show();
      }
      break;
    case EVOLVING_WAVE: {
      // slowly transition to destination wave values
      _waves[0].setHeight(
          mapTimerToValue(_waves[1].getHeight(), _waves[2].getHeight())
      );
      _waves[0].setLength(
          mapTimerToValue(_waves[1].getLength(), _waves[2].getLength())
      );
      _waves[0].setWidth(
          mapTimerToValue(_waves[1].getWidth(), _waves[2].getWidth())
      );
      _waves[0].setColorIndex(
          mapTimerToValue(_waves[1].getColorIndex(), _waves[2].getColorIndex())
      );
      // when the timer is up, set new random values to transition to
      if (waveTimer.complete()) {
        _waves[1] = _waves[0];       // store previous values
        _waves[2].setRandomValues(); // values to transition to
        _waves[0].setSpeed(_waves[2].getSpeed());
        waveTimer.totalCycleTime = random(10000, 15000);
        waveTimer.reset();
      }
      _waves[0].show();
      break;
    }
    default:
      break;
    }
  }
};
