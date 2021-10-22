//CALIBRACIÓN DE SENSORES
int Der = 900;
int Izq = 900;

void seguidor(){
  //Si la linea esta en el centro de los dos sensores
  if (sensorRead(J1) < Der  && sensorRead(J2) < Izq) {
    goForward(M1,M3);
  }

  //si el sensor de la derecha lee blanco
  else if (sensorRead(J1) > Der && sensorRead(J2) < Izq) {
    turnRight(M3, M1);
  }

  //si el sensor de la izquierda lee blanco
  else if (sensorRead(J1) < Der && sensorRead(J2) > Izq) {
    turnLeft(M3, M1);
  }
}

void recolector(){
  motorOn(M4, FORWARD);
  delay(400);
  motorOff(M4);
  turnLeft(M3, M1);
  delay(350);
  goForward(M1, M3);
  delay(1000);
  goReverse(M1, M3);
  delay(300);
  motorsOff(M1, M3);
  motorOn(M4, REVERSE);
  delay(200);
  motorOff(M4);
  motorSpeed(M1, 80);
  motorSpeed(M3, 80);
  goReverse(M1, M3);
  delay(500);
  while (sensorRead(J2) < Izq){
    turnRight(M3, M1);
  }
}

//Función para que gire hacia la izquierda en interseccion
void giroIzq(){
    goForward(M1, M3);
    delay(200);
    turnLeft(M3, M1);
    delay(700);
    while (sensorRead(J1) < Der){
    turnLeft(M3, M1);
    }
}

//Función para que gire hacia la derecha en interseccion
void giroDer(){
  goForward(M1, M3);
  delay(200);
  turnRight(M3, M1);
  delay(700);
  while (sensorRead(J2) < Izq){
  turnRight(M3, M1);
  }
}

//Para imprimir lecturas del sensor infrarrojo
void lecturas(){
  Serial.print("J2 = ");
  Serial.print(sensorRead(J2));
  Serial.print("        ");
  Serial.print("J1 = ");  
  Serial.println(sensorRead(J1));
  
  delay(50);
}

void setup () {
  Serial.begin(9600);

  //Motor derecho
  motorSpeed(M1,80);
  //Motor izquierdo
  motorSpeed(M3,80);
  motorOn(M4, REVERSE);
  delay(200);

}
void loop () {

  lecturas();
  seguidor();

  if (sensorRead(J1) > Der && sensorRead(J2) > Izq) {
    goForward(M3, M1);
  }
  else if (ultrasoundRead(J3) <= 12){
    recolector();
  }
  
  //si los dos sensores leen blanco (intersección)
  
}
