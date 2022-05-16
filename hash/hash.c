#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct hash_tabla hash_tabla_t;
typedef enum estado {vacio, ocupado, borrado } estado_t;

struct hash_tabla {
    char* clave;
    void* dato;
	estado_t estado;
};

struct hash {
    size_t cantidad_elementos;
    size_t capacidad;
    hash_tabla_t* tabla;
};

/* http://www.cse.yorku.ca/~oz/hash.html */
static unsigned long hash_f(const char* clave) {

	unsigned long hash = 0;
	int c;

	while ((c = *clave++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}


hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));

	if (hash == NULL) {
		return NULL;
	}

	hash->capacidad = 10;
	hash->cantidad_elementos = 0;

	hash->tabla = malloc((hash->capacidad) * sizeof(hash_tabla_t));

	if ( hash->tabla == NULL) {
		free(hash);
		return NULL;
	}

	for(size_t i = 0; i < hash->capacidad; i++) {
		hash->tabla[i].clave = NULL;
		hash->tabla[i].dato = NULL;
		hash->tabla[i].estado = vacio;
	}

	return hash;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
	size_t posicion = hash_f(clave) % hash->capacidad;

	hash->tabla[posicion].clave = strdup(clave);
	hash->tabla[posicion].dato = dato;
	hash->tabla[posicion].estado = ocupado;
	
	hash->cantidad_elementos++;

	return true;
}


void *hash_obtener(const hash_t *hash, const char *clave) {
	size_t posicion = hash_f(clave) % hash->capacidad;
	printf("la posicion es %lu", posicion);

	return hash->tabla[posicion].dato;
}


bool hash_pertenece(const hash_t *hash, const char *clave) {
	size_t posicion = hash_f(clave) % hash->capacidad;
	if (!hash->tabla[posicion].clave) {
		return false;
	}
	return true;
}


size_t hash_cantidad(const hash_t *hash) {
	return hash->cantidad_elementos;
}


void *hash_borrar(hash_t *hash, const char *clave) {
	size_t posicion = hash_f(clave) % hash->capacidad;
	if (!hash_pertenece) {
		return NULL;
	}
	
	void* elemento_a_borrar = hash->tabla[posicion].dato;

	hash->tabla[posicion].estado = borrado;
	hash->cantidad_elementos--;
	free(hash->tabla[posicion].clave); 
		
	
	return elemento_a_borrar;
}

