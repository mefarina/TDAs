#include "pila.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool pila_redimensionar(pila_t* pila, size_t tam_nuevo) {
    void** datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(void*));

    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    pila->datos = datos_nuevo;
    pila->capacidad = tam_nuevo;
    return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void) {
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    pila->capacidad = 3;
    pila->cantidad = 0;
    pila->datos = malloc((pila->capacidad) * sizeof(void*));
    
    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
       
    return pila;
}


bool pila_apilar(pila_t *pila, void *valor) {
    //Tengo capacidad?
    if (pila->cantidad == pila->capacidad) {
        pila_redimensionar(pila, (pila->capacidad) * 2);
    }   
    pila->datos[pila->cantidad] = valor;
    (pila->cantidad)++;
    return true;
}


bool pila_esta_vacia(const pila_t *pila) {
    if (pila->cantidad == 0) {
        return true;
    } 
    return false;
}


void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila) == 1) {
        return NULL;
    }
    
    return pila->datos[(pila->cantidad) - 1];
}

void *pila_desapilar(pila_t *pila) {
    if(pila->cantidad == 0) {
        return NULL;
    }
    if ((pila->cantidad) * 4 <= pila->capacidad) {
        pila_redimensionar(pila, (pila->capacidad) / 2);
    } 
    pila->cantidad--;
    return pila->datos[pila->cantidad];
}


void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}
