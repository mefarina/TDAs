#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct nodo nodo_t; 

struct nodo {
    void* dato;
    nodo_t* prox;
};

struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

lista_t *lista_crear(void) {
    lista_t* lista = malloc(sizeof(lista_t));

    if (lista == NULL) {
        return NULL;
    }

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;

    return lista;
}


bool lista_esta_vacia(const lista_t *lista) {
    return lista->largo == 0;
}


bool lista_insertar_primero(lista_t *lista, void *valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return false;
    }

	nodo->dato = valor;
	nodo->prox = lista->primero;

	if (lista_esta_vacia(lista) == true) {
		lista->ultimo = nodo;
	}
	lista->primero = nodo;
	lista->largo++;

    return true;
}


void *lista_ver_primero(const lista_t *lista){
	return lista->primero->dato;
}


void *lista_borrar_primero(lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}

	nodo_t* nodo_actual = lista->primero;
	void* dato_actual = lista->primero->dato;
	lista->primero = lista->primero->prox;
	lista->largo--;

	free(nodo_actual);
	return dato_actual;
}


bool lista_insertar_ultimo(lista_t *lista, void *valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	
	if (nodo == NULL || lista_esta_vacia(lista)) {
		return false;
	}
	
	nodo->dato = valor;
	lista->ultimo->prox = nodo;
	lista->ultimo = nodo;

	lista->largo++;
	return true;
}


void *lista_ver_ultimo(const lista_t *lista) {
	return lista->ultimo->dato;
}


size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}


void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
	while (lista_esta_vacia(lista) == false) {
		lista_borrar_primero(lista);
		}
	
	free(lista);
}


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	nodo_t* nodo = lista ->primero;
	while(nodo != NULL) {
		if (lista_esta_vacia(lista) == false) {
			void* dato = nodo->dato;
			visitar(dato, extra);
			nodo = nodo->prox;		
		}
	}
}