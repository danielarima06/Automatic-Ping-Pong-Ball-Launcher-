void TestMotor(void) {
  // uses left /right buttons to move the launcer left/right along the linear stage
  //NEW - 1
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:  //up button
             // doing nothing


    case 1:  // down button
             // NEW - 2
      tslIncrement = millis() - incrementTime;
      if ((buttonPressed != prevButtonPressed) || (tslIncrement > 250)) {
        incrementTime = millis();
        if (buttonPressed == 3) {
          counts = counts + 1;
        } else if (buttonPressed == 1) {
          counts = counts - 1;
        }
        Serial.print("the stripe number is ");
        Serial.println(counts);
      }
      break;
    case 4:  // left button
      motorRight = 0;
      TurnMotorOn();
      break;
    case 2:  // right button
      motorRight = 1;
      TurnMotorOn();
      break;
    case 5:  // select button
      // NEW - 3
      if (counts != 24) {
        counts = 24;
        Serial.print("the stripe number is ");
        Serial.println(counts);
      }
      break;
    case 0:  // none
      TurnMotorOff(40);
      // NEW - 4
      if(userInput == 'g'){
        CountStripes();
      }
      break;
    default:
      // doing nothing
      break;
  }
  if (motorOn == 1) {
    switch (userInput) {
      case 'd':
        PrintLeftRight();
        break;
      case 'e':
        PrintSensorValue();
        break;
      case 'f':
        PrintBlackWhite();
        break;
      case 'g':
        // NEW - 5
        CountStripes();
        break;
    }
  }
}

void PrintLeftRight(void) {
  // prints "launcher is moving left" or "launcher is moving right" as appropriate. It should only print every printdelay milliseconds and should not call delay().
  tslPrint = millis() - printTime;
  if (tslPrint > printInterval) {
    printTime = millis();
    Serial.print("launcher is moving ");
    if (motorRight == 1) {
      Serial.println("RIGHT");
    } else {
      Serial.println("LEFT");
    }
  }
}

void PrintSensorValue(void) {
  irSensorValue = analogRead(irSensorPin);
  tslPrint = millis() - printTime;
  if (tslPrint > 50) {
    printTime = millis();
    Serial.print("The sensor value is: ");
    Serial.println(irSensorValue);
  }
}

void PrintBlackWhite(void) {
  // prints "over black" if global variable black is one and "over white" if globial variable black is 0. It should only print "over black" or "over white" whgen a change in black occurs.
  bool prevBlack = black;
  black = GetEncoderBoolean();
  if (black != prevBlack) {
    if (black == 1) {
      Serial.println("over black");
    } else {
      Serial.println("over white");
    }
  }
}
