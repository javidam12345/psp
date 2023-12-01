/*
a) Jerarquía de procesos:

Al ejecutar el programa, el proceso padre imprimirá "CCC", luego se bifurca y crea un proceso hijo. La jerarquía de procesos después de fork() será:

[Proceso Padre (PID 1000)]
|
+----> [Proceso Hijo (PID 1001)]

b) Salida del código:

Con un fork() exitoso, el proceso padre y el proceso hijo continúan su ejecución justo después de la llamada a fork().
 El padre ejecutará la rama del if donde la condición es verdadera (porque fork() devuelve el PID del hijo que es un valor no cero),
 y el hijo ejecutará la rama del else (porque fork() devuelve 0 en el proceso hijo).

Por lo tanto, la salida será "CCC" seguido de "AAA" o "BBB" en cualquier orden. Estas son las dos posibles salidas:


CCC
AAA
BBB

 o

CCC
BBB
AAA

Si el fork() falla, lo que es poco común, el proceso padre entra en la rama del else y la salida sería:


CCC
BBB

c) Modificación del código para salida especificada:

Para obtener la salida:

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    printf("CCC \n");
    pid_t pid = fork();
    if (pid != 0) {
        // Proceso padre
        wait(NULL); // Espera a que el hijo termine
        printf("AAA \n");
    } else {
        // Proceso hijo
        printf("BBB \n");
        exit(0); // Termina el proceso hijo
    }
    exit(0);
}
/*
En este código, el proceso padre imprime "CCC", luego se bifurca y espera a que el proceso hijo termine de imprimir
 "BBB" antes de imprimir "AAA". Esto garantiza que "BBB" se imprima antes de "AAA" sin importar la planificación del sistema operativo.

*/



