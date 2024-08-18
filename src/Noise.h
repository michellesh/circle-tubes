#define NUM_PARTICLES 50
struct XY {
  float x;
  float y;
};
XY _particles[NUM_PARTICLES];

class Noise : public Pattern {
private:
  float _speed = SPEED.DFLT;
  float _scale = SCALE.DFLT;
  uint8_t _colorIndex = 0;

public:
  static constexpr Range SPEED = {3, 20, 10};
  static constexpr Range SCALE = {1, 15, 5};

  float getSpeed() { return _speed; }

  float getScale() { return _scale; }

  void setSpeed(float x) { _speed = x; }

  void setScale(float x) { _scale = x; }

  void setColorIndex(uint8_t x) { _colorIndex = x; }

  void show() {
    float time = millis() / _speed; // millis()/10 good

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        int x = i;
        int y = tubes[i].yValue[j];
        float noiseValue = inoise8(x * _scale, y * _scale + time, time);
        uint8_t colorIndex =
            map(noiseValue, 0, 120, 0,
                100); // use smaller portion of the color palette
        CRGB color = palette.colorFromPalette(colorIndex);
        uint8_t brightnessValue =
            sin8(noiseValue) * 1.5; // increase brightness contrast
        tubes[i].leds[j] = color.nscale8(brightnessValue);
      }
    }
  }

  void fire() {
    float time = millis();

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        int x = i;
        int y = YMAX - tubes[i].yValue[j];
        uint8_t colorIndex = qsub8(
            inoise8(x * 60, y * 60 + time, time / 3),
            abs8(y - YMAX) * 255 / YMAX
        );
        tubes[i].leds[j] = palette.colorFromPalette(colorIndex);
        tubes[i].leds[j].nscale8(colorIndex);
      }
    }
  }

  void ripple() {
    float time = millis() * (_speed * 2);
    int centerX = NUM_TUBES / 2;
    int centerY = YMAX / 2;

    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        int x = i;
        int y = tubes[i].yValue[j];
        float dist = sqrt(sq(x - centerX) + sq(y - centerY));
        uint8_t noiseValue = inoise8(dist * (_scale / 2), time);
        uint8_t brightnessValue =
            sin8(noiseValue) * 1.5; // Increase brightness contrast

        CRGB color = CHSV(noiseValue, 100, brightnessValue);
        tubes[i].leds[j] = color;
      }
    }
  }

  bool inBounds(int x, int y) {
    return x > 0 && x < NUM_TUBES && y > 0 && y < YMAX;
  }

  void showParticles() {
    //float noiseScale = mapf(globalOffset, 1, 10, 0.0005, 1); // 0.005
    //static float prevNoiseScale = noiseScale;
    //if (prevNoiseScale != noiseScale) {
    //  Serial.print("noiseScale: ");
    //  Serial.println(noiseScale);
    //  prevNoiseScale = noiseScale;
    //}
    float width = mapf(globalWidth, 1, 10, 0.1, 10);
    float speed = mapf(globalSpeed, 1, 10, 0.001, 1);
    float angMult = mapf(globalOffset, 1, 10, 0.001, 10);
    static float prevAngMult = angMult;
    if (prevAngMult != angMult) {
      Serial.print("angMult: ");
      Serial.println(angMult);
      prevAngMult = angMult;
    }

    // update particles
    for (int i = 0; i < NUM_PARTICLES; i++) {
      XY p = _particles[i];
      float n =
           inoise8(_particles[i].x, _particles[i].y) * angMult;
      //Serial.print("noise: ");
      //Serial.println(n);
      //if (i == 0) {
      //  Serial.print("x: ");
      //  Serial.print(p.x);
      //  Serial.print(" y: ");
      //  Serial.println(p.y);
      //}
      float a = 2 * PI * n;// * mapf(n, 0, 255, 0.01, 100);
      _particles[i].x += cos(a) * speed; // * speed here
      _particles[i].y += sin(a) * speed;
      if (!inBounds(_particles[i].x, _particles[i].y)) {
        _particles[i].x = random(NUM_TUBES);
        _particles[i].y = random(YMAX);
      }
    }

    // show leds that are close to particles
    for (int i = 0; i < NUM_TUBES; i++) {
      for (int j = 0; j < tubes[i].length; j++) {
        int x = i;
        int y = tubes[i].yValue[j];
        for (int k = 0; k < NUM_PARTICLES; k++) {
          XY p = _particles[k];
          float dist = distance(p.x, p.y, x, y);
          if (dist < width) {
            uint8_t colorIndex = map(dist, 0, width, 100, 0);
            tubes[i].leds[j] = palette.colorFromPalette(colorIndex);
            uint8_t brightness = map(dist, 0, width, BRIGHTNESS, 0);
            brightness = sin8(brightness) * 1.5; // increase brightness contrast
            tubes[i].leds[j].nscale8(brightness);
          }
        }
      }
    }
  }
};