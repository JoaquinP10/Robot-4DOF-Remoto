//------------Bluetooth_Recibe_Dato()------------
// Descripcion: Lee un caracter recibido por el modulo UART1 y lo devuelve como resultado.
// Entradas: Ninguno
// Salidas: Caracter recibido por el modulo UART1.

char Bluetooth_Recibe_Dato(void){
    while((UART1_FR_R & UART_FR_RXFE) != 0); //espera que el FIFO de recepcion no este vacio
    return(UART1_DR_R & 0xFF);
}

