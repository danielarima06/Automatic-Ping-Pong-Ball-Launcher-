void TestReloader(void) {
  //moves the reloader link rod to the dispense angle and then back to the hold angle when the select button is pressed
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 5:  // select button
      if (prevButtonPressed != buttonPressed) {
        if (state > 0) {
          Serial.println(F("Previous reload event is still in progress"));
        } else {
          state = 1;
        }
      }
      break;
  }
  switch (state) {
    case 1:  // command the reloader servo to the dispense angle
      reloadServo.write(dispenseAngle);
      Serial.print(F("dispensing"));
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:  // delay, then command the reloader servo to the hold angle
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > dispenseDuration) {
        reloadServo.write(holdAngle);
        Serial.println(F("holding"));
        state = 0;
      }
      break;
  }
}
