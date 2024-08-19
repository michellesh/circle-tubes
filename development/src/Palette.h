#include "colors.h"

#define DEFAULT_PALETTE 0

class Palette {
private:
  CRGBPalette16 _currentPalette = *(activePalettes[DEFAULT_PALETTE]);
  CRGBPalette16 _targetPalette = *(activePalettes[DEFAULT_PALETTE]);
  uint8_t _activePaletteIndex = DEFAULT_PALETTE;
  uint8_t _secondsPerPalette = 10;
  Timer _paletteCycleTimer = {_secondsPerPalette * 1000};

  void _setNextColorPalette() {
    const uint8_t numberOfPalettes =
        sizeof(activePalettes) / sizeof(activePalettes[0]);
    static uint8_t whichPalette = -1;
    whichPalette = addmod8(whichPalette, 1, numberOfPalettes);

    _targetPalette = *(activePalettes[whichPalette]);
  }

public:
  void cycle() {
    if (_paletteCycleTimer.complete()) {
      _setNextColorPalette();
      _paletteCycleTimer.reset();
    }
    EVERY_N_MILLISECONDS(10) {
      nblendPaletteTowardPalette(_currentPalette, _targetPalette, 12);
    }
  }

  void setPalette(uint8_t whichPalette) {
    _activePaletteIndex = whichPalette;
    _currentPalette = *(activePalettes[whichPalette]);
    _targetPalette = *(activePalettes[whichPalette]);
    _paletteCycleTimer.reset();
  }

  uint8_t getPalette() { return _activePaletteIndex; }

  CRGB colorFromPalette(uint8_t paletteIndex) {
    return ColorFromPalette(_currentPalette, paletteIndex);
  }

  CRGB mapToColor(int value, int from, int to) {
    int paletteIndex = map(value, from, to, 0, 255);
    return ColorFromPalette(_currentPalette, paletteIndex);
  }
};
