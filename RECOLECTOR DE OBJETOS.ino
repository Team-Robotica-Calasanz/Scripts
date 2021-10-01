void setup() {  //hola

   Serial.begin(9600);
  motorSpeed(M1,100);
  motorSpeed(M2,98.2380952381);
  motorSpeed(M3,75);
  motorOff(M3);
  motorsOff(M1, M2);
  
}

void loop() {
  Serial.println(ultrasoundRead(J3));
  goForward(M1,M2);
  if (ultrasoundRead(J3) <= 30) {
    motorOn(M3, REVERSE);
    delay(400);
    motorOff(M3);
    delay(500);
    goForward(M1,M2);
    if (ultrasoundRead(J3) <= 15) {
      motorsOff(M1 , M2);
      motorOn(M3,FORWARD);
      delay(700);
      motorOff(M3);  //Aqui agarra el obejto y se cierra
      turnRight(M1,M2);
      delay(1400);
      goForward(M1,M2);
      delay(3150);
      motorsOff(M1 , M2);
      motorOn(M3, REVERSE);
      delay(400); //Aqui ya suelta el objeto
      goReverse(M1 , M2);
      delay(1000);
      motorsOff(M1,M2);
      motorOn(M3,FORWARD);
      delay(400);
      motorOff(M3);
    }
  }
  
  
}

