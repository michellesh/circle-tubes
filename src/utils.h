float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  float percentage = (value - inMin) / (inMax - inMin);
  return outMin + (outMax - outMin) * percentage;
}

uint8_t mirrorFade(uint8_t x, uint8_t max = 255) {
  return x < 127 ? map(x, 0, 127, 0, max) : map(x, 127, 255, max, 0);
}

float sinwave(
    float minValue, float maxValue, unsigned long waveLength = 50,
    unsigned long waveLengthOffset = 0
) {
  return mapf(
      sin((float)(ticks + waveLengthOffset) * PI / waveLength), -1, 1, minValue,
      maxValue
  );
}