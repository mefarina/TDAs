#include "pila.h"
#include "testing.h"
#include <stdio.h>


static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();
    // print_test( ... pila_esta_vacia(pila) ... );
    print_test("Pila está vacía:", pila_esta_vacia(pila) == 1);
    print_test("Tope de pila es NULL", pila_ver_tope(pila) == NULL);
    print_test("Desapilar devuelve NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}


static void prueba_pila_apilar(void) {
    pila_t *pila = pila_crear();
    int arreglo[] = {50, 30, 5};
    print_test("Apilar elemento 50:", pila_apilar(pila, &arreglo[0]));
    print_test("Tope == 50:", *((int*)pila_ver_tope(pila)) == 50);
    print_test("Apilar elemento 30:", pila_apilar(pila, &arreglo[1]));
    print_test("Tope == 30:", *((int*)pila_ver_tope(pila)) == 30);

    print_test("Desapilar 30", pila_desapilar(pila) == &arreglo[1]);
    print_test("Tope == 50:", *((int*)pila_ver_tope(pila)) == 50);

    print_test("Apilar elemento 5:", pila_apilar(pila, &arreglo[2]));
    print_test("Tope == 5:", *((int*)pila_ver_tope(pila)) == 5);

    pila_destruir(pila);
}


static void prueba_pila_redimensionar(void) {
    pila_t *pila = pila_crear();
    //capacidad inicial = 5
    int arreglo[] = {50, 30, 5, 10, 20, 1, 9, 3, 25, 5};
    printf("Agrego el doble de la capacidad de la pila\n");
    for(int i = 0; i < 10; i++) {
        print_test("Apilando elemento", pila_apilar(pila, &arreglo[i]));
    }
    print_test("Tope == 5:", *((int*)pila_ver_tope(pila)) == 5);

    printf("Desapilo varios elementos\n");
    for(int i = 0; i <= 8; i++) {
        print_test("Depilando elemento", pila_desapilar(pila));
    } 
    //Cómo pruebo la redimension al desapilar?
    print_test("Verificando tope", pila_ver_tope(pila));
    print_test("Tope == 50:", *((int*)pila_ver_tope(pila)) == 50);

    pila_destruir(pila);

}



void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_apilar();
    prueba_pila_redimensionar();
    // ...
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
