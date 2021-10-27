//Punto intermedio entre negro y blanco. if ultrasoundRead(Sensor) < sen = negro    if ultrasoundRead(Sensor) > sen = blanco

int sen = 850;
int tot = 0;
int intersec = 0;

void seguidor(){
  //Si la linea esta en el centro de los dos sensores
  if (sensorRead(J1) < sen  && sensorRead(J2) < sen) {
    goForward(M1,M3);
  }

  //si el sensor de la derecha lee blanco
  else if (sensorRead(J1) > sen && sensorRead(J2) < sen) {
    turnRight(M3, M1);
  }

  //si el sensor de la izquierda lee blanco
  else if (sensorRead(J1) < sen && sensorRead(J2) > sen) {
    turnLeft(M3, M1);
  }
}

void recolector1(){

  motorsOff(M1, M3);
  //Cerrar pinza
  motorOn(M4, FORWARD);
  delay(350);
  motorOff(M4);
  //Girar hacia la izquierda para sacar objeto
  turnRight(M3, M1);
  delay(750);

  //Avanzar para sacar objeto
  goForward(M1, M3);
  delay(600);
  motorsOff(M1, M3);
  

  //Abrir la pinza de nuevo
  motorOn(M4, REVERSE);
  delay(350);
  motorOff(M4);

  //Retroceder para volver a ruta
  goReverse(M1, M3);
  delay(500);

  //Encontrar ruta de nuevo
  while (sensorRead(J1) < sen){
    turnLeft(M3, M1);
  }
}

void recolector2(){

  motorsOff(M1, M3);
  //Cerrar pinza
  motorOn(M4, FORWARD);
  delay(350);
  motorOff(M4);

  //Avanzar para sacar objeto
  goForward(M1, M3);
  delay(150);

  //Abrir la pinza de nuevo
  motorOn(M4, REVERSE);
  delay(350);
  motorOff(M4);

  //Retroceder para volver a ruta
  goReverse(M1, M3);
  delay(700);

  //Encontrar ruta de nuevo
  while (sensorRead(J1) < sen){
    turnLeft(M3, M1);
  }
}

void recolector3(){

  motorsOff(M1, M3);
  //Cerrar pinza
  motorOn(M4, FORWARD);
  delay(350);
  motorOff(M4);
  //Girar hacia la derecha para sacar objeto
  turnRight(M3, M1);
  //AGULO DE GIRO (ANTES= 750)
  delay(850);

  //Avanzar para sacar objeto
  goForward(M1, M3);
  delay(1550);
  motorsOff(M1, M3);
  delay(200);

  //Abrir la pinza de nuevo
  motorOn(M4, REVERSE);
  delay(350);
  motorOff(M4);

  //Retroceder para volver a ruta
  goReverse(M1, M3);
  delay(220);

  //Encontrar ruta de nuevo
  while (sensorRead(J1) < sen){
    turnRight(M3, M1);
  }
  motorSpeed(M1, 70);
  motorSpeed(M3, 70);
}

//Función para que gire hacia la izquierda en interseccion
void giroIzq(){
    goForward(M1, M3);
    delay(100);
    turnLeft(M3, M1);
    delay(300);
    while (sensorRead(J1) < sen){
    turnLeft(M3, M1);
    }
}

//Función para que gire hacia la derecha en interseccion
void giroDer(){
  goForward(M1, M3);
  delay(150);
  turnRight(M3, M1);
  delay(450);
  while (sensorRead(J2) < sen){
  turnRight(M3, M1);
  }
}

void final_totem(){
  motorsOff(M1, M3);
  turnLeft(M3, M1);
  delay(650);
  goForward(M1, M3);
  delay(400);
  motorsOff(M1, M3);
  //Cerrar pinza
  motorOn(M4, FORWARD);
  delay(400);
  motorOff(M4);
  motorSpeed(M1, 80);
  motorSpeed(M3, 80);
  goReverse(M1, M3);
  delay(3000);
  
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

}
void loop () {

  lecturas();
  seguidor();

  //Para primer tótem
  if (ultrasoundRead(J3) < 10 && tot == 1){
    recolector1();
    tot++;
  }

  else if (ultrasoundRead(J3) < 12 && tot == 2){
    recolector2();
    tot++;
  }

  else if (ultrasoundRead(J3) < 10 && tot == 4){
    recolector3();
    tot++;
  }

  //Para coger a la izquierda desde el inicio
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 0){
    giroDer();
    tot++;
  }

  //Ruta a seguir habiendo recogido el primer tótem
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot > 0 && tot < 3){
    goForward(M1, M3);
  }

  //Ruta a seguir luego de recoger el tercer tótem
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 3){
    giroIzq();
    tot++;
  }
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 4){
    goForward(M1, M3);
  }
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 5){
    final_totem();
  }
}
