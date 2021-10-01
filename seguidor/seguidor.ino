//CALIBRACIÓN DE SENSORES
int Der = 900;
int Izq = 900;

//Función para que gire hacia la izquierda en interseccion
void giroIzq(){
    goForward(M1, M2);
    delay(200);
    turnLeft(M2, M1);
    delay(700);
    while (sensorRead(J1) < Der){
    turnLeft(M2, M1);
    }
}

//Función para que gire hacia la izquierda en interseccion
void giroDer(){
  goForward(M1, M2);
  delay(200);
  turnRight(M2, M1);
  delay(700);
  while (sensorRead(J2) < Izq){
  turnRight(M2, M1);
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
  motorSpeed(M1,53);
  //Motor izquierdo
  motorSpeed(M2,50);

}
void loop () {

  lecturas();

  //Si la linea esta en el centro de los dos sensores
  if (sensorRead(J1) < Der  && sensorRead(J2) < Izq) {
    goForward(M1,M2);
  }

  //si el sensor de la derecha lee blanco
  else if (sensorRead(J1) > Der && sensorRead(J2) < Izq) {
    turnRight(M2 , M1);
  }

  //si el sensor de la izquierda lee blanco
  else if (sensorRead(J1) < Der && sensorRead(J2) > Izq) {
      turnLeft(M2 , M1);
  }

  //si los dos sensores leen blanco (intersección)
  else if (sensorRead(J1) > Der && sensorRead(J2) > Izq) {
    //Intrucciones para girar a la izquierda, derecha o seguir derehco
    //giroDer();
    //giroIzq();
    //goForward(M2, M1);
  }
}
