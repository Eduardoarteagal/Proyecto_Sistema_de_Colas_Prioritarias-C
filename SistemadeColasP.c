#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para una tarea
typedef struct Tarea {
    int id;
    int prioridad;
    char descripcion[100];
} Tarea;

// Estructura para la cola prioritaria (max-heap)
typedef struct ColaPrioritaria {
    int tamano;
    int capacidad;
    Tarea *array;
} ColaPrioritaria;

// Crea una cola prioritaria de capacidad `capacidad`
ColaPrioritaria* crearColaPrioritaria(int capacidad) {
    ColaPrioritaria *cola = (ColaPrioritaria*)malloc(sizeof(ColaPrioritaria));
    cola->tamano = 0;
    cola->capacidad = capacidad;
    cola->array = (Tarea*)malloc(capacidad * sizeof(Tarea));
    return cola;
}

// Intercambia dos elementos en la cola prioritaria
void intercambiar(Tarea *a, Tarea *b) {
    Tarea temp = *a;
    *a = *b;
    *b = temp;
}

// Ajusta la cola prioritaria para mantener el orden del max-heap
void heapify(ColaPrioritaria *cola, int indice) {
    int mayor = indice;
    int izquierda = 2 * indice + 1;
    int derecha = 2 * indice + 2;

    if (izquierda < cola->tamano && cola->array[izquierda].prioridad > cola->array[mayor].prioridad) {
        mayor = izquierda;
    }
    if (derecha < cola->tamano && cola->array[derecha].prioridad > cola->array[mayor].prioridad) {
        mayor = derecha;
    }

    if (mayor != indice) {
        intercambiar(&cola->array[indice], &cola->array[mayor]);
        heapify(cola, mayor);
    }
}

// Inserta una tarea en la cola prioritaria
void insertarTarea(ColaPrioritaria *cola, int id, int prioridad, char *descripcion) {
    if (cola->tamano == cola->capacidad) {
        printf("Cola prioritaria llena\n");
        return;
    }

    int i = cola->tamano++;
    cola->array[i].id = id;
    cola->array[i].prioridad = prioridad;
    strncpy(cola->array[i].descripcion, descripcion, sizeof(cola->array[i].descripcion));

    while (i != 0 && cola->array[i].prioridad > cola->array[(i - 1) / 2].prioridad) {
        intercambiar(&cola->array[i], &cola->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Extrae la tarea con la mayor prioridad de la cola prioritaria
Tarea extraerTarea(ColaPrioritaria *cola) {
    if (cola->tamano <= 0) {
        printf("Cola prioritaria vacia\n");
        Tarea vacia = {0, 0, ""};
        return vacia;
    }
    if (cola->tamano == 1) {
        return cola->array[--cola->tamano];
    }

    Tarea raiz = cola->array[0];
    cola->array[0] = cola->array[--cola->tamano];
    heapify(cola, 0);

    return raiz;
}

// Muestra todas las tareas en la cola prioritaria
void mostrarTareas(ColaPrioritaria *cola) {
    for (int i = 0; i < cola->tamano; i++) {
        printf("ID: %d, Prioridad: %d, Descripción: %s\n",
               cola->array[i].id, cola->array[i].prioridad, cola->array[i].descripcion);
    }
}

// Función principal
int main() {
    ColaPrioritaria *cola = crearColaPrioritaria(10);
    
    insertarTarea(cola, 1, 5, "Tarea 1");
    insertarTarea(cola, 2, 2, "Tarea 2");
    insertarTarea(cola, 3, 8, "Tarea 3");
    insertarTarea(cola, 4, 1, "Tarea 4");
    
    printf("Tareas en la cola prioritaria:\n");
    mostrarTareas(cola);

    printf("\nExtrayendo tarea con mayor prioridad:\n");
    Tarea tarea = extraerTarea(cola);
    printf("ID: %d, Prioridad: %d, Descripción: %s\n",
           tarea.id, tarea.prioridad, tarea.descripcion);

    printf("\nTareas restantes en la cola prioritaria:\n");
    mostrarTareas(cola);

    free(cola->array);
    free(cola);
    
    return 0;
}
