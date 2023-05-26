/***************************************************************************************
 Funcion UART_ConfigurarBluetooth
 Descripcion: Configura el modulo UART1 para la comunicacion mediante Bluetooth. Se
 establece una velocidad de transmision de 9600 baudios y se habilita la interrupcion de
 recepcion. Se configuran los pines PB0 y PB1 como entrada/salida UART1
 respectivamente. Asimismo, se configuran los pines PA0 y PA1 como entrada/salida
 respectivamente para determinar si es que el modulo es esclavo o maestro y su estado de
 coneccion.
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: 
 Ultima modificacion: 25 de mayo de 2023
****************************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>
#include "UART.h"

void UART_ConfigurarBluetooth(void){
    //activar senal de reloj GPIO en A
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R0;
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);
    //activar senal de reloj GPIO en B
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1;
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0);
    //activar senal de reloj UART en B
    SYSCTL_RCGC1_R = SYSCTL_RCGC1_UART1;
    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R1) == 0);

    //Desactivar el modulo UART
    UART1_CTL_R &= ~UART_CTL_UARTEN;

    //Configurar PB0 PB1
    GPIO_PORTB_AMSEL_R &= ~(0x03); //Funciones analogicas desactivadas en PB0 PB1
    GPIO_PORTB_DEN_R |= 0x03; //Se habilitan funciones digitales
    GPIO_PORTB_AFSEL_R |= 0x03; //Se habilita funcion alternativa

    //Se escogen los nibbles con el valor que corresponde a U1Tx y U1Rx 
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00)|0x00000011; 

    //Configurar PA0 PA1
    GPIO_PORTA_DIR_R = (GPIO_PORTA_DIR_R & (~0x01)) | (0x20); //Coloca a PA0 como entrada y PA1 como salida
    GPIO_PORTA_AMSEL_R &= ~(0x03); //Funciones analogicas desactivadas en PB0 PB1
    GPIO_PORTA_DEN_R |= 0x03; //Se habilitan funciones digitales
    GPIO_PORTA_AFSEL_R &= ~0x03; //Se utilizan como GPIO
	  //GPIO_PORTA_DR8R_R |= 0x10; /Se activa Driver en PA1

    //Configurar velocidad.
    UART1_IBRD_R = (UART1_IBRD_R & 0xFFFF0000) | 104; //BRD = 16,000,000 / (16 * 9600) = 104.1667
    UART1_FBRD_R = (UART1_FBRD_R & 0xFFFFFFC0) | 11; // DIVFRAC = 0.1667 * 64 + 0.5 = 11.3333

    //Configurar trama y buffers
    // 8, N, 1, FIFOs habilitados
    UART1_LCRH_R = (UART0_LCRH_R & 0xFFFFFF00) | 0x70;

    //Habilitar UART
    UART1_CTL_R &= ~UART_CTL_UARTEN;
}