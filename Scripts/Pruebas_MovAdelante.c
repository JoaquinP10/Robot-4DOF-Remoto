/**************************************************************************
 Programa Pruebas_MovAdelante
 Descripcion: Implementa las funciones creadas para simular el movimiento 
 del robot hacia adelante
 Estado:
 18 de junio: Version 1.0. El robot se desplaza hacia adelante. Falta
 optimizar la friccion del pie de apoyo y buscar hacer el mov mas rapido y fluido
 
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

void Config_Servos(void){

SYSCTL_RCGCGPIO_R |= 0x02; //Habilita senhal de reloj en puerto B
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
    PWM0_1_CTL_R &= (~0x03);

    // PWM bajo en load, alto en cmpA
    PWM0_0_GENA_R = 0xC8;
    PWM0_0_GENB_R = 0xC08;
    PWM0_1_GENA_R = 0xC8;
    PWM0_1_GENB_R = 0xC08;

    // Frecuencia = 50 Hz - LOAD = 40 000 = (sys_clock/(div_freq*freq))
    PWM0_0_LOAD_R = 40000 - 1;
    PWM0_1_LOAD_R = 40000 - 1;

    // Ciclo de trabajo inicial = 7.5%
    PWM0_0_CMPA_R = (40000 * 7.5)/100 - 1;
    PWM0_0_CMPB_R = (40000 * 7.5)/100 - 1;
    PWM0_1_CMPA_R = (40000 * 7.5)/100 - 1;
    PWM0_1_CMPB_R = (40000 * 7.5)/100 - 1;

    // Inicializamos PWM0 PWM1
    PWM0_0_CTL_R |= 0x01;
    PWM0_1_CTL_R |= 0x01;

    // Habilitamos la senal PWM0 PWM1
    PWM0_ENABLE_R |= 0x03; //PWM0EN PWM1EN
    PWM0_ENABLE_R |= 0x0C; //PWM2EN PWM3EN

}

void Servos_Rotacion(double duty_cycle1, double duty_cycle2, double duty_cycle3, double duty_cycle4){ //angulo de 0 a 180

    if (((duty_cycle1 >= 5) && (duty_cycle1 <= 10)) && ((duty_cycle2 >= 5) && (duty_cycle2 <= 10)) && ((duty_cycle3 >= 5) && (duty_cycle3 <= 10)) && ((duty_cycle4 >= 5) && (duty_cycle4 <= 10))){
        PWM0_0_CMPA_R = (LOAD * duty_cycle1)/100 - 1; //SERVO1
        PWM0_0_CMPB_R = (LOAD * duty_cycle2)/100 - 1; //SERVO2
        PWM0_1_CMPA_R = (LOAD * duty_cycle3)/100 - 1; //SERVO3
        PWM0_1_CMPB_R = (LOAD * duty_cycle4)/100 - 1; //SERVO4
    }
}

void main(void){
    uint32_t i = 0;
    double j =0;
    Config_Servos();
    while(1){

        Servos_Rotacion(9, 9, 7.5, 7.5);
        for(i=0; i<1000000; i++);

        for(j=0; j<=300; j++){
            Servos_Rotacion(9 - 3*j/(double)300, 9 - 3*j/(double)300, 7.5 + 1.2*j/(double)300 , 7.5 + 0.5*j/(double)300);
            for(i=0; i <1000; i++);
        }

        for(i=0; i<500000; i++);

        for(j=0; j<=300; j++){
            Servos_Rotacion(6, 6, 8.7 - 1.2*j/(double)300 , 8 - 0.5*j/(double)300);
            for(i=0; i <1000; i++);
        }

        for(i=0; i<500000; i++);

        for(j=0; j<=300; j++){
            Servos_Rotacion(6 + 3*j/(double)300, 6 + 3*j/(double)300, 7.5-0.5*j/(double)300 , 7.5-1.2*j/(double)300);
            for(i=0; i <1000; i++);
        }

        for(i=0; i<500000; i++);

        for(j=0; j<=300; j++){
            Servos_Rotacion(9, 9, 7+0.5*j/(double)300 , 6.3 + 1.2*j/(double)300);
            for(i=0; i <1000; i++);
        }

    }
}