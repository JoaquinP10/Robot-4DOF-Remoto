void Bluetooth_Transmite_Cadena(unsigned char Arreglo[])
{
    unsigned char caracter;
    uint8_t i=0;
    caracter= Arreglo[i++];
    while (caracter != '\0'){ //Se envÃ­an todos los caracteres hasta el fin de cadena
    Bluetooth_Transmite_Car(caracter);
    caracter= Arreglo[i++];
    }

}