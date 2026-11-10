Button Usage: Up/Down    -
              Left/Right -
              Select     -

  Pin Usage:    Pin type/number     Hardware
              ----------------    ----------------
              Digital Pin 10                  Led
              Digital Pin 11                  left switch 
              Digital Pin 12                  right switch 
              Analog A7                       Buttons 
              Digital Pin 4                   Motor
              Digital Pin 5                   Motor
              Analog Pin A5                   irSensor
              Digital Pin 9                   launcher servo
              Digital Pin 6                   solenoid 
              Digital Pin 10                  reloader servo
*******************************************************************/

/****************************
 ** #defines and #includes **
 ****************************/
#include <Servo.h>
/***********************
 ** Global Variables ***
 ***********************/
// *** Declare & Initialize Pins ***
const int ledPin = 13;
const int leftSwitchPin = 11;
const int rightSwitchPin = 12;
const int buttonPin = A7;
const int motorDirectionPin = 4;
const int motorPowerPin = 5;
const int debugLedPin = 13;
const int irSensorPin = A5;
const int launcherServoPin = 9;
const int solenoidPowerPin = 6;
const int reloaderServoPin = 10;
// *** Create Servo Objects ***
Servo launcherServo;
Servo reloadServo;
// *** Declare & Initialize Program Variables ***
int ledOnDuration = 1000;
int ledOffDuration = 2000;
unsigned long blinkTime = 0;
unsigned long tslBlink = 0;
bool ledOn = 0;
int leftSwitchState = 0;
int rightSwitchState = 0;
unsigned long printTime = 0;
unsigned long tslPrint = 0;
int printInterval = 2000;
unsigned long leftSwitchChangeTime = 0;
unsigned long rightSwitchChangeTime = 0;
unsigned long tslLeftSwitchChange = 0;
unsigned long tslRightSwitchChange = 0;
int switchDebounceInterval = 20;
int buttonNumber = 0;
unsigned long cibn = 0;
int buttonPressed = 0;
const int motorPower = 255;
bool motorOn = 0;
bool motorRight = 0;
unsigned long debugPrintTime = 0;
unsigned long tslDebugPrint = 0;
int debugPrintInterval = 200;
unsigned long debugBlinkTime = 0;
unsigned long tslDebugBlink = 0;
int debugLedHiLo = 0;
int irSensorValue = 0;
bool black = 1;
unsigned long stripeChangeTime = 0;
unsigned long tslStripeChange = 0;
int counts = 24;
unsigned long incrementTime = 0;
unsigned long tslIncrement = 0;
bool startMotion = 0;
int desiredPosition = 24;
int desiredServoAngle = 90;
int servoAngleIncrement = 5;
int state = 0;
unsigned long stateChangeTime = 0;
unsigned long tslStateChange = 0;
int solenoidActivationTime = 31;
int holdAngle = 40;
int dispenseAngle = 0;
int dispenseDuration = 245;
int target = 0;
int headed = 0;
int driveTo[] = { 19, 35, 33, 31, 32, 34 };
int writeToServo[] = { 140, 110, 130, 90, 120, 80 };
float xTargetVec[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
//int writeToServo[] = {140,110,130,90,120,80};
int servoReloadAngle = 80;

// values they gave us 
// float alpha = 15.12;
// float beta = 0.0001;
// float thetaL0 = 28.03;
// float kappa = 2.90;
// float lambda = -0.001;

// our values
float alpha = 5.93;
float beta = 0.0714;
float thetaL0 = 26.71;
float kappa = 3.08;
float lambda = -0.0030;
char userInput = 'z';
bool newUserInput = 1;  // 1 means user entered a letter this time through loop function
                        // 0 means user did not enter a letter this time through loop function

/********************
 ** Setup Function **
 ********************/
void setup(void) {
  // PUT YOUR SETUP CODE HERE, TO RUN ONCE:

  // *** Initialize Serial Communication ***
  Serial.begin(9600);
  Serial.println("");
  Serial.println("TestHardwareSketch menu");
  // Because userInput was initialized to 'z' and
  // newUserInput was initialized to 1, the menu
  // will print when you upload the sketch -
  // see case 'z' in loop()

  // *** Configure Digital Pins & Attach Servos ***
  pinMode(ledPin, OUTPUT);
  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);
  pinMode(motorDirectionPin, OUTPUT);
  pinMode(motorPowerPin, OUTPUT);
  launcherServo.attach(launcherServoPin);
  pinMode(solenoidPowerPin, OUTPUT);
  reloadServo.attach(reloaderServoPin);
  // *** Take Initial Readings ***
  black = GetEncoderBoolean();
  // *** Move Hardware to Desired Initial Positions ***
  reloadServo.write(holdAngle);
}  // end setup() function
