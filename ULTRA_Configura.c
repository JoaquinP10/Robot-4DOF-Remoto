/***************************************************************************************
 Funcion ULTRA_Configura()
 Descripcion: Configura el puerto A para el control del sensor ultrasonico. 
 Se configuran los puertos PB2 y PB3 como un temporizador en modo Input Capture (IC)
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 20 de mayo de 2023
****************************************************************************************/

#include "tm4c123fg6pm.h"
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
    
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;  // Asignar a PB3 como Timer IC

    SYSCTL_RCGCTIMER_R |= 0x08;  // Habilitar el reloj del Timer 3
    while((SYSCTL_PRTIMER_R & 0x08) == 0);  // Esperar a que el reloj este listo

    /*

    #define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable

    #define TIMER_CFG_16_BIT        0x00000004  // 16-bit timer configuration,
                                                // function is controlled by bits
                                                // 1:0 of GPTMTAMR and GPTMTBMR
    #define TIMER_TAMR_TACMR        0x00000004  // GPTM TimerA Capture Mode
    #define TIMER_TAMR_TAMR_CAP     0x00000003  // Capture mode
    #define TIMER_CTL_TAEN          0x00000001  // GPTM TimerA Enable
    #define TIMER_CTL_TAEVENT_POS   0x00000000  // Positive edge
    #define TIMER_IMR_CAEIM         0x00000004  // GPTM CaptureA Event Interrupt
                                                // Mask
    #define TIMER_ICR_CAECINT       0x00000004  // GPTM CaptureA Event Interrupt
                                                // Clear
    #define TIMER_TAILR_M           0xFFFFFFFF  // GPTM Timer A Interval Load
                                                // Register

                                                
    TIMER3_CTL_R &= ~0x08; // disable timer0A during setup
    TIMER3_CFG_R = 0x04; // configure for 16-bit timer mode
    TIMER3_TAMR_R = (TIMER3_TAMR_R & ~0xFFF) + 7
                                    // configure for rising edge event
    TIMER3_CTL_R &= ~(TIMER_CTL_TAEVENT_POS|0xC);
    TIMER3_TAILR_R = 0xFFFF;         // max start value
    TIMER3_TAPR_R = 0xFF;            // max prescale value
    TIMER3_IMR_R |= TIMER_IMR_CAEIM; // enable capture match interrupt
    TIMER3_ICR_R = TIMER_ICR_CAECINT;// clear timer0A capture match flag
    TIMER3_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 16-b, +edge timing, interrupts
                                    // Timer0A=priority 2
    NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
    NVIC_EN0_R = NVIC_EN0_INT19;     // enable interrupt 19 in NVIC
    */



}

