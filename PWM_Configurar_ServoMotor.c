/**************************************************************************
 Funcion PWM_Configurar_ServoMotor
 Descripción: Configura el módulo M0 PWM1 para el control del servomotor. 
 Se establece una frecuencia de 50Hz y un ciclo de trabajo de 5% para la 
 posición mínima del servomotor y 10% para la posición máxima.
 Entradas: Ninguna
 Salidas: Ninguna
 Autor:
 Ultima modificacion: 20 de mayo de 2023
***************************************************************************/

#include "tm4c123gh6pm.h"
#include <stdint.h>