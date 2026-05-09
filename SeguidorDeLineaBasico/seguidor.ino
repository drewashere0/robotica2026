#include "variables.h"
void LecturaSensores() {//lee cada sensor y escribe el valor leido en el monitor serial
 sigueLineas.read(sensorValues);

  Serial.print(S0);
  Serial.print(" ");
  Serial.print(S1);
  Serial.print(" ");
  Serial.print(S2);
  Serial.print(" ");
  Serial.print(S3);
  Serial.print(" ");
  Serial.print(S4);
  Serial.print(" ");
  Serial.print(S5);
  Serial.print(" ");
  Serial.print(S6);
  Serial.print(" ");
  Serial.println(S7);

  delay(100);
}

void seguidor() {  //seguidor de linea usando como base el umbral y los colores blanco y negro
  if (S0 > umbral && S1 > umbral && S2 < umbral && S3 < umbral && S4 < umbral && S5 < umbral && S6 < umbral && S7 < umbral) {  // N N B B B B B B
    Motor(60, 180);
  }
  if (S0 < umbral && S1 > umbral && S2 > umbral && S3 < umbral && S4 < umbral && S5 < umbral && S6 < umbral && S7 < umbral) {  //B N N B B B B B
    Motor(80, 160);
  }
  if (S0 < umbral && S1 < umbral && S2 > umbral && S3 > umbral && S4 < umbral && S5 < umbral && S6 < umbral && S7 < umbral) {  // B B N N B B B B
    Motor(100, 140);
  }
  if (S0 < umbral && S1 < umbral && S2 < umbral && S3 > umbral && S4 > umbral && S5 < umbral && S6 < umbral && S7 < umbral) {  // B B B N N B B B
    Motor(120, 120);
  }
  if (S0 < umbral && S1 < umbral && S2 < umbral && S3 < umbral && S4 > umbral && S5 > umbral && S6 < umbral && S7 < umbral) {  // B B B B N N B B
    Motor(140, 100);
  }
  if (S0 < umbral && S1 < umbral && S2 < umbral && S3 < umbral && S4 > umbral && S5 > umbral && S6 > umbral && S7 < umbral) {  //B B B B B N N B
    Motor(160, 80);
  }
  if (S0 < umbral && S1 < umbral && S2 < umbral && S3 < umbral && S4 < umbral && S5 < umbral && S6 > umbral && S7 > umbral) {  //B B B B B B N N
    Motor(180, 60);
  }
}

void segpos() {  //Seguidor de linea basado en la posicion relativa del robot
  int posicion = sigueLineas.readLineBlack(sensorValues);
  posicion = map(posicion, 0, 7000, -255, 255);
  Serial.print(posicion);
  Serial.println();

  if ((posicion <= 255) && (posicion > 200)) {  //extremo izquierdo de la linea/giro 90 izquierda
    Motor(-25, 125);
  }

  else if ((posicion <= 200) && (posicion >= 150)) {  //medio izquierdo de la linea/giro medio izquierda
    Motor(-10, 100);

  } else if ((posicion <= 150) && (posicion > 10)) {  //bajo izquierdo de la linea/giro bajo izquierda
    Motor(80, 90);
  }
  else if ((posicion <= 10) && (posicion >= -10)) {  //centro
    Motor(85, 85);
    giroI = false;
    giroD = false;
    gap = false;
  }

  else if ((posicion <= -10) && (posicion > -150)) {  //bajo derecho de la linea/giro bajo derecha
    Motor(90, 80);
  }

  else if ((posicion <= -150) && (posicion >= -200)) {  //media derecho de la linea/giro medio derecha
    Motor(100, -10);
  }

  else if ((posicion <= -200) && (posicion >= -255)) {  //extremo derecho de la linea/giro 90 derecha
    Motor(125, -25);
 
}
}

void casosEsp() {
  if ((N(S0) && N(S1) && N(S3) && N(S4) && B(S7))) {  // giro de 90 grados hacia la izquierda
    giroI = true;
  }
  if ((B(S0) && N(S3) && N(S4)  && N(S6) && N(S7))) {  //giro de 90 grados hacia la derecha
    giroD = true;
  }
   if (B(S0) && B(S1) && B(S2) && B(S3) && B(S4) && B(S5) && B(S6) && B(S7)) {  //espacios en blanco (gap)
    gap = true;
  }

  if (giroI == true) {
    while (!(B(S0) && B(S1) && B(S2) && B(S3) && B(S4) && B(S5) && B(S6) && B(S7))) {//seguira girando hasta no detectar una linea negra
      Motor(-120, 120);
      sigueLineas.read(sensorValues);
     
    }
  }
  if (giroD == true) {
    while (!(B(S0) && B(S1) && B(S2) && B(S3) && B(S4) && B(S5) && B(S6) && B(S7))) {//seguira girando hasta no detectar una linea negra
      Motor(120, -120);
      sigueLineas.read(sensorValues);
   
    }
  }
    if (gap == true){
       while (!(B(S0) && B(S1) && B(S2) && B(S3) && B(S4) && B(S5) && B(S6) && B(S7))) {//Seguira girando hasta no detectar una linea negra
      Motor(100,100);
      sigueLineas.read(sensorValues);
   
    }

    }
   giroI = false;
      giroD = false;
      gap = false;
}
void calibrar() {
  Motor(150, -150);
  for (int i = 0; i < 70; i++) {
    sigueLineas.calibrate();
  }
}
