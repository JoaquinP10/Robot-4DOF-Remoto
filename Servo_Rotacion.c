/**************************************************************************
 Funcion Servo_Rotacion
 Descripcion: Genera un giro en uno de los servos en un angulo entre
 0 y 180 grados aproximadamente
 Entradas: Servo a efectuar el giro, angulo de giro
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 13 de junio de 2023
***************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define LOAD 40000
#define SERVO1 1 //PB6
#define SERVO2 2 //PB7
#define SERVO3 3 //PB4
#define SERVO4 4 //PB5

void Servo_Rotacion(uint8_t Servo, uint16_t angulo){ //angulo de 0 a 180
    double duty_cycle = angulo/(double)36 + 5; //relacion entre angulo de rotacion y ciclo de trabajo

    if (((Servo >= SERVO1) && (Servo <= SERVO4)) && ((angulo >= 0) && (Servo <= 180))){
        if (Servo == SERVO1){
            PWM0_0_CMPA_R = (LOAD * duty_cycle)/100 - 1;
        }
        else if (Servo == SERVO2){
            PWM0_0_CMPB_R = (LOAD * duty_cycle)/100 - 1;
        }
        else if (Servo == SERVO3){
            PWM0_1_CMPA_R = (LOAD * duty_cycle)/100 - 1;
        }
        else if (Servo == SERVO4){
            PWM0_1_CMPB_R = (LOAD * duty_cycle)/100 - 1;
        }
        else{ //you shouldn't be here
            while(1);
        }
    }
}

void main(void){
    Servo_Rotacion(SERVO3, 180);
    while(1);
}
