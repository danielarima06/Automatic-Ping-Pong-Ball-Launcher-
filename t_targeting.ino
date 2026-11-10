// ComputeStuff
void ComputeStuff(void) {
  Serial.println(F("Performing targeting claculations"));
  float d[] = { 0.0876, 0.1190 };
  float H[] = { 0.0866, 0.0750, 0.1060, 0.0250 };
  TargetServoAngles(d, kappa, lambda, H, alpha, beta, thetaL0, xTargetVec);
  for (int i = 0; i < 6; i++) {
    Serial.print("To hit a Target at  ");
    Serial.print(xTargetVec[i]);
    Serial.print(" m, command the servo to ");
    Serial.print(writeToServo[i]);
    Serial.println(" deg");
  }
}
// Deg2rad
float Deg2Rad(float angleDeg) {
  return angleDeg * (M_PI / 180);
}

// Rad2Deg
float Rad2Deg(float angleRad) {
  return angleRad * (180 / M_PI);
}

// Quadratic
float Quadratic(float a, float b, float c, int plusOrMinus) {
  return (-b + (plusOrMinus)*sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
}

// LandingDistance
float LandingDistance(float d[], float kappa, float lamda, float thetaL_deg) {
  float g = 9.81;
  float d1 = d[0];
  float d2 = d[1];
  float v0 = kappa + lamda * thetaL_deg;
  float thetaL_rad = Deg2Rad(thetaL_deg);
  float x0 = d2 * cos(thetaL_rad);
  float y0 = d2 * sin(thetaL_rad) + d1;
  float v0x = v0 * cos(thetaL_rad);
  float v0y = v0 * sin(thetaL_rad);
  float a = -0.5 * g;
  float b = v0y;
  float c = y0;
  float plusOrMinus = -1;
  float t_land = Quadratic(a, b, c, plusOrMinus);
  float x_land = x0 + v0x * t_land;
  return x_land;
}

// Range Angle Function
float RangeAngle(float d[], float kappa, float lamda) {
  float d1 = d[0];
  float d2 = d[1];
  float maxDistance = 0.0;
  float rangeAngle = 0.0;
  float currentAngle = 0.0;
  float angleStep = 0.05;
  while (currentAngle <= 90.0) {

    float currentDist = LandingDistance(d, kappa, lamda, currentAngle);

    if (currentDist > maxDistance) {
      maxDistance = currentDist;
      rangeAngle = currentAngle;
    }
    currentAngle = currentAngle + angleStep;
  }
  return rangeAngle;
}

// steep angle
float LaunchAngle(float d[], float kappa, float lamda, float xTarget) {
  float thetaL = RangeAngle(d, kappa, lamda);
  float xLand = LandingDistance(d, kappa, lamda, thetaL);
  float angleStep = 0.05;
  while (xLand > xTarget) {
    thetaL += angleStep;
    xLand = LandingDistance(d, kappa, lamda, thetaL);
  }
  return thetaL;
}

// theta servo
float ThetaServo(float H[], float thetaL, float alpha, float beta, float thetaL0) {
  float thetaL_rad = Deg2Rad(thetaL);
  float alpha_rad = Deg2Rad(alpha);
  float thetaL0_rad = Deg2Rad(thetaL0);

  float K1 = H[0] / H[1];
  float K2 = H[0] / H[3];
  float K3 = (pow(H[0], 2) + pow(H[1], 2) - pow(H[2], 2) + pow(H[3], 2)) / (2 * H[1] * H[3]);

  float theta2 = thetaL_rad + thetaL0_rad;

  float a = cos(theta2) - K1 - (K2 * cos(theta2)) + K3;
  float b = -2 * sin(theta2);
  float c = K1 - ((K2 + 1) * cos(theta2)) + K3;

  float t = Quadratic(a, b, c, -1);  // 1 for the positive root
  float theta4 = 2 * atan(t);

  float thetaS_rad = (theta4 + alpha_rad) / (1 - beta);

  return Rad2Deg(thetaS_rad);
}

// TargetServoAngles
void TargetServoAngles(float d[], float kappa, float lambda, float H[], float alpha, float beta, float thetaL0, float xTargetVec[]) {
  // Pseudocode Step 1 & 2: Declare local vectors for intermediate floats
  float localThetaL[6];
  float localThetaS[6];

  for (int i = 0; i < 6; i++) {
    Serial.print("Computing target ");
    Serial.println(i);
    // Serial.print(xTargetVec[i]);
    localThetaL[i] = LaunchAngle(d, kappa, lambda, xTargetVec[i]);
    // Serial.print(" ");
    // Serial.print(localThetaL[i]);
    localThetaS[i] = ThetaServo(H, localThetaL[i], alpha, beta, thetaL0);
    // Serial.print(" ");
    // Serial.print(localThetaS[i]);
    writeToServo[i] = round(localThetaS[i]);
    // Serial.print(" ");
    // Serial.println(writeToServo[i]);
  }
}
