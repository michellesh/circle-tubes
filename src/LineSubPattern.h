#define MAX_LINES NUM_TUBES

struct Wave {
  int yMin;
  int yMax;
  int speed;
  float height;

  float getValue(int index) {
    float offset = index * height;
    return mapf(sin((ticks * speed) + offset), -1, 1, yMin, yMax);
  }
};
Wave wave = {YMAX / 2 - 10, YMAX / 2 + 10, 2, 0.3};

class LineSubPattern : public SubPattern {
private:
  Line _lines[MAX_LINES];
  uint8_t _numLines = MAX_LINES;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t REPEATING_LINES = 0;
  static const uint8_t SINE_WAVE = 1;

  LineSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case REPEATING_LINES:
    case SINE_WAVE:
      _numLines = NUM_TUBES;
      for (int i = 0; i < _numLines; i++) {
        _lines[i] = Line(i);
        _lines[i].setPath(tubes[i]);
      }
      break;
    default:
      break;
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case REPEATING_LINES:
      for (int i = 0; i < _numLines; i++) {
        _lines[i].showRepeat();
      }
      break;
    case SINE_WAVE: {
      wave.speed = mapf(globalSpeed, 1, 10, 1, 5);
      wave.height = mapf(globalOffset, 1, 10, 0.1, 1);
      for (int i = 0; i < _numLines; i++) {
        float position = wave.getValue(i);
        _lines[i].setOffset(position);
        _lines[i].show();
      }
      break;
    }
    default:
      break;
    }
  }
};
