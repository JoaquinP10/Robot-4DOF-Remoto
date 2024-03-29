/***************************************************************************************
 Funcion Configurar_Bluetooth
 Descripcion: Configura el modulo UART1 para la comunicacion mediante Bluetooth. Se
 establece una velocidad de transmision de 9600 baudios y se habilita la interrupcion de
 recepcion. Se configuran los pines PB0 y PB1 como entrada/salida UART1
 respectivamente. Asimismo, se configuran los pines PA0 y PA1 como entrada/salida
 respectivamente para determinar si es que el modulo es esclavo o maestro y su estado de
 coneccion.
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: Joaquin Pozo
 Ultima modificacion: 14 de junio de 2023
****************************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>
#include "Bluetooth.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

void main(void){
    //activar senal de reloj GPIO en A
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R0;
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);
    //activar senal de reloj GPIO en B
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1;
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0);
    //activar senal de reloj UART en B
    SYSCTL_RCGC_UART_R = SYSCTL_RCGC1_UART1;
    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R1) == 0);
    
    //Desactivar el modulo UART
    UART1_CTL_R &= ~UART_CTL_UARTEN;

    //Configurar PB0 PB1
    GPIO_PORTA_DIR_R &= ~BIT0; //PB0 entrada
    GPIO_PORTA_DIR_R |= BIT1; //PB1 salida
    GPIO_PORTB_AMSEL_R &= ~(BIT0 | BIT1); //Funciones analogicas desactivadas en PB0 PB1
    GPIO_PORTB_PDR_R &= ~(BIT0 | BIT1); //Sin resistencia de pull down
    GPIO_PORTB_PUR_R &= ~(BIT0 | BIT1); //Sin resistencia de pull up
    GPIO_PORTB_DEN_R |= (BIT0 | BIT1) ; //Se habilitan funciones digitales
    GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1); //Se habilita funcion alternativa

    //Se escogen los nibbles con el valor que corresponde a U1Tx y U1Rx 
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00)|0x00000011; 

    //Configurar PA0 (enable/key) PA1(state)
    GPIO_PORTA_DIR_R = (GPIO_PORTA_DIR_R & (~0x01)) | (0x02); //Coloca a PA0 como entrada y PA1 como salida
    GPIO_PORTA_AMSEL_R &= ~(BIT0 | BIT1); //Funciones analogicas desactivadas en PA0 PA1
    GPIO_PORTA_DEN_R |= (BIT0 | BIT1); //Se habilitan funciones digitales
    GPIO_PORTA_AFSEL_R &= ~(BIT0 | BIT1); //Se utilizan como GPIO
	//GPIO_PORTA_DR8R_R |= 0x10; /Se activa Driver en PA1

    //Configurar velocidad.
    UART1_IBRD_R = (UART1_IBRD_R & 0xFFFF0000) + 104; //BRD = 16,000,000 / (16 * 9600) = 104.1667
    UART1_FBRD_R = (UART1_FBRD_R & 0xFFFFFFC0) + 11; // DIVFRAC = 0.1667 * 64 + 0.5 = 11.3333

    //Configurar trama y buffers
    // 8, N, 1, FIFOs habilitados
    UART1_LCRH_R = (UART0_LCRH_R & 0xFFFFFF00) | 0x70;

    //Habilitar UART
    UART1_CTL_R &= ~0x20; //HSE=0 (/16)
    UART1_CTL_R |= 0x301; //UARTEN = 1, RXE = 1, TXE = 1
}

//How to change master/slave
//AT+ROLE=0
//Other useful commands:
//AT+PSWD? //password
//AT //are you in config mode? //change modes with button, or with key/state pin
//
