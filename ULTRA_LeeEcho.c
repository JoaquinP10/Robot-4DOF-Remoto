/**************************************************************************
 Funcion ULTRA_MideDistancia
 Descripcion: Lee el pulso generado por 
 el sensor ultrasonico HC-SR04 y lo devuelve como resultado en metros, al analizar
 la duración del ancho de pulso del echo.
 Entradas: Ninguna
 Salidas: Distancia entre el sensor ultrasonido y el objeto medido
 Autor: Joaquin Pozo
 Ultima modificacion: 13 de junio de 2023
***************************************************************************/

//corregir caratula

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ULTRA.h"

uint32_t ULTRA_MideDistancia(void){

    uint32_t flancoSubida, flancoBajada;
    uint32_t i;
    uint32_t ciclos_reloj;
    double ancho_pulso;
    uint32_t distancia_cm;

    GPIO_PORTB_DATA_R |= TRIGGER; //Trigger en alta
    for (i=0; i<2000; i++); //delay de 10 microsegundos (falta calibrar)
    GPIO_PORTB_DATA_R &= ~TRIGGER; //Trigger en baja

    while(1){
        /*flanco de subida*/
        TIMER3_ICR_R = (1<<2); // borrar flag de captura

        while((TIMER3_RIS_R & (1<<2)) == 0); //Esperar hasta que se detecte una captura
        if (GPIO_PORTB_DATA_R & ECHO){  //verifica que haya un flanco de subida
            flancoSubida = TIMER3_TAR_R; //se guarda el tiempo de flanco de subida
            TIMER3_ICR_R = 0x04; // borrar flag de captura

            /*flanco de bajada*/

            while((TIMER3_RIS_R & (1<<2)) == 0); //Esperar hasta que se detecte una captura
            flancoBajada = TIMER3_TAR_R; //se guarda el tiempo de flanco de bajada

            ciclos_reloj = (flancoBajada - flancoSubida) & 0x000FFFFFF;
            ancho_pulso = ciclos_reloj * (1/(double)16000000);
            distancia_cm = (ancho_pulso*340/2) *100;
            return distancia_cm;
        }
    }
}
