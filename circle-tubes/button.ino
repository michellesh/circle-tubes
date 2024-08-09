bool isButtonPressed() {
  return !digitalRead(button.pin);
}

void checkButtonPressed() {
  if (isButtonPressed()) {
    if (!button.pressed) {
      button.pressed = true;
      onButtonPressed();
    }
  } else if (button.pressed) {
    button.pressed = false;
  }
}

void onButtonPressed() {
  Serial.println("click");
}
