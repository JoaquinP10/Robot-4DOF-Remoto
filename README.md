# Robot-4DOF-Remoto
Proyecto propuesto en el curso de Sistemas Digitales que consiste en un robot bípedo que puede ser controlado a través de un dispositivo móvil a través de Bluetooth, donde este puede desplazarse y girar libremente. Además, posee una funcionalidad que determina la distancia entre él y un objeto y se la muestra al usuario.

El móvil presenta una interfaz con botones para el movimiento en las cuatro direcciones, para el giro horario y
antihorario; un botón adicional para determinar la distancia respecto a un objeto y dos pantallas: una donde se
muestra si el robot está vinculado al móvil y otra donde se muestra el resultado de la distancia al usuario.

## Requerimientos

El sistema consta de un ultrasonido que determinará la distancia entre el robot y un objeto cercano,
además de un módulo Bluetooth que permite la comunicación entre el dispositivo móvil y el robot.
Además, posee cuatro servomotores que dictarán el movimiento del robot.
1. El dispositivo móvil debe estar emparejado con el robot a través de Bluetooth
2. Se permiten las opciones de movimiento, rotación y distancia a un objeto
3. Cuando se presione alguno de los botones, se bloquearán los demás.
4. Con los botones de desplazamiento, el robot se podrá mover hacia delante, atrás, izquierda o
derecha.
5. Con los botones de giro, el robot podrá girar hacia el sentido horario y antihorario
6. Si estos se dejan presionados, el robot seguirá ejecutando la acción
7. Al presionar el botón de distancia, el ultrasonido se activará y determinará el valor en cm. Este se
mostrará en una sección del móvil
8. Si la distancia es mayor a 4 m, se mostrará un mensaje en el móvil “Fuera de rango”
9. Se repite el proceso
