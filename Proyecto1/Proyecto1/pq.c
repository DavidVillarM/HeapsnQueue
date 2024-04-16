#include "pq.h"
#include <stdlib.h>

/* Función auxiliar para intercambiar dos elementos en el montículo */
void swap(PrioValue* a, PrioValue* b) {
    PrioValue temp = *a;
    *a = *b;
    *b = temp;
}

/* Función auxiliar para realizar el up-heap (flotar hacia arriba) en el montículo */
void up_heap(PQ* pq, int index) {
    while (index > 0 && pq->arr[index]->prio < pq->arr[(index - 1) / 2]->prio) {
        swap(&pq->arr[index], &pq->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

/* Función auxiliar para realizar el down-heap (hundir hacia abajo) en el montículo */
void down_heap(PQ* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->arr[left]->prio < pq->arr[smallest]->prio)
        smallest = left;

    if (right < pq->size && pq->arr[right]->prio < pq->arr[smallest]->prio)
        smallest = right;

    if (smallest != index) {
        swap(&pq->arr[index], &pq->arr[smallest]);
        down_heap(pq, smallest);
    }
}

/* Crea la cola de prioridad PQ e inicializa sus atributos
retorna un puntero a la cola de prioridad 
retorna NULL si hubo error*/
PQ* pq_create() {
   
	
	/* PQ pq = (PQ) malloc(sizeof(struct Heap)); */
	/* AGREGUE SU CODIGO AQUI */
    PQ* pq = (PQ*)malloc(sizeof(PQ));
    if (pq != NULL) {
        pq->cap = 10;  // initial capacity
        pq->size = 0;
        pq->arr = (PrioValue*)malloc(pq->cap * sizeof(PrioValue));
        if (pq->arr == NULL) {
            free(pq);
            return NULL;
        }
    }
    return pq;
}

/*
Agrega un valor a la cola con la prioridad dada

retorna TRUE si tuvo exito, FALSE si no
*/
BOOLEAN pq_add(PQ* pq, void* valor, int prioridad) {
   
	/* AGREGUE SU CODIGO AQUI */
    if (pq == NULL)
        return FALSE;

    if (pq->size >= pq->cap) {
        // Realizar un redimensionamiento del arreglo si es necesario
        pq->cap *= 2;
        pq->arr = (PrioValue*)realloc(pq->arr, pq->cap * sizeof(PrioValue));
        if (pq->arr == NULL)
            return FALSE;
    }

    PrioValue newItem = (PrioValue)malloc(sizeof(struct _PrioValue));
    if (newItem == NULL)
        return FALSE;

    newItem->prio = prioridad;
    newItem->value = valor;

    pq->arr[pq->size] = newItem;
    up_heap(pq, pq->size);
    pq->size++;

    return TRUE;
}

/* Saca el valor de menor prioridad (cima del monticulo) y lo guarda en la posicion retVal (paso por referencia) 
   retorna FALSE si tiene un error
   retorna TRUE si tuvo EXITO
*/
BOOLEAN pq_remove(PQ* pq, void** retVal) {

   /* AGREGUE SU CODIGO AQUI */
    if (pq == NULL || pq->size == 0)
        return FALSE;

    *retVal = pq->arr[0]->value;
    free(pq->arr[0]);
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;
    down_heap(pq, 0);

    return TRUE;
}

/* retorna el tamaño de la cola de prioridad, 
   retorna 0 si hubo error 
 */
int pq_size(PQ* pq) {

   	/* AGREGUE SU CODIGO AQUI */
    if (pq == NULL)
        return 0;
    return pq->size;
}

/* Destruye la cola de prioridad, 
retorna TRUE si tuvo exito
retorna FALSE si tuvo error*/
BOOLEAN pq_destroy(PQ* pq) {
   
   /* AGREGUE SU CODIGO AQUI */
    if (pq == NULL)
        return FALSE;

    for (int i = 0; i < pq->size; i++)
        free(pq->arr[i]);

    free(pq->arr);
    free(pq);
    return TRUE;
}
