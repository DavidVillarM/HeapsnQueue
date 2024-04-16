#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "pq.h"

#define MAX_CHARS 256 

int main(int argc, char* argv[]) {

    /* revisar que se pasó el nombre del archivo via parametros */
    if (argc != 2) {
        printf("Forma de uso:\n");
        printf("\tProyecto1.exe nombre_de_archivo.txt\n");
        return 1;
    }

    printf("Intentando abrir el archivo: %s\n", argv[1]);
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    int freq[MAX_CHARS] = { 0 };
    char c;
    while ((c = fgetc(f)) != EOF) {
        freq[(unsigned char)c]++;
    }
    fclose(f);

    PQ* pq = pq_create();
    if (pq == NULL) {
        printf("Error al crear la cola de prioridad.\n");
        return 1;
    }

    for (int i = 0; i < MAX_CHARS; i++) {
        if (freq[i] > 0) {
            char character = (char)i;
            pq_add(pq, (void*)character, freq[i]);
        }
    }

    /* Sacar y mostrar los elementos de la cola de prioridad */
    printf("Frecuencias de menor a mayor:\n");
    printf("Caracter | frecuencia\n");
    void* retVal;
    while (pq_remove(pq, &retVal)) {
        char character = (char)retVal;
        printf("%c = %d\n", character, freq[(unsigned char)character]);
    }

    /* Liberar la memoria de la cola de prioridad */
    pq_destroy(pq);

    return 0;
}