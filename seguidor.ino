int Der = 970;
int Izq = 960;


void setup () {
  Serial.begin(9600);
  motorSpeed(M1,63);
  motorSpeed(M2,60);

}
void loop () {
   Serial.print("J2 = ");
  Serial.print(sensorRead(J2));

  Serial.print("        ");
  
  Serial.print("J1 = ");  
  Serial.println(sensorRead(J1));
  
  delay(50);
  
 if (sensorRead(J1) < Der  && sensorRead(J2) < Izq) {
    goForward(M1,M2);
  } else if (sensorRead(J1) > Der && sensorRead(J2) < Izq) {
    turnRight(M2 , M1);
  } else if (sensorRead(J1) < Der && sensorRead(J2) > Izq) {
      turnLeft(M2 , M1);
  } else {
    motorsOff(M1, M2);
   
 }
 
}
