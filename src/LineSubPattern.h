#define MAX_LINES NUM_TUBES
#define NUM_WAVES 3

Range WAVE_HEIGHT = {5, 18, 10};
Range WAVE_SPEED = {1, 5, 2};
Range WAVE_LENGTH = {0.2, 0.5, 0.3};
Range WAVE_WIDTH = {1, 6, 3};

struct Wave {
  int height;
  int speed;
  float length;
  int width;
  CRGB color;

  float getValue(int index) {
    float offset = index * length;
    return mapf(sin((ticks * speed) + offset), -1, 1, YMAX / 2 - height, YMAX / 2 + height);
  }
};
Wave wave1 = {10, 2, 0.3, 3, CRGB::Blue};
Wave wave2 = {10, 2, 0.3, 3, CRGB::Green};
Wave wave3 = {10, 2, 0.3, 3, CRGB::Yellow};
Wave waves[] = {wave1, wave2, wave3};

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
      _numLines = NUM_TUBES;
      for (int i = 0; i < _numLines; i++) {
        _lines[i] = Line(i);
        _lines[i].setPath(tubes[i]);
      }
    case SINE_WAVE:
      _numLines = NUM_TUBES;
      for (int i = 0; i < _numLines; i++) {
        _lines[i] = Line(i);
        _lines[i].setPath(tubes[i]);
      }
      for (int i = 0; i < NUM_WAVES; i++) {
        waves[i].height = mapf(random(1, 11), 1, 11, WAVE_HEIGHT.MIN, WAVE_HEIGHT.MAX);
        waves[i].speed = WAVE_SPEED.DFLT;
        waves[i].length = mapf(random(1, 11), 1, 11, WAVE_LENGTH.MIN, WAVE_LENGTH.MAX);
        waves[i].width = mapf(random(1, 11), 1, 11, WAVE_WIDTH.MIN, WAVE_WIDTH.MAX);
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
      //wave1.speed = mapf(globalSpeed, 1, 10, WAVE_SPEED.MIN, WAVE_SPEED.MAX);
      //waves[0].length = mapf(globalOffset, 1, 10, WAVE_LENGTH.MIN, WAVE_LENGTH.MAX);
      for (int i = 0; i < _numLines; i++) {
        for (int j = 0; j < NUM_WAVES; j++) {
          float position = waves[j].getValue(i);
          _lines[i].setOffset(position);
          _lines[i].show(waves[j].color, waves[j].width);
        }
      }
      break;
    }
    default:
      break;
    }
  }
};
