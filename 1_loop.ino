/*******************
 ** Loop Function **
 *******************/
void loop(void) {
  //PUT YOUR MAIN CODE HERE, TO RUN REPEATEDLY

  if (Serial.available() > 0) {
    userInput = Serial.read();
    Serial.print("User entered ");
    Serial.println(userInput);
    newUserInput = 1;
  }

  switch (userInput) {

      // TEMPLATE
      //    case 'x':
      //      // do something once
      //      if (newUserInput == 1) {
      //        // *** REPLACE THIS COMMENT WITH "ONCE" CODE ***
      //        newUserInput = 0;  // DO NOT DELETE!!
      //      }
      //      // do something over and over
      //      // *** REPLACE THIS COMMENT WITH "OVER AND OVER" CODE ***
      //      break;

    case 'a':
      // print instructions once
      if (newUserInput == 1) {
        Serial.println("Test a: Check that IR LED is blinking");
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // call testing function over and over
      TestIRLED();
      break;

    case 'b':
      // print instructions once
      if (newUserInput == 1) {
        Serial.println("Test b: Press the switches to test");
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // call testing function over and over
      TestSwitches();
      break;

    case 'c':
      // print instructions once
      if (newUserInput == 1) {
        Serial.println("Test c: Press the buttons to test");
        newUserInput = 0;  // DO NOT DELETE!!
      }

      // call testing function over and over
      TestButtons();
      break;

    case 'd':
      // do something once
      if (newUserInput == 1) {
        Serial.println("press the left and right buttons to test the motor");
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;
    case 'e':
      // do something once
      if (newUserInput == 1) {
        Serial.println("press the left and right buttons to test the motor and sensor");
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;
    case 'f':
      // do something once
      if (newUserInput == 1) {
        Serial.println("press the left and right buttons to test the motor and encoder");
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;
    case 'g':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("press the left and right buttons to count stripes"));
        Serial.println(F("press the up and down buttons to increment counts"));
        Serial.println(F("press the select button to set counts to 24"));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestMotor();
      break;
    case 'h':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("press the left and right buttons to increment desiredPosition"));
        Serial.println(F("press the up and down buttons to increment counts"));
        Serial.println(F("press the select button to send the launcher to the desired position."));
        newUserInput = 0;  // DO NOT DELETE!!
        startMotion = 0;
      }
      // do something over and over
      TestMoveLauncher();
      break;
    case 'i':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("press the up/down/left/right buttons to increment desiredServoAngle"));
        Serial.println(F("press the select button to command the servo and fire the solenoid"));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestAimFire();
      break;
      // print menu once
      if (newUserInput == 1) {
        PrintMenu();
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // no need to do anything over and over
      break;
    case 'j':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("press the select button to reload a ball"));
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // do something over and over
      TestReloader();
      break;
      // print menu once
      if (newUserInput == 1) {
        PrintMenu();
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // no need to do anything over and over
      break;
    case 'k':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("press the left and right buttons to increment headed"));
        Serial.println(F("press the up and down buttons to  increment target"));
        Serial.println(F("press the select button to start Demo 1"));
        newUserInput = 0;  // DO NOT DELETE!!
        startMotion = 0;
      }
      // do something over and over
      Demo1();
      break;
    case 's':
      if (newUserInput == 1) {
        Serial.println(F("Ardiuno: requesting data from MATLAB"));
        GetDataFromMATLAB();
        newUserInput = 0;
        Serial.println(F("done"));
      }
      break;
    case 't':
      if (newUserInput == 1) {
        Serial.println(F("Ardiuno: Requesting data from MATLAB"));
        GetDataFromMATLAB();
        Serial.println(F("Ardiuno: computing stuff"));
        ComputeStuff();
        newUserInput = 0;  // DO NOT DELETE!!
        Serial.println("done");
      }
      break;
    case 'v':
      if (newUserInput == 1) {
        Serial.println(F("Running Demo 4/competition code"));
        newUserInput = 0;  // DO NOT DELETE!!
        GetDataFromMATLAB();
        startMotion = 1;
        state = 1;
      }
      Demo1();
      break;
    case 'z':
      // print menu once
      if (newUserInput == 1) {
        PrintMenu();
        newUserInput = 0;  // DO NOT DELETE!!
      }
      // no need to do anything over and over
      break;

    default:
      // print message once
      if (newUserInput == 1) {
        Serial.print(F("No code written for "));
        Serial.println(userInput);
        Serial.println(F("Enter z to print menu"));
        newUserInput = 0;  // DO NOT DELETE
        TurnMotorOff(45);
        Serial.println(F("aborting!"));
        startMotion = 0;
        headed = 0;
        target = 0;
        state = 0;
        digitalWrite(solenoidPowerPin, 0);
      }
      // no need to do anything over and over
      break;
  }

}  // end loop() function
