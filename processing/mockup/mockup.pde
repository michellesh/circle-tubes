int padding = 30;
int spacing = 20;
int smallRadius = 1;
int bigRadius = 5;
int threshold = 2;

int numTubes = 23;
float[] position = new float[numTubes];
float[] maxPosition = new float[numTubes];
float[] minPosition = new float[numTubes];
int[] numLEDs = {4,  11, 14, 15, 18, 19, 20, 21, 22, 23, 22, 23,
                 22, 23, 22, 21, 20, 19, 18, 15, 14, 11, 4};
float[][] yPos = new float[numTubes][];
float[][] yValue = new float[numTubes][];
float[] xPos = new float[numTubes];
int yMax = (max(numLEDs) - 1) * 2; //44

int maxPos = max(numLEDs) * spacing;
int maxLEDs = max(numLEDs);
int maxHeight = maxLEDs - 1;
int minHeight = -maxHeight;

float ticks = 0;

void setup() {
  size(500, 500);
  stroke(255);
  // frameRate(30);

  // draw leds as small points
  for (int i = 0; i < numLEDs.length; i++) {
    int tubeHeight = numLEDs[i] * spacing;
    int offset = (maxPos - tubeHeight) / 2;
    minPosition[i] = offset;
    maxPosition[i] = tubeHeight;
    yPos[i] = new float[numLEDs[i]];
    yValue[i] = new float[numLEDs[i]];
    print("i =", i, ": ");
    for (int j = 0; j < numLEDs[i]; j++) {
      xPos[i] = padding + (i * spacing);
      yPos[i][j] = offset + padding + (j * spacing);
      int yMaxTube = ((numLEDs[i] - 1) * 2);
      yValue[i][j] = (yMax - yMaxTube) / 2 + (j * 2);
      print(yValue[i][j], " ");
    }
    println();
  }
}

void draw() {
  background(0);
  for (int i = 0; i < numLEDs.length; i++) {
    for (int j = 0; j < numLEDs[i]; j++) {
      float dist = abs(position[i] - yValue[i][j]);
      if (dist < threshold) {
        // strokeWeight(bigRadius);
        strokeWeight(map(dist, 0, threshold, bigRadius, smallRadius));
      } else {
        strokeWeight(smallRadius);
      }
      point(xPos[i], yPos[i][j]);
    }

    float offset = i * 0.3;
    position[i] = map(sin((ticks * 2) + offset), -1, 1, yMax / 2 - 10, yMax / 2 + 10);
  }
  ticks += 0.01;
}
