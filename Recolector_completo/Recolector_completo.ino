//Punto intermedio entre negro y blanco. if ultrasoundRead(Sensor) < sen = negro    if ultrasoundRead(Sensor) > sen = blanco
int sen = 900;
int tot = 0;
int girDer_count = 0;

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
  delay(400);
  motorOff(M4);
  //Girar hacia la izquierda para sacar objeto
  turnLeft(M3, M1);
  delay(650);

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

  //Cerrar pinza
  motorOn(M4, REVERSE);
  delay(350);
  motorOff(M4);

  //Retroceder para volver a ruta
  goReverse(M1, M3);
  delay(400);

  //Encontrar ruta de nuevo
  while (sensorRead(J2) < sen){
    turnRight(M3, M1);
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
  delay(300);
  while (sensorRead(J2) < sen){
  turnRight(M3, M1);
  }
}

void final_totem(){

  //Para hacer dos giros a la derecha
  if (girDer_count < 2){
    giroDer();
    girDer_count++;
  }

  //Luego de hacer los dos giros a la derecha
  else{
    while (ultrasoundRead(J4) < 14){
    goForward(M1, M3);
    }
    motorsOff(M1, M3);
    //Cerrar pinza
    motorOn(M4, FORWARD);
    delay(400);
    motorOff(M4);
    //Llevar totem a la zona propia
    goReverse(M1, M3);
    delay(5000);
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
  motorSpeed(M1,70);
  //Motor izquierdo
  motorSpeed(M3,70);
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
  if (ultrasoundRead(J3) < 14){
    recolector();
    tot++;
  }

  //Para coger a la izquierda desde el inicio
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 0){
    giroIzq();
    tot++;
  }

  //Ruta a seguir habiendo recogido el primer tótem
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot < 4){
    goForward(M1, M3);
  }

  //Ruta a seguir luego de recoger el tercer tótem
  else if (sensorRead(J1) > sen && sensorRead(J2) > sen && tot == 4){
    goForward(M1, M3);
    final_totem();
  }  
}
