float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  float percentage = (value - inMin) / (inMax - inMin);
  return outMin + (outMax - outMin) * percentage;
}

uint8_t mirrorFade(uint8_t x, uint8_t max = 255) {
  return x < 127 ? map(x, 0, 127, 0, max) : map(x, 127, 255, max, 0);
}

float modf(float f, int i) {
  int intMod = int(f) % i;
  float remainder = f - int(f);
  return intMod + remainder;
}

float distance(float x1, float y1, float x2, float y2) {
  float deltaX = x2 - x1;
  float deltaY = y2 - y1;
  return sqrt(deltaX * deltaX + deltaY * deltaY);
}