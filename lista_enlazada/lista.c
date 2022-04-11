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

struct lista_iter {
	nodo_t* actual;
	nodo_t* anterior;
	lista_t* lista;
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


/* ---------------Iterador externo-------------- */ 


lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));

    if (iter == NULL) {
        return NULL;
    }

	iter->actual = lista->primero;
	if (iter->actual == NULL) printf("iter->actual ta nulo\n");
	if (lista->primero == NULL) printf("lista->primero ta nulo\n");
	iter->anterior = NULL;
	iter->lista = lista;

	return iter;
}


void *lista_iter_ver_actual(const lista_iter_t *iter) {
	if (iter->actual == NULL) {
		return NULL;
	}	
	return iter->actual->dato;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	if (iter->actual == NULL) {
		return false;
	}	
	
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;

	return true;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	if (iter->actual == NULL) {
		return true;
	}

	return false;
}

bool lista_iter_insertar(lista_iter_t *iter, void *valor) {
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));

    if (nodo_nuevo == NULL || lista_esta_vacia(iter->lista) == true) {
        return false;
    }

	if (iter->lista->primero) {
		iter->anterior = nodo_nuevo;
	} 

	if (lista_iter_al_final(iter)) {
		iter->lista->ultimo = nodo_nuevo;
	}
	
	nodo_nuevo->dato = valor;	
	iter->anterior->prox = nodo_nuevo;
	nodo_nuevo->prox = iter->actual;
	iter->actual = nodo_nuevo;
	
	iter->lista->largo++;	

	return true;
}


void *lista_iter_borrar(lista_iter_t *iter) {
	if (lista_esta_vacia(iter->lista)) {
		return NULL;
	}

	nodo_t* nodo_a_eliminar = iter->actual;
	void* dato_a_eliminar = nodo_a_eliminar->dato;
	iter->actual = nodo_a_eliminar->prox;
	iter->lista->primero = iter->actual;

	free(nodo_a_eliminar);
	return dato_a_eliminar;
}



