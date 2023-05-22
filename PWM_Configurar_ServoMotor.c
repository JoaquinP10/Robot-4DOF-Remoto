/**************************************************************************
 Funcion PWM_Configurar_ServoMotor
 Descripcion: Configura el modulo M0 PWM1 para el control del servomotor. 
 Se establece una frecuencia de 50Hz y un ciclo de trabajo de 5% para la 
 posicion minima del servomotor y 10% para la posicion maxima.
 Entradas: Ninguna
 Salidas: Ninguna
 Autor:
 Ultima modificacion: 20 de mayo de 2023
***************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <SERVO.h>

void PWM_Configurar_ServoMotor(void){
    
    SYSCTL_RCGCPWM_R |= 0x01;
    while((SYSCTL_PRPWM_R & 0x01) == 0);

    // Configuramos divisor de frecuencia con 4
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_4;

    // Generador 0: Modo cuenta descendente, inhabilitado
    PWM0_0_CTL_R = 0;
    // PWM bajo en load, alto en cmpA
    PWM0_0_GENA_R = 0xC8;
    // frecuencia base = 
    PWM0_0_LOAD_R = ;
    // Ciclo de trabajo = 
    PWM0_0_CMPA_R = ;
    // Habilitamos el generador 0
    PWM0_0_CTL_R |= PWM_0_CTL_ENABLE;
    // Habilitamos la señal PWM
    PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN;

}