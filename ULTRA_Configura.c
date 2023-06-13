/***************************************************************************************
 Funcion ULTRA_Configura()
 Descripcion: Configura el puerto A para el control del sensor ultrasonico. 
 Se configuran los puertos PB2 como GPIO y PB3 como un temporizador en modo Input Capture (IC)
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 13 de junio de 2023
****************************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ULTRA.h"

#define TRIGGER (1<<3) //PB3
#define ECHO (1<<2) //PB2

void ULTRA_Configura(void){
    SYSCTL_RCGCGPIO_R |= 0x02;  // Habilitar el reloj del Puerto B
    while((SYSCTL_PRGPIO_R & 0x02) == 0);  // Esperar a que el reloj este listo

    GPIO_PORTB_DIR_R |= TRIGGER;  // PB3 como salida (Trigger)
    GPIO_PORTB_DIR_R &= ~(ECHO); // PB2 como entrada (Echo)
    GPIO_PORTB_DEN_R |= (TRIGGER | ECHO);  // Habilitar la funcion digital para PB2 y PB3

    GPIO_PORTB_AFSEL_R &= ~(TRIGGER); // PB3 como GPIO
    GPIO_PORTB_AFSEL_R |= ECHO; // Habilita funcion alternativa en PB2

    GPIO_PORTB_DATA_R &= ~(TRIGGER);  // PB3 baja

    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFF0FF) | 0x00000700;  // Asignar a PB2 como Timer IC

    SYSCTL_RCGCTIMER_R |= 0x08;  // Habilitar el reloj del Timer 3
    while((SYSCTL_PRTIMER_R & 0x08) == 0);  // Esperar a que el reloj este listo

    TIMER3_CTL_R &= ~0x01; // Deshabilita Timer3A durante la configuracion
    TIMER3_CFG_R |= 0x04; // Temporizador de 16 bits
    TIMER3_TAMR_R |= 0x17; //Configura como Capture Mode, y cuenta ascendente (TIMERTAILR = 0x00)
 //   TIMER3_TAPR_R |= 0x02;
    TIMER3_CTL_R |= 0x0C; //captura en flanco de subida y de bajada
    TIMER3_CTL_R |= 0x01;  // Habilita Timer3A
}

