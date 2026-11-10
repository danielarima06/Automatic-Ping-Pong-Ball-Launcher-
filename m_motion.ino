void MoveLauncher(void) {
  //depending on flag variables motorOn and startMotion, calls functions to manage launcher motion or prepair the launcher for motion.
  //DebugPrint("calling MoveLauncher function; startMotion = ", startMotion);
  if (motorOn == 1) {
    Moving();
  } else {
    if (startMotion == 1) {
      PreparingToMove();
    } else {
      NotMoving();
    }
  }
}

void PreparingToMove(void) {
  // set desiredPosition
  if(userInput == 'k' || userInput == 'v') {
    switch (headed) {
      case 0:
        leftSwitchState = digitalRead(leftSwitchPin);
        if (leftSwitchState == 1) {
          Serial.println(F("already home!"));
          counts = 5;
          desiredPosition = 5;
          startMotion = 0;
          headed = 1;
        } else {
          Serial.println(F("headed home"));
          desiredPosition = -50;
        }
        break;
      case 1:
        desiredPosition = driveTo[target];
        break;
      case 2:
        desiredPosition = 100;
        break;
    }
  }

  // set motorRight
  if (desiredPosition > counts) {
    motorRight = 1;
  } else {
    motorRight = 0;
  }
  // turn motor on
  if (counts != desiredPosition) {
    TurnMotorOn();
    startMotion = 0;
  }
}

void Moving(void) {
  //count stripes
  CountStripes();
  //stop at target
  if (counts == desiredPosition) {
    TurnMotorOff(45);
    CountStripes();
    Serial.print(F("launcher at stripe "));
    Serial.println(counts);
  }

  //read switches
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);
  // stop at home (moving left, left switch tripped)
  if ((motorRight == 0) && (leftSwitchState == 1)) {
    TurnMotorOff(45);
    CountStripes();
    counts = 5;
    Serial.println(F("launcher at home - counts set to 5"));
  }
  // stop at reloader (moving right, right switch tripped)
  else if ((motorRight == 1) && (rightSwitchState == 1)) {
    TurnMotorOff(45);
    CountStripes();
    counts = 43;
    Serial.println(F("launcher at reloader - counts set to 43"));
  }
}
