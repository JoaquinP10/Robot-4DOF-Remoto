/**************************************************************************
 Funcion PWM_Configurar_ServoMotor
 Descripcion: Configura el modulo M0 PWM1.4 para el control de los servomotores
 en los pines PB4, PB5, PB6 y PB7.
 Se establece una frecuencia de Hz y un ciclo de trabajo de % para la posicion
  minima del servomotor y % para la posicion maxima
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 26 de mayo de 2023
***************************************************************************/
//PB6 M0PWM0 M0 PWM Gen 0
//PB7 M0PWM1 M0 PWM Gen 0
//PB4 M0PWM2 M0 PWM Gen 1
//PB5 M0PWM3 M0 PWM Gen 1

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <SERVO.h>
#define FREQUENCY 50 //Hz
#define SYS_CLOCK 16 000 000 //Hz
#define DIVFREQ 8


void PWM_Configurar_ServoMotor(void){
    
    SYSCTL_RCGCGPIO_R = 0x02; //Habilita senhal de reloj en puerto B
    while((SYSCTL_PRGPIO_R & 0x02) == 0); //Espera hasta que este listo

    GPIO_PORTB_AMSEL_R &= ~0xF0; //Desactivar modo analogico
    GPIO_PORTB_DIR_R |= 0xF0; //PB4.7 como salidas
    GPIO_PORTB_DEN_R |= 0xF0; //habilitar como pin digital
    GPIO_PORTB_AFSEL_R |= 0xF0; //habilitar funcion alternativa
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFFFF0000) | (0x44440000); //configurar como PWM

    SYSCTL_RCGC0_R |= (1<<20); //Habilita senal de reloj de PWM
    
    // Configuramos divisor de frecuencia con 8,
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_8;

    // Generador 0 1: Modo cuenta descendente, inhabilitado
    PWM0_0_CTL_R &= (~0x03);
    PWM1_0_CTL_R &= (~0x03);

    // PWM bajo en load, alto en cmpA
    PWM0_0_GENA_R = 0xC8;
    PWM0_0_GENB_R = 0xC08;
    PWM1_0_GENA_R = 0xC8;
    PWM1_0_GENB_R = 0xC08;

    // frecuencia base = 
    PWM0_0_LOAD_R = ((SYS_CLOCK/DIVFREQ)/FREQUENCY);
    PWM0_1_LOAD_R = ((SYS_CLOCK/DIVFREQ)/FREQUENCY);

    // Ciclo de trabajo = 7.5%
    PWM0_0_CMPA_R = (PWM0_0_LOAD_R * 0.075) - 1;
    PWM0_0_CMPB_R = (PWM0_0_LOAD_R * 0.075) - 1;
    PWM1_0_CMPA_R = (PWM0_1_LOAD_R * 0.075) - 1;
    PWM1_0_CMPB_R = (PWM0_1_LOAD_R * 0.075) - 1;

    // Inicializamos PWM0 PWM1
    PWM0_0_CTL_R |= 0x01;
    PWM0_1_CTL_R |= 0x01;
    
    // Habilitamos la senal PWM0 PWM1
    PWM0_ENABLE_R |= 0x03; //PWM0EN PWM1EN
    PWM0_ENABLE_R |= 0x0C; //PWM2EN PWM3EN

}