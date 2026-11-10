void TestIRLED(void) {
  // write code here to blink the LED
  // temporary code:
  tslBlink = millis() - blinkTime;
  if (ledOn == 0) {
    if (tslBlink > ledOffDuration) {
      digitalWrite(ledPin, HIGH);
      ledOn = 1;
      blinkTime = millis();
      Serial.println("Led is on");
    }
  } else {
    if (tslBlink > ledOnDuration) {
      digitalWrite(ledPin, LOW);
      ledOn = 0;
      blinkTime = millis();
      Serial.println("Led is off");
    }
  }
}
