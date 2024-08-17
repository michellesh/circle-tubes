#include "colors.h"

#define MAX_PALETTE_INDEX 245
#define DEFAULT_PALETTE 0

class Palette {
private:
  CRGBPalette16 _currentPalette = *(activePalettes[DEFAULT_PALETTE]);
  CRGBPalette16 _targetPalette = *(activePalettes[DEFAULT_PALETTE]);
  uint8_t _activeColorMode = VERTICAL_GRADIENT;
  uint8_t _activePaletteIndex = DEFAULT_PALETTE;

public:
  static const uint8_t SOLID = 0;
  static const uint8_t VERTICAL_GRADIENT = 1;
  static const uint8_t HORIZONTAL_GRADIENT = 2;
  static const uint8_t RADIAL_GRADIENT = 3;

  void cycle() {
    EVERY_N_MILLISECONDS(10) {
      nblendPaletteTowardPalette(_currentPalette, _targetPalette, 12);
    }
  }

  void setColorMode(uint8_t colorMode) { _activeColorMode = colorMode; }

  uint8_t getColorMode() { return _activeColorMode; }

  void setPalette(uint8_t whichPalette) {
    _activePaletteIndex = whichPalette;
    _currentPalette = *(activePalettes[whichPalette]);
    _targetPalette = *(activePalettes[whichPalette]);
  }

  uint8_t getPalette() { return _activePaletteIndex; }

  CRGB colorFromPalette(uint8_t paletteIndex) {
    return ColorFromPalette(_currentPalette, paletteIndex);
  }

  CRGB mapToColor(int value, int from, int to) {
    int paletteIndex = map(value, from, to, 0, 255);
    return ColorFromPalette(_currentPalette, paletteIndex);
  }

  CRGB getColor(int i, bool reversePalette = false) {
    uint8_t paletteIndex = 0;
    switch (_activeColorMode) {
    case VERTICAL_GRADIENT: {
      // TODO
      break;
    }
    default:
      break;
    }
    if (reversePalette) {
      paletteIndex = MAX_PALETTE_INDEX - paletteIndex;
    }
    return ColorFromPalette(_currentPalette, paletteIndex);
  }
};
