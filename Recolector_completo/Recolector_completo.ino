//Punto intermedio entre negro y blanco. if ultrasoundRead(Sensor) < sen = negro    if ultrasoundRead(Sensor) > sen = blanco
int sen = 900;
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

void recolector(){

  motorsOff(M1, M3);
  //Cerrar pinza
  motorOn(M4, FORWARD);
  delay(350);
  motorOff(M4);
  //Girar hacia la izquierda para sacar objeto
  turnRight(M3, M1);
  delay(450);

  //Avanzar para sacar objeto
  goForward(M1, M3);
  delay(600);
  motorsOff(M1, M3);
  delay(1000);

  //Retroceder por si el objeto está caido
  goReverse(M1, M3);
  delay(200);

  motorsOff(M1, M3);
  delay(200);

  //Abrir la pinza de nuevo
  motorOn(M4, REVERSE);
  delay(700);
  motorOff(M4);

  //Retroceder para volver a ruta
  goReverse(M1, M3);
  delay(400);

  //Encontrar ruta de nuevo
  while (sensorRead(J1) < sen){
    turnLeft(M3, M1);
  }
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
  delay(100);
  turnRight(M3, M1);
  delay(400);
  while (sensorRead(J2) < sen){
  turnRight(M3, M1);
  }
}

void final_totem(){
  while (ultrasoundRead(J3) > 17){
    seguidor();
  }
  goForward(M1, M3);
  delay(300);
  motorsOff(M1, M3);
  motorOn(M4, FORWARD);
  delay(350);
  motorOff(M4);
  goReverse(M1, M3);
  delay(5000);
  
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
  motorOn(M4, FORWARD);
  delay(350);
  motorOn(M4, REVERSE);
  delay(350);
  motorOff(M4);

}
void loop () {

  lecturas();
  seguidor();

  //Si hay un tótem adelante
  if (ultrasoundRead(J3) < 13){
    recolector();
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
    giroDer();
    tot++;
  }
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 6){
    giroIzq();
    final_totem();
  }
}
