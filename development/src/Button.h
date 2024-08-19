#define BUTTON_PIN 4

struct Button {
  int pin;
  bool pressed;
};

Button button = {BUTTON_PIN};

void setupButton() { pinMode(button.pin, INPUT); }

bool isButtonPressed() { return !digitalRead(button.pin); }

void onButtonPressed() { Serial.println("click"); } // TODO

void handleButton() {
  if (isButtonPressed()) {
    if (!button.pressed) {
      button.pressed = true;
      onButtonPressed();
    }
  } else if (button.pressed) {
    button.pressed = false;
  }
}
