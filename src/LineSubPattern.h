#define MAX_LINES NUM_TUBES

class LineSubPattern : public SubPattern {
private:
  Line _lines[MAX_LINES];
  uint8_t _numLines = MAX_LINES;
  uint8_t _activeSubPattern = 0;

public:
  static const uint8_t REPEATING_LINES = 0;

  LineSubPattern(uint8_t x = 0) { _activeSubPattern = x; }

  void setup() {
    switch (_activeSubPattern) {
    case REPEATING_LINES:
      _numLines = NUM_TUBES;
      for (int i = 0; i < _numLines; i++) {
        _lines[i] = Line(i);
        _lines[i].setPath(tubes[i]);
        _lines[i].setSpeedMultiplier(0.1);
      }
      break;
    default:
      break;
    }
  }

  virtual void show() {
    for (int i = 0; i < _numLines; i++) {
      _lines[i].show();
    }
  }
};
