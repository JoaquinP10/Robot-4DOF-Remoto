/**************************************************************************
 Funcion PWM_Configurar_ServoMotor
 Descripcion: Configura el modulo M0 PWM1 para el control de los servomotores
 en los pines PB4, PB5, PB6 y PB7.
 Se establece una frecuencia de Hz y un ciclo de trabajo de % para la posicion
  minima del servomotor y % para la posicion maxima
 Entradas: Ninguna
 Salidas: Ninguna
 Autor:
 Ultima modificacion: 25 de mayo de 2023
***************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <SERVO.h>

void PWM_Configurar_ServoMotor(void){
    
    SYSCTL_RCGCGPIO_R = 0xF0;
    while((SYSCTL_PRGPIO_R & 0xF0) == 0);

    GPIO_PORTB_AMSEL_R &= ~0xF0; //Desactivar modo analogico
    GPIO_PORTB_DIR_R |= 0xF0; //PB4.7 como salidas
    GPIO_PORTB_DEN_R |= 0xF0; //habilitar como pin digital
    GPIO_PORTB_AFSEL_R |= 0xF0; //habilitar funcion alternativa
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFFFF0000) | (0x44440000); //configurar como PWM

    SYSCTL_RCGCPWM_R |= 0x01; //Habilita senal de reloj
    while((SYSCTL_PRPWM_R & 0x01) == 0); //espera hasta que este listo
    
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
    // Inicializamos PWM0
    PWM0_0_CTL_R |= PWM_0_CTL_ENABLE;
    // Habilitamos la senal PWM0
    PWM0_ENABLE_R |= PWM_ENABLE_PWM0EN;

}