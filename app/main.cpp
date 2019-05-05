#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* cabecera de las llamadas a MPI */
#include <mpi.h> 

/**
 * Manda un mensaje desde todos los procesos con
 * rango distinto de 0 al proceso 0. El proceso 0
 * los saca por pantalla.
 * Entrada: ninguna
 * Salida: contenido de los mensajes recibidos por 
 * el proceso 0, que los imprime
 */
int main(int argc, char** argv) {
    int mi_rango; /* rango del proceso    */
    int p; /* numero de procesos   */
    int fuente; /* rango del que envia  */
    int dest; /* rango del que recibe */
    int tag = 0; /* etiqueta del mensaje */
    char mensaje[228]; /* mensaje  */
    char hostname[128]; /*Para guardar el nombre de la máquina*/
    MPI_Status estado; /* devuelve estado al recibir*/

    /* Comienza las llamadas a MPI */
    MPI_Init(&argc, &argv);

    /* Averiguamos el rango de nuestro proceso */
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

    /* Averiguamos el número de procesos que estan 
     * ejecutando nuestro porgrama 
     */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (mi_rango != 0) {
        /* Crea mensaje */
        gethostname(hostname, sizeof hostname); 
        /*Ahora estoy haciendo que cada proce que no sea el master imprima el nombre de la máquina*/
        sprintf(mensaje, " Hola! Mi nombre es %s!", hostname);
        dest = 0;
        /* Usa strlen+1 para que la marca /0 se transmita */
        MPI_Send(mensaje, strlen(mensaje) + 1, MPI_CHAR,
                dest, tag, MPI_COMM_WORLD);
    } else { /* mi_rango == 0 */
        for (fuente = 1; fuente < p; fuente++) {
            MPI_Recv(mensaje, 228, MPI_CHAR, fuente,
                    tag, MPI_COMM_WORLD, &estado);
            printf("%s\n", mensaje);
        }
    }

    /* Termina con MPI. Recordemos que después de 
     * esta llamada no podemos llamar a funciones 
     * MPI, ni siquiera de nuevo a MPI_Init 
     */
    MPI_Finalize();
    return EXIT_SUCCESS;
}

    /* Termina con MPI. Recordemos que después de 
     * esta llamada no podemos llamar a funciones 
     * MPI, ni siquiera de nuevo a MPI_Init 
     */
    MPI_Finalize();
    return EXIT_SUCCESS;
}
