/***************************************************************************************
 Funcion ULTRA_Configura()
 Descripcion: Configura el puerto A para el control del sensor ultrasonico. 
 Se configuran los puertos PB2 como GPIO y PB3 como un temporizador en modo Input Capture (IC)
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 25 de mayo de 2023
****************************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ULTRA.h"

void ULTRA_Configura(void){
    SYSCTL_RCGCGPIO_R |= 0x02;  // Habilitar el reloj del Puerto B
    while((SYSCTL_PRGPIO_R & 0x02) == 0);  // Esperar a que el reloj este listo
    
    GPIO_PORTB_DIR_R |= 0x04;  // PB2 como salida (Trigger)
    GPIO_PORTB_DIR_R &= ~0x08; // PB3 como entrada (Echo)
    GPIO_PORTB_DEN_R |= 0x0C;  // Habilitar la funcion digital para PB2 y PB3

    GPIO_PORTB_AFSEL_R &= ~0x04; // PB2 como GPIO
    GPIO_PORTB_AFSEL_R |= 0x08; // Habilita funcion alternativa en PB3

    GPIO_PORTB_DATA_R &= ~0x02;  // PB2 baja
    
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;  // Asignar a PB3 como Timer IC

    SYSCTL_RCGCTIMER_R |= 0x08;  // Habilitar el reloj del Timer 3
    while((SYSCTL_PRTIMER_R & 0x08) == 0);  // Esperar a que el reloj este listo

    TIMER3_CTL_R &= ~0x01; // Deshabilita Timer3A durante la configuracion
    TIMER3_CFG_R = 0x04; // Temporizador de 16 bits
    TIMER3_TAMR_R |= 0x17; //Configura como Capture Mode, y cuenta ascendente (TIMERTAILR = 0x00)                        
    TIMER3_CTL_R |= 0xC; //captura en flanco de subida y de bajada
    //TIMER3_TAPR_R = 0xFF;            // Maximo valor de preescalado
    //TIMER3_TAILR_R = 0xFFFF;         // Maximo valor de inicio
    //TIMER3_IMR_R |= 0x04; // enable capture match interrupt
    TIMER3_ICR_R = 0x04; // borrar flag de captura
    TIMER3_CTL_R |= 0x01;  // Habilita Timer3A
}

