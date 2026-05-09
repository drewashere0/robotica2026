#include <QTRSensors.h>
#include "variables.h"

QTRSensors sigueLineas;

const uint8_t SensorCount = 8;

uint16_t sensorValues[SensorCount];

int umbral = 4000, posicion,boton;

const int frecuencia = 5000,resolucion = 8;



bool giroI = false,giroD = false,gap = false;


#define N(sensor) ((sensor) >= umbral)
#define B(sensor) ((sensor) < umbral)

void setup() {

  Serial.begin(9600);

  sigueLineas.setTypeAnalog();

  sigueLineas.setSensorPins((const uint8_t[])

                              { 36, 39, 34, 35, 32, 33, 25, 26 },
                            SensorCount);

  sigueLineas.setEmitterPin(27);
  
  motorSetup();

  while (boton == 0) {
    boton = digitalRead(BOTON);
  }
  boton = 0;

  calibrar();
  Motor(0, 0);

  while (boton == 0) {
    boton = digitalRead(BOTON);
  }

  boton = digitalRead(BOTON);
}

void loop() {
  sigueLineas.read(sensorValues);

  segpos();
}
