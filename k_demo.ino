void Demo1(void) {
  //Uses UP/DOWN to increment target variable. Uses LEFT/RIGHT to increment headed variable. Uses SELECT to assign 1 to startMotion, which will result in MoveLauncher() being called repeatedly until the launcher arrives at desiredPosition.
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:
    case 1:
      tslIncrement = millis() - incrementTime;
      if ((buttonPressed != prevButtonPressed) || (tslIncrement > 250)) {
        incrementTime = millis();
        if (buttonPressed == 3) {
          target = target + 1;
        } else if (buttonPressed == 1) {
          target = target - 1;
        }
        target = constrain(target, 0, 5);
        Serial.print("the target value is ");
        Serial.println(target);
      }
      break;
    case 4:
    case 2:
      tslIncrement = millis() - incrementTime;
      if ((buttonPressed != prevButtonPressed) || (tslIncrement > 250)) {
        incrementTime = millis();
        if (buttonPressed == 2) {
          headed = headed + 1;
        } else if (buttonPressed == 4) {
          headed = headed - 1;
        }
        headed = constrain(headed, 0, 2);
        Serial.print("the launcher is headed to ");
        Serial.println(headed);
      }
      break;
    case 5:
      startMotion = 1;
      state = 1;
      break;
    case 0:
      MoveLauncher();
      break;
  }
}
