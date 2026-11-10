void GetDataFromMATLAB(void){
  Serial.println(F("ready for data"));
  for(target = 0; target <= 5; target++){
  String dataString1 = Serial.readStringUntil('\n');
  driveTo[target] = dataString1.toInt();
  String dataString2 = Serial.readStringUntil('\n');
  xTargetVec[target] = dataString2.toFloat();
  Serial.print("For target ");
  Serial.print(target);
  Serial.print(", drive to stripe ");
  Serial.print(driveTo[target]);
  Serial.print(" and aim for ");
  Serial.print(xTargetVec[target], 3);
  Serial.println("m.");
  }
  target = 0;
}

 
