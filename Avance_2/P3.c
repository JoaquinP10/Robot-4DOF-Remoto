/******************************************************************************************
* Nombre: Avance 2 - Ejercicio 3
* Módulo: Módulo Tiva Launchpad EK-TM4C123GH6PM
* Descripción: Programa que genera 4 señales PWM que controlan los servomotores de forma
autónoma. Cada señal empieza con un ciclo de trabajo de 7.5% el cual aumenta 0.1% cada vez
que se supere una cuenta SERVOXCUENTA. Al llegar a 10% automáticamente el ciclo de trabajo
empieza a disminuir en 0.1% hasta llegar a 5% para empezar a incrementar y repetir el lazo.
* Ciclo: Semestre 2023-1
* Alumno:
* Fecha: 31-05-23
******************************************************************************************/

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "TivaES.h"

#define LOAD 40000

#define SERVO1CUENTA 10000
#define SERVO2CUENTA 8000
#define SERVO3CUENTA 6000
#define SERVO4CUENTA 4000

//1 PB6
//2 PB7
//3 PB4
//4 PB5

void PWM_Configurar_Servomotor(void);

void main(void){

    int razon[4]= {1,1,1,1}; //razon de los 4 Servos. Se utilizará para aumentar o disminuir el ciclo de trabajo
    uint32_t cuenta =0; //cuenta
    double duty_cycle[4] = {7.5, 7.5, 7.5, 7.5}; //ciclos de trabajo de los 4 Servos

    PWM_Configurar_Servomotor(); //configura servos en los pines PB4, PB5, PB6, PB7


    while(1){ //bucle infinito
        /*Cuando la cuenta llega a SERVO1CUENTA, el ciclo de trabajo varía en 0.1%
        Se usa el operador % para simbolizar que la condicion se cumple cuando
        la cuenta sea un multiplo de SERVO1CUENTA (para que este evento ocurra mas de una vez*/
        if ((cuenta % SERVO1CUENTA) == 0) {
            duty_cycle[0]= duty_cycle[0] + (razon[0] * 0.1); //se aumenta el ciclo de trabajo en 0.1%
            PWM0_0_CMPA_R = (LOAD * duty_cycle[0])/100 - 1; //se genera la onda con el nuevo ciclo de trabajo
            if ((10 - duty_cycle[0]) < 0.1){ //cuando el ciclo de trabajo alcanza el limite superior de 10,
                razon[0] = -1; //se empieza a disminuir en 0.1 el ciclo de trabajo, por esto la razon es negativa
            }
            if ((duty_cycle[0]-5) < 0.1){ //cuando llega al limite inferior de 5
                razon[0] = 1; //la razon se vuelve positiva
            }
        }

        //Se hace exactamente lo mismo en los demás servos.
        //Se utilizan 4 if, y no if-else, ya que pueden cumplirse mas de una condicion a la vez
        if ((cuenta % SERVO2CUENTA) == 0){
            duty_cycle[1]= duty_cycle[1] + (razon[1] * 0.1);
            PWM0_0_CMPB_R = (LOAD * duty_cycle[1])/100 - 1;
            if ((10 - duty_cycle[1]) < 0.1){
                razon[1] = -1;
            }
            if ((duty_cycle[1]-5) < 0.1){
                razon[1] = 1;
            }
        }
        if ((cuenta % SERVO3CUENTA) == 0){
            duty_cycle[2]= duty_cycle[2] + (razon[2] * 0.1);
            PWM0_1_CMPA_R = (LOAD * duty_cycle[2])/100 - 1;
            if ((10 - duty_cycle[2]) < 0.1){
                razon[2] = -1;
            }
            if ((duty_cycle[2]-5) < 0.1){
                razon[2] = 1;
            }
        }

        if ((cuenta % SERVO4CUENTA) == 0){
            duty_cycle[3]= duty_cycle[3] + (razon[3] * 0.1);
            PWM0_1_CMPB_R = (LOAD * duty_cycle[3])/100 - 1;
            if ((10 - duty_cycle[3]) < 0.1){
                razon[3] = -1;
            }
            if ((duty_cycle[3]-5) < 0.1){
                razon[3] = 1;
            }
        }

        cuenta++; //se actualiza la cuenta

        if(cuenta == 120000) cuenta = 0; //cuando la cuenta llega a 120000 (minimo comun multiplo de todos los SERVOCUENTA) se reasgina a 0
    }
}

void PWM_Configurar_Servomotor(void){

    SYSCTL_RCGCGPIO_R = 0x02; //Habilita senhal de reloj en puerto B
    while((SYSCTL_PRGPIO_R & 0x02) == 0); //Espera hasta que este listo

    GPIO_PORTB_AMSEL_R &= ~0xF0; //Desactivar modo analogico
    GPIO_PORTB_DIR_R |= 0xF0; //PB4.7 como salidas
    GPIO_PORTB_DEN_R |= 0xF0; //habilitar como pin digital
    GPIO_PORTB_AFSEL_R |= 0xF0; //habilitar funcion alternativa
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0xFFFF0000) | (0x44440000); //configurar como PWM

    SYSCTL_RCGC0_R |= (1<<20); //Habilita senal de reloj de PWM

    // Configuramos divisor de frecuencia con 8,
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_8;

    // Generador 0 1: Modo cuenta descendente, inhabilitado
    PWM0_0_CTL_R &= (~0x03);
    PWM0_1_CTL_R &= (~0x03);

    // PWM bajo en load, alto en cmpA
    PWM0_0_GENA_R = 0xC8;
    PWM0_0_GENB_R = 0xC08;
    PWM0_1_GENA_R = 0xC8;
    PWM0_1_GENB_R = 0xC08;

    // Frecuencia = 50 Hz - LOAD = 39 999
    PWM0_0_LOAD_R = 40000 - 1;
    PWM0_1_LOAD_R = 40000 - 1;

    // Ciclo de trabajo = 7.5%
    PWM0_0_CMPA_R = (40000 * 10)/100 - 1;
    PWM0_0_CMPB_R = (40000 * 7.5)/100 - 1;
    PWM0_1_CMPA_R = (40000 * 7.5)/100 - 1;
    PWM0_1_CMPB_R = (40000 * 7.5)/100 - 1;

    // Inicializamos PWM0 PWM1
    PWM0_0_CTL_R |= 0x01;
    PWM0_1_CTL_R |= 0x01;

    // Habilitamos la senal PWM0 PWM1. Se habilita a la vez
    PWM0_ENABLE_R |= (0x03 | 0x0C);

}
