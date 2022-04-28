#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct hash_campo hash_campo_t;
typedef enum estado {vacio, ocupado, borrado } estado_t;

struct hash_campo {
    char* clave;
    void* dato;
	estado_t estado;
};

struct hash {
    size_t cantidad_elementos;
    size_t capacidad;
    hash_campo_t* campo;
};

/* http://www.cse.yorku.ca/~oz/hash.html */
unsigned long hash(unsigned char *str) {
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

	hash->campo = malloc(sizeof(hash_campo_t*) * hash->capacidad);

	if ( hash->campo == NULL) {
		free(hash);
		return NULL;
	}

	for(size_t i = 0; i < hash->capacidad; i++) {
		hash->campo[i].clave = NULL;
		hash->campo[i].dato = NULL;
		hash->campo[i].estado = vacio;
	}

	return hash;
}

int main() {
	hash_t* hash = hash_crear(NULL);
}