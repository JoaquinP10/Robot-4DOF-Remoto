//------------Bluetooth_Envia_Dato()------------
// Descripcion: Envia un caracter por el modulo UART1.
// Entradas: Caracter a enviar por el modulo UART1.
// Salidas: Ninguna
// Autor: 
// Ultima modificacion: 
void Bluetooth_Envia_Dato(char data){
    while((UART1_FR_R & UART_FR_TXFF) != 0); //Espera que el FIFO de transmision no este lleno
    UART1_DR_R = data; //envia el dato
}
