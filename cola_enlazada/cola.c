#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo nodo_t; 

struct nodo {
    void* dato;
    nodo_t* prox;
};

struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};


cola_t *cola_crear(void) {
    cola_t* cola = malloc(sizeof(cola_t));

    if (cola == NULL) {
        return NULL;
    }

    cola->primero = NULL;
    cola->ultimo = NULL;

    return cola;
}


bool cola_esta_vacia(const cola_t *cola) {
	return (cola->primero == NULL);
}


bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t* nodo = malloc(sizeof(cola_t));

	if (nodo == NULL) {
		return false;
	}

	nodo->dato = valor;
	nodo->prox = NULL;

	if (cola_esta_vacia(cola) == true) {
		cola->primero = nodo;
    	cola->ultimo = nodo;
	}
	else {
		nodo_t* nodo_actual = cola->ultimo;
		nodo_actual->prox = nodo;
		cola->ultimo = nodo;
	}
	
    return true;
}


void *cola_ver_primero(const cola_t *cola) {
	if (cola_esta_vacia(cola) == true) {
		return NULL;
	} else {
		nodo_t* nodo = cola->primero;
		return nodo->dato;
	}
}


void *cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	
	nodo_t* nodo_actual = cola->primero; 
	void* dato_actual = cola->primero->dato;
	cola->primero = cola->primero->prox;
	free(nodo_actual);
	return dato_actual;
	}


void cola_destruir(cola_t* cola, void destruir_dato(void*)){
	while (cola_esta_vacia(cola) == false) {
		cola_desencolar(cola);
	}
	
	free(cola);
}
	
