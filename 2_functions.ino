/****************************
 ** User-Defined Functions **
 ****************************/
// create custom headers as necessary to clearly organize your functions
void ReadButtons(void) {
  // Keep track of the previous button number
  int prevButtonNumber = buttonNumber;
  // Read the button value
  int buttonValue = 0;
  buttonValue = analogRead(buttonPin);
  // Determine the button number that corresponds to the button value
  if (buttonValue < 5) {
    buttonNumber = 1;
  } else if ((buttonValue > 115) && (buttonValue < 175)) {
    buttonNumber = 2;
  } else if ((buttonValue > 305) && (buttonValue < 365)) {
    buttonNumber = 3;
  } else if ((buttonValue > 480) && (buttonValue < 540)) {
    buttonNumber = 4;
  } else if ((buttonValue > 715) && (buttonValue < 775)) {
    buttonNumber = 5;
  } else if (buttonValue > 1015) {
    buttonNumber = 0;
  } else {
    buttonNumber = -1;
  }

  // Determine if the button number is an actual button press or a bounce
  if (buttonNumber == prevButtonNumber) {
    cibn = cibn + 1;
    if (cibn > 100) {
      buttonPressed = buttonNumber;
    }
  } else {
    cibn = 0;
  }
}

void TurnMotorOn(void) {
  // if the motor is not already on, sets the motor direction, turns the motor on and sets the motor on flag to 1
  if (motorOn == 0) {
    digitalWrite(motorDirectionPin, motorRight);
    analogWrite(motorPowerPin, motorPower);
    motorOn = 1;
  }
}

void TurnMotorOff(int reverseTime) {
  // if the motor is on, turns the motor off, turns the motor on in the opposite direction, turns the motor off again, and sets the motor on flag to zero
  if (motorOn == 1) {
    analogWrite(motorPowerPin, 0);
    delay(10);
    digitalWrite(motorDirectionPin,!motorRight);
    analogWrite(motorPowerPin,motorPower);
    delay(reverseTime);
    analogWrite(motorPowerPin, 0);

    motorOn = 0;
  }
}

bool GetEncoderBoolean(void) {
  // reads the ir sensor value and returns
  //1 (true) if the ir sensor is over a black stripe
  //0 (false) if the ir sensor is over a white stripe
  irSensorValue = analogRead(irSensorPin);
  if ((black == 1) && (irSensorValue < 90)) {
    return 0;
  } else if ((black == 0) && (irSensorValue > 300)) {
    return 1;
  } else {
    return black;
  }
}

void CountStripes(void){
  // incraments a counter variable (counter) each time the ir sensor moves from a white stripe to a black stripe or vise versa. 
  bool prevBlack = black;
  black = GetEncoderBoolean();
  tslStripeChange = millis() - stripeChangeTime;
  if(black != prevBlack){
    stripeChangeTime = millis();
    if(motorRight){
      counts = counts + 1;
    } else{
      counts = counts - 1;
    }
    Serial.print(" the stripe number is ");
    Serial.print(counts);
    Serial.print(" and ");
    Serial.print(tslStripeChange);
    Serial.println(" seconds since stripe color changed");
  }

}
