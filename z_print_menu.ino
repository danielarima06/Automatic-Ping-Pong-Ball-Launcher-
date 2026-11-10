void PrintMenu(void) {
  // update this every time you add a new case
  // to the switch on userInput
  Serial.println(F("a = test IR LED"));
  Serial.println(F("b = test switches"));
  Serial.println(F("c = test buttons"));
  Serial.println(F("d = test motor"));
  Serial.println(F("e = test motor and sensor"));
  Serial.println(F("f = test motor and encoder"));
  Serial.println(F("g = test count"));
  Serial.println(F("h = test move launcher"));
  Serial.println(F("i = test aim fire"));
  Serial.println(F("j = test relaoder"));
  Serial.println(F("k = test Demo 1"));
  Serial.println(F("s = Get data from MATLAB"));
  Serial.println(F("t = get target data and return servo angle"));
  Serial.println(F("v = competition code"));
  Serial.println(F("z = print menu"));
}
