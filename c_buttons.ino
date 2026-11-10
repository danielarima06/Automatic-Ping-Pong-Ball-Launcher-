void TestButtons(void) {
  // write code here to test the buttons
  // temporary code:
  // Keep track of the previously pressed button
  int prevButtonPressed = buttonPressed;
  // Check what button is currently pressed
  ReadButtons();
  // If appropriate, print a new message
  tslPrint = millis() - printTime;
  if ((tslPrint > printInterval) || (buttonPressed != prevButtonPressed)) {
    printTime = millis();
    switch (buttonPressed) {
      case 3:
        Serial.println("UP button Pressed");
        break;
      case 1:
        Serial.println("DOWN button Pressed");
        break;
      case 4:
        Serial.println("LEFT button Pressed");
        break;
      case 2:
        Serial.println("RIGHT button Pressed");
        break;
      case 5:
        Serial.println("SELECT button Pressed");
        break;
      case 0:
        Serial.println("NO buttons Pressed");
        break;
      default:
        Serial.println("Something went wrong");
    }
  }
}
