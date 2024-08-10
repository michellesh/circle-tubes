int padding = 30;
int spacing = 20;
int radius = 5;

int[] numLEDs = {4,  11, 14, 15, 18, 19, 20, 21, 22, 23, 22, 23,
                 22, 23, 22, 21, 20, 19, 18, 15, 14, 11, 4};
int maxHeight = max(numLEDs) * spacing;

void setup() {
  size(500, 500);
  strokeWeight(radius);
  background(0);
  stroke(255);
}

void draw() {
  for (int i = 0; i < numLEDs.length; i++) {
    int height = numLEDs[i] * spacing;
    int offset = (maxHeight - height) / 2;
    for (int j = 0; j < numLEDs[i]; j++) {
      int x = padding + (i * spacing);
      int y = offset + padding + (j * spacing);
      point(x, y);
    }
  }
}
