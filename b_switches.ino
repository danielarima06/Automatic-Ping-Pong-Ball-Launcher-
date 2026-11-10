void TestSwitches(void) {
  // write code here to test the switches
  // temporary code:
  // Keep track of previous switch states for comparison
  int prevLeftSwitchState = leftSwitchState;
  int prevRightSwitchState = rightSwitchState;
  int tempLeftSwitchState = 0;
  int tempRightSwitchState = 0;
  // Update the switch state variables
  tempLeftSwitchState = digitalRead(leftSwitchPin);
  tempRightSwitchState = digitalRead(rightSwitchPin);
  // Left switch debounce code
  if (tempLeftSwitchState != prevLeftSwitchState) {
    tslLeftSwitchChange = millis() - leftSwitchChangeTime;
    if (tslLeftSwitchChange > switchDebounceInterval) {
      leftSwitchChangeTime = millis();
      leftSwitchState = tempLeftSwitchState;
    }
  }
  // Right switch debounce code
  if (tempRightSwitchState != prevRightSwitchState) {
    tslRightSwitchChange = millis() - rightSwitchChangeTime;
    if (tslRightSwitchChange > switchDebounceInterval) {
      rightSwitchChangeTime = millis();
      rightSwitchState = tempRightSwitchState;
    }
  }
  // If appropriate, print a new message
  tslPrint = millis() - printTime;
  if ((leftSwitchState != prevLeftSwitchState) || (rightSwitchState != prevRightSwitchState) || (tslPrint > printInterval)) {
    printTime = millis();
    Serial.print("Left switch state: ");
    Serial.print(leftSwitchState);
    Serial.print("... Right switch state: ");
    Serial.println(rightSwitchState);
  }
}
