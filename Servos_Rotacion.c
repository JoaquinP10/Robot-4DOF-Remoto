/**************************************************************************
 Funcion Servo_Rotacion
 Descripcion: Genera rotaciones en los 4 servos con un ciclo de un trabajo
 entre 5 y 10%
 Entradas: 4 angulos de giro
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 19 de junio de 2023
***************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define LOAD 40000
#define SERVO1 1 //PB6
#define SERVO2 2 //PB7
#define SERVO3 3 //PB4
#define SERVO4 4 //PB5

void Servo_Rotacion(double duty_cycle1, double duty_cycle2, double duty_cycle3, double duty_cycle4){ //angulo de 0 a 180
    
    if (((duty_cycle1 >= 5) && (duty_cycle1 <= 10)) && ((duty_cycle2 >= 5) && (duty_cycle2 <= 10)) && ((duty_cycle3 >= 5) && (duty_cycle3 <= 10)) && ((duty_cycle4 >= 5) && (duty_cycle4 <= 10))){
		PWM0_0_CMPA_R = (LOAD * duty_cycle1)/100 - 1; //SERVO1
		PWM0_0_CMPB_R = (LOAD * duty_cycle2)/100 - 1; //SERVO2
		PWM0_1_CMPA_R = (LOAD * duty_cycle3)/100 - 1; //SERVO3
		PWM0_1_CMPB_R = (LOAD * duty_cycle4)/100 - 1; //SERVO4
    }
}

void main(void){
    Servos_Rotacion(7.5, 7.5, 7.5, 7.5);
    while(1);
}
