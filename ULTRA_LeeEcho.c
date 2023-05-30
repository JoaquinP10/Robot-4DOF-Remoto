//header

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ULTRA.h"

void ULTRA_LeeEcho(void){

    uint32_t flancoSubida, flancoBajada;
    uint32_t i;

    GPIO_PORTB_DATA_R |= 0x02; //Trigger en alta
    for (i=0; i<10000; i++); //delay de 10 microsegundos
    GPIO_PORTB_DATA_R &= ~0x02; //Trigger en baja

    while(1){
        /*flanco de subida*/
        TIMER3_ICR_R = 0x04; // borrar flag de captura
        while((TIMER3_RIS_R & 0x02) == 0); //Esperar hasta que se detecte una captura
        if (GPIO_PORTB_DATA_R & 0x08)  //verifica que haya un flanco de subida
            {flancoSubida = TIMER3_TAR_R;} //se guarda el tiempo de flanco de subida
        else
            {return;}
        /*flanco de bajada*/
        TIMER3_ICR_R = 0x04; // borrar flag de captura
        while((TIMER3_RIS_R & 0x02) == 0); //Esperar hasta que se detecte una captura
        flancoBajada = TIMER3_TAR_R; //se guarda el tiempo de flanco de bajada
        break;
    }
    return (flancoBajada - flancoSubida) & 0x000FFFFFF; //por que 24 bits? (incluye preescalador, data solo hasta 18)
}