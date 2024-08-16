#define MAX_LINES NUM_TUBES

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
      static float t = 0;
      for (int i = 0; i < _numLines; i++) {
        float offset = i * 0.3;
        float position =
            mapf(sin((t * 2) + offset), -1, 1, YMAX / 2 - 10, YMAX / 2 + 10);
        _lines[i].setOffset(position);
        _lines[i].show();
      }
      t += 0.01;
      break;
    }
    default:
      break;
    }
  }
};
