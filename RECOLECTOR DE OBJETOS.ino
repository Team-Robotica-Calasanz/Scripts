int Der = 975;
int Izq = 970;
int OR = 0;

void Objeto() {
  motorsOff(M1,M2);
    motorOn(M3, REVERSE);
    delay(400);
    motorOff(M3);
    delay(500);
    goForward(M1,M2);
    delay(150);
    motorsOff(M1,M2);
    motorOn(M3, FORWARD);
    delay(400);
    motorOff(M3);
    delay(500);
    turnLeft(M2,M1);
    delay(700);
    goForward(M1,M2);
    delay(500);
    motorsOff(M1 , M2);
    motorOn(M3, REVERSE);
    delay(500);
    motorOff(M3);
    goReverse(M1, M2);
    delay(500);
    turnRight(M2, M1);
    delay(700);
    motorsOff(M1,M2);
}


void setup() {
  Serial.begin(9600);
    motorOn(M1, FORWARD);
    motorOn(M2, FORWARD);
    delay(50);
    motorSpeed(M1, 84);
    motorSpeed(M2, 80); 

}



void loop() {

  Serial.print("J1= ");
  Serial.print(sensorRead(J1));
  Serial.print(" ");
  Serial.print("J2= ");
  Serial.println(sensorRead(J2));
  //Serial.print(" ");
  //Serial.print("US= ");
  //Serial.println(ultrasoundRead(J3));


  if(sensorRead(J1) < Der && sensorRead(J2) < Izq) { //ambos negros 
   goForward(M1, M2);
  }
  else if(sensorRead(J1) < Der && sensorRead(J2) > Izq) { // +
  turnLeft(M2, M1);
  }
  else if(sensorRead(J1) > Der && sensorRead(J2) < Izq) {
  turnRight(M2, M1);
  }
  else if(ultrasoundRead(J3) <= 12) {
  Objeto(); 
    int OR = OR + 1;
  }
  else {
    turnLeft(M2, M1);
    delay(640);
  }
}
 /* else if(sensorRead(J1) > Der && sensorRead(J2) > Izq) {
    goForward(M1, M2);
    delay(400);
    while (sensorRead(J1) > Der){
      turnLeft(M1, M2);
    }
    while (sensorRead(J1) < Der){
      turnLeft(M1, M2);
    }*/
 // }
  //else if(sensorRead(J1) > Der && sensorRead(J2) > Izq && OR == 3) {
    //goForward(M1, M2);
    //delay(300);}
    //turnLeft(M2, M1);
    //delay(300);
    //while(sensorRead(J1) < Der) 
    //turnLeft(M2, M1); 
  //}
    