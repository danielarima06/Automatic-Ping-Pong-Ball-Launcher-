void NotMoving(void) {
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);
  // at home
  if (leftSwitchState == 1) {
    AtHome();
  } else if (rightSwitchState == 1) {
    AtReloader();
  }
  // at target
  else if (desiredPosition == counts) {
    AtTarget();
  }
}

void AtReloader(void) {
  switch (state) {
    case 1:  //dispense ball
      // command reloader servo
      reloadServo.write(dispenseAngle);
      Serial.println(F("dispensing"));
      // change the state, update the time
      state = 2;
      stateChangeTime = millis();
      break;

    case 2:  // delay, then stop dispensing
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > dispenseDuration) {
        // command the reloader servo
        reloadServo.write(holdAngle);
        Serial.println(F("holding"));
        // change the state, update the time
        state = 3;
        stateChangeTime = millis();
        break;


        case 3:  // delay, then set motion variables
          tslStateChange = millis() - stateChangeTime;
          // REDUCED: 1000ms -> 150ms 
          if (tslStateChange > 150) {
            startMotion = 1;
            headed = 1;
            target = target + 1;
            Serial.println(F("ball reloaded - setting motion variables"));
            state = 1;
            break;
          }
      }
  }
}


void AtHome(void) {
  switch (state) {
    case 1:  // turn the led on
      // turn the led on
      digitalWrite(ledPin, 1);
      Serial.println(F("starting time - led on"));
      // change the state, update the time
      state = 2;
      stateChangeTime = millis();
      break;

    case 2:  // delay, then turn the led off
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        // turn the led off
        digitalWrite(ledPin, 0);
        Serial.println(F("triggering timer - led off"));
        // chnage the state
        state = 3;
        break;

        case 3:  //SET THE MOTION VARIABLES
          Serial.println(F("SETTING MOTION VARIABLES"));
          if (target < 5) {
            if (target == 0 && userInput == 'v') {
              Serial.println(F("Calling ComputeStuff()"));
              ComputeStuff();
            }
            startMotion = 1;
            headed = 1;
            state = 1;
          } else {
            target = 0;
            state = 0;
            Serial.println(F("ALL DONE"));
            if (userInput == 'v') {
              Serial.println(F("done"));
            }
            userInput = 'x';
            break;
          }
      }
  }
}

void AtTarget(void) {
  switch (state) {
    case 1:  // command launcher servo to firing angle
      desiredServoAngle = writeToServo[target];
      launcherServo.write(map(desiredServoAngle, 0, 180, 180, 0));
      Serial.print(F("Commanding launcher servo to "));
      Serial.print(desiredServoAngle);
      Serial.print(F(" for target "));
      Serial.println(target);
      state = 2;
      stateChangeTime = millis();
      break;

    case 2:  // delay, then turn the solenoid on
      tslStateChange = millis() - stateChangeTime;
      // REDUCED: 2000ms -> 400ms
      if (tslStateChange > 400) {
        digitalWrite(solenoidPowerPin, 1);
        Serial.println(F("Firing!"));
        state = 3;
        stateChangeTime = millis();
      }
      break;

    case 3:  // delay, then turn the solenoid off
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > solenoidActivationTime) {
        digitalWrite(solenoidPowerPin, 0);
        Serial.println(F("done firing"));
        state = 4;
        stateChangeTime = millis();
      }
      break;

    case 4:  // delay, then command the launcher servo to the reload angle
      tslStateChange = millis() - stateChangeTime;
      // REDUCED: 2000ms -> 50ms
      if (tslStateChange > 50) {
        launcherServo.write(map(106, 0, 180, 180, 0));
        Serial.println(F("commanding launcher servo to reload angle "));
        state = 5;
      }
      break;

    case 5:  // set the motion variables
      startMotion = 1;
      if (target < 5) {
        headed = 2;
      } else {
        headed = 0;
      }
      Serial.println(F("target actions complete - setting motion variables"));
      state = 1;
  }
}
