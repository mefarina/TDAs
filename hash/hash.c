#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct hash_tabla hash_tabla_t;
typedef enum estado {vacio, ocupado, borrado } estado_t;

struct hash_tabla {
    const char* clave;
    void* dato;
	estado_t estado;
};

struct hash {
    size_t cantidad_elementos;
    size_t capacidad;
    hash_tabla_t* tabla;
};

/* http://www.cse.yorku.ca/~oz/hash.html */
unsigned long hash_f(const char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}


hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));

	if (hash == NULL) {
		return NULL;
	}

	hash->capacidad = 10;
	hash->cantidad_elementos = 0;

	hash->tabla = malloc(sizeof(hash_tabla_t*) * hash->capacidad);

	if ( hash->tabla == NULL) {
		free(hash);
		return NULL;
	}

	for(size_t i = 0; i < hash->capacidad; i++) {
		hash->tabla[i].dato = NULL;
		hash->tabla[i].estado = vacio;
	}

	return hash;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
	int posicion = hash_f(clave) %  hash->capacidad;

	hash->tabla[posicion].clave = clave;
	hash->tabla[posicion].dato = dato;
	hash->tabla[posicion].estado = ocupado;
	
	hash->cantidad_elementos++;

	return true;
}

