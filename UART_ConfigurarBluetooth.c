/***************************************************************************************
 Funcion UART_ConfigurarBluetooth
 Descripción: Configura el módulo UART1 para la comunicacion mediante Bluetooth. Se
 establece una velocidad de transmisión de 9600 baudios y se habilita la interrupción de
 recepción. Se configuran los pines PB0 y PB1 como entrada/salida UART1
 respectivamente. Asimismo, se configuran los pines PA0 y PA1 como entrada/salida
 respectivamente para determinar si es que el módulo es esclavo o maestro y su estado de
 coneccion.
 Entradas: Ninguna
 Salidas: Ninguna
 Autor: Joaquín Pozo
 Ultima modificacion: 20 de mayo de 2023
****************************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "UART.h"

void UART_ConfigurarBluetooth(void){
    //activar señal de reloj GPIO en A
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R0;
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);
    //activar señal de reloj GPIO en B
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1;
    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0);
    //activar señal de reloj UART en B
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R1) == 0);

    //Desactivar el modulo UART
    UART1_CTL_R &= ~UART_CTL_UARTEN;

    //Configurar Pines 
    GPIO_PORTB_AMSEL_R &= ~(0x03); //Funciones analógicas desactivadas en PB0 PB1
    GPIO_PORTB_DEN_R |= 0x03; //Se habilitan funciones digitales
    GPIO_PORTB_AFSEL_R |= 0x03; //Se habilita funcion alternativa
    //Se escoge el los nibbles con el valor que corresponde a U1Tx y U1Rx 
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00)|0x00000011; 

    GPIO_PORTA_DIR_R = (GPIO_PORTA_DIR_R & (~0x01)) | (0x20); //Coloca a PA0 como entrada y PA1 como salida
    GPIO_PORTA_AMSEL_R &= ~(0x03); //Funciones analógicas desactivadas en PB0 PB1
    GPIO_PORTA_DEN_R |= 0x03; //Se habilitan funciones digitales
    GPIO_PORTA_AFSEL_R &= ~0x03; //Se utilizan como GPIO

    //Configurar velocidad

    //Configurar trama y buffers

    //Habilitar UART
}