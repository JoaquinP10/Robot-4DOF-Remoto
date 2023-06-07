
//Servo 1 
//Servo 2
//Servo 3
//Servo 4

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "SERVO.h"

#define LOAD 40000
#define SERVO1 1
#define SERVO2 2
#define SERVO3 3
#define SERVO4 4

void Servo_Rotacion(uint8_t Servo, uint16_t angulo){ //angulo de 0 a 180
    double duty_cycle = angulo/double(36) + 5; //relacion entre angulo de rotacion y ciclo de trabajo
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
    else{
        //you shouldn't be here
    }
    
}