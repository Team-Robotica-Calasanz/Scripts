int Der = 900;
int Izq = 900;
//hola
//Codigo para que gire hacia la izquierda en interseccion
void giroIzquierda(){
    goForward(M1, M2);
    delay(200);
    turnLeft(M2, M1);
    delay(700);
    while (sensorRead(J1) < Der){
    turnLeft(M2, M1);
    }
  }

//Codigo para que gire hacia la izquierda en interseccion
void giroDerecha(){
  goForward(M1, M2);
  delay(200);
  turnRight(M2, M1);
  delay(700);
  while (sensorRead(J1) < Der){
  turnRight(M2, M1);
  }
}
 


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
  } 
 else if (sensorRead(J1) > Der && sensorRead(J2) < Izq) {
    turnRight(M2 , M1);
  } 
 else if (sensorRead(J1) < Der && sensorRead(J2) > Izq) {
      turnLeft(M2 , M1);
  } 

  else if (sensorRead(J1) > Der && sensorRead(J2) > Izq) {
      giroDerecha();
  } 
 /*else if (sensorRead(J1) > Der && sensorRead(J2) > Izq){
  while (sensorRead(J2) > Izq){
    turnLeft(M2, M1);*/
  
  
  
}

