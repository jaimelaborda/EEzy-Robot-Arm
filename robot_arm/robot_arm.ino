/* Arduino Robot Arm controller with servos SG90
 *  by Jaime Laborda Macario
 *  https://github.com/jaimelaborda
 *  
 *  https://github.com/jaimelaborda/EEzy-Robot-Arm
 *  Preliminary version
*/
//DEFINICIONES
#define MAX_BASE 180
#define MIN_BASE 0
#define MAX_HOMBRO 130
#define MIN_HOMBRO 50
#define MAX_CODO 180
#define MIN_CODO 110

#define DEFAULT_BASE 70
#define DEFAULT_HOMBRO 100
#define DEFAULT_CODO 180

#define GRIPPER_OPEN 90
#define GRIPPER_CLOSE 0
#define RAMP_OPEN 100
#define RAMP_CLOSE 0


#include <Servo.h>
#include "robot_arm.h"

Servo base, hombro, codo, gripper, ramp;  // create servo object to control a servo

String recibido = "";
int valores_recibidos[2] = {0, 0};
int indice = 0, indice_1 = 0, i = 0;

void PosicionInicial(void)
{
  base.write(DEFAULT_BASE);
  hombro.write(DEFAULT_HOMBRO);
  codo.write(DEFAULT_CODO);
  gripper.write(GRIPPER_CLOSE);
  ramp.write(RAMP_CLOSE);
}

void SecuenciaRampa(void)
{
  
}

void setup() {
  base.attach(11);  // attaches the servo on pin 9 to the servo object
  hombro.attach(10);
  codo.attach(9);
  gripper.attach(6);
  ramp.attach(5);

  Serial.begin(9600);
  Serial.println("Hola");

  PosicionInicial();
}

void loop() {
  //base.write(90);
  //delay(100);
  //hombro.write(50);
  //delay(100);
  //codo.write(180);
  //delay(50);
  //gripper.write(90);
  //delay(50);
  //gripper.write(0);

  if (Serial.available() > 2) //Mando: "num_servo, posicion_servo". Ejemplo: "1, 180" (pone a 180º la base)
  {

    recibido = "";
    valores_recibidos[0] = 0; //Numero de servo
    valores_recibidos[1] = 0; //Posicion de servo
    indice = 1, indice_1 = 0, i = 0;

    recibido = Serial.readStringUntil('\n');
    //Parseo
    if (recibido.substring(0, 2).equals("S,")) {
      while (indice < recibido.length())
      {
        indice_1 = indice + 1;
        indice = recibido.indexOf(',', indice_1);

        valores_recibidos[i] = recibido.substring(indice_1, indice).toInt();
        i++;
      }
      Serial.println(valores_recibidos[0]);
      Serial.println(valores_recibidos[1]);
    }

    //Interpreto los datos
    if (valores_recibidos[1] >= 0 && valores_recibidos[1] <= 180)
    {
      switch (valores_recibidos[0])
      {
        case 1: //BASE
          if (valores_recibidos[1] >= MIN_BASE && valores_recibidos[1] <= MAX_BASE)
          {
            base.write(valores_recibidos[1]);
          }
          break;

        case 2: //HOMBRO
          if (valores_recibidos[1] >= MIN_HOMBRO && valores_recibidos[1] <= MAX_HOMBRO)
          {
            hombro.write(valores_recibidos[1]);
          }
          break;

        case 3: //CODO
          if (valores_recibidos[1] >= MIN_CODO && valores_recibidos[1] <= MAX_CODO)
          {
            codo.write(valores_recibidos[1]);
          }
          break;

        case 4: //GRIPPER
          if ((valores_recibidos[1] == GRIPPER_OPEN) || (valores_recibidos[1] == GRIPPER_CLOSE))
          {
            gripper.write(valores_recibidos[1]);
          }
          break;

        case 5: //RAMP
          if ((valores_recibidos[1] == RAMP_OPEN) || (valores_recibidos[1] == RAMP_CLOSE))
          {
            ramp.write(valores_recibidos[1]);
          }
          break;
      }
    } else Serial.println("Posicion Fuera de rango");
  }
}

