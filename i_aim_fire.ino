void TestAimFire(void) {
#include <Servo.h>
  //Uses UP/DOWN to increment/decrement desiredServoAngle variable by 5 degrees
  //Uses LEFT/RIGHT to decrement/increment desiredServoAngle variable by 1 degree
  //[ADD LATER] Uses SELECT to command the servo to desiredServoAngle and fire the solenoid
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:  // up button
    case 1:  // down button
    case 4:  // left button
    case 2:  // right button
      switch (buttonPressed) {
        case 3:  // up button
          servoAngleIncrement = 5;
          break;
        case 1:  // down button
          servoAngleIncrement = -5;
          break;
        case 4:  // left button
          servoAngleIncrement = -1;
          break;
        case 2:  // right button
          servoAngleIncrement = 1;
          break;
      }
      tslIncrement = millis() - incrementTime;
      if ((prevButtonPressed != buttonPressed) || (tslIncrement > 250)) {
        incrementTime = millis();
        desiredServoAngle = desiredServoAngle + servoAngleIncrement;
        desiredServoAngle = constrain(desiredServoAngle, 0, 180);
        Serial.print(F("The desired servo angle is "));
        Serial.println(desiredServoAngle);
      }
      break;
    case 5:  // select button
      if (prevButtonPressed != buttonPressed) {
        if (state > 0) {
          Serial.println(F("Previous aim/fire sequence is still in progress"));
        } else {
          state = 1;
          stateChangeTime = millis();
        }
      }
      break;
  }
  switch (state) {
    case 1:  // delay, then command the servo
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        launcherServo.write(map(desiredServoAngle, 0, 180, 180, 0));
        Serial.print(F("launcher servo commanded to "));
        Serial.println(desiredServoAngle);
        state = 2;
        stateChangeTime = millis();
      }
      break;
    case 2:  // delay, then turn the colenoid on
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        digitalWrite(solenoidPowerPin, HIGH);
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3:  // delay, then turn the colenoid off
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > solenoidActivationTime) {
        digitalWrite(solenoidPowerPin, 0);
        state = 0;
      }
      break;
  }
}
