#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "TivaES.h"


#define FREQUENCY 50 //Hz
#define SYS_CLOCK 16000000 //Hz
#define DIVFREQ 8
#define LOAD 40000

void delay(uint32_t cuenta);
void PWM_Configurar_Servomotor(void);

void main(void){

    uint32_t i =0;
    double duty_cycle=5;
    uint8_t estado;
    TivaES_Inicializa();
    PWM_Configurar_Servomotor();
    while(1){
	PWM0_0_CMPA_R = (40000 * duty_cycle)/100 - 1;
        TivaES_Espera_Pulsadores();
	if (estado==1){
	    if ((10 - duty_cycle) < 0.1) duty_cycle+=0.1;
	    delay(10000);
	}
	else if (estado==2){
	    if ((duty_cycle-5) < 0.1) duty_cycle-=0.1;
	    delay(10000);
	}
    }

}

void delay(uint32_t cuenta){
    uint32_t i;
    for(i=0; i<cuenta; i++);
}

void PWM_Configurar_Servomotor(void){

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
    PWM0_1_CTL_R &= (~0x03);

    // PWM bajo en load, alto en cmpA
    PWM0_0_GENA_R = 0xC8;
    PWM0_0_GENB_R = 0xC08;
    PWM0_1_GENA_R = 0xC8;
    PWM0_1_GENB_R = 0xC08;

    // Frecuencia = 50 Hz - LOAD = 40 000
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



