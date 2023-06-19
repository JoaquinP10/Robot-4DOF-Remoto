/**************************************************************************
 Funcion Servo_Rota_DutyCycle
 Descripcion: Genera un giro en uno de los servos en un angulo entre
 en un duty_cycle de 5 a 10%
 Entradas: Servo a efectuar el giro, ciclo de trabajo
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

void Servo_Rota_DutyCycle(uint8_t Servo, double duty_cycle){ //angulo de 0 a 180

    if (((Servo >= SERVO1) && (Servo <= SERVO4)) && ((duty_cycle >= 5) && (duty_cycle <= 10))){
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
    Servo_Rota_DutyCycle(SERVO3, 6);
    while(1);
}
