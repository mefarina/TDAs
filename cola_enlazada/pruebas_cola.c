#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_cola_vacia(void) {
    printf("-----PRUEBAS COLA VACIA-----\n\n");
    cola_t* cola = cola_crear();
    // La cola se crea correctamente y empieza estando vacia
    print_test("Cola está vacía:", cola_esta_vacia(cola) == true);
    print_test("Ver primero es NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolar devuelve NULL", cola_desencolar(cola) == NULL);
    printf("\n");

    cola_destruir(cola, NULL);
}

static void prueba_encolar(void) {
    printf("-----PRUEBAS ENCOLAR-----\n\n");
    //Probar invariante FIFO
    cola_t* cola = cola_crear();
    int a = 2;
    int b = 4;
    print_test("Encolar 2 == true:", cola_encolar(cola, &a) == true);
    print_test("Encolar 4 == true:", cola_encolar(cola, &b) == true);
    //El primer elemento que sale es el primero que entra
    print_test("First out es 2:", *((int*)cola_desencolar(cola)) == 2);
    print_test("Ver primero es 4", *((int*)cola_ver_primero(cola)) == 4);
    print_test("Cola no está vacía:", cola_esta_vacia(cola) == false);
    printf("\n");

    cola_destruir(cola, NULL);
}

static void prueba_encolar_NULL(void) {
    printf("-----PRUEBAS ENCOLAR NULL----\n\n");
    cola_t* cola = cola_crear();
    //Encolar NULL es válido
    print_test("Encolar NULL == true:", cola_encolar(cola, NULL) == true);
    print_test("Cola no está vacía:", cola_esta_vacia(cola) == false);
    print_test("Desencolar NULL:", cola_desencolar(cola) == NULL);
    printf("\n");

    cola_destruir(cola, NULL);
}


static void prueba_volumen(void) {
    printf("-----PRUEBAS DE VOLUMEN----\n\n");
    cola_t* cola = cola_crear();

    //Encolar muchos elementos
    int i = 0;
    bool ok = true;
    int elementos = 10000;
    
    while (i < elementos) {
        int num = 0;
        ok &= cola_encolar(cola, &num);
        num++;
        i++;
	}

    print_test("se pudieron encolar todos los elementos", ok == true);

    ok = true;
    while (i < elementos) {
        cola_desencolar(cola);
        i++;
	}

    print_test("se pudieron desencolar todos los elementos", cola_esta_vacia(cola) == true);
    printf("\n");
    
    cola_destruir(cola, free);
}


void pruebas_pila_estudiante() {
    prueba_cola_vacia();
    prueba_encolar();
    prueba_encolar_NULL();
    prueba_volumen();

}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
