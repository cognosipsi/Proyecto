#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "treemap.h"

//gcc -g main.c hashmap-answer.c list.c opcion.c treemap.c -o proyecto

int main (void) {
    int op;
    printf("¿Desea ver un tutorial?\n");
    printf("1. Si\n");
    printf("2. No\n");
    scanf("%d", &op);
    if(op == 1) {
        tutorial();
    }
    while(op != 10) {
        printf("Seleccione una opción:\n\n");
        printf("1. Buscar\n");
        printf("2. Cambiar orden\n");
        printf("3. Agregar al carro\n");
        printf("4. Quitar del carro\n");
        printf("5. Mostrar carro\n");
        printf("6. Productos recomendados\n");
        printf("7. Finalizar compra\n");
        printf("8. Mostrar puntos acumulados\n");
        printf("9. Soporte de ayuda\n");
        printf("10. Cerrar aplicacion");
        scanf("%d", &op);
        if (op == 1) {
            printf("Seleccione una opción:\n\n");
            printf("1. Buscar por producto\n");
            printf("2. Buscar por tipo de producto\n");
            printf("3. Buscar por marca\n");
            scanf("%d", &op);

            if (op == 1) {
                search_product();
            }
            if (op == 2) {
                search_type();
            }
            if (op == 3) {
                search_brand();
            }
        }
        if (op == 2) {
            printf("Seleccione una opción:\n\n");
            printf("1. Ordenar por precio");
            printf("2. Ordenar por marca");
            printf("3. Ordenar por tipo");
            printf("4. Orden alfabético");
            scanf("%d", &op);

            if (op == 1) {
                price_sort();
            }
            if (op == 2) {
                brand_sort();
            }
            if (op == 3) {
                type_sort();
            }
            if (op == 4) {
                az_sort();
            }
        }
        if (op == 3) {
            push_cart();
        }

        if (op == 4) {
            pop_cart();
        }
        
        if (op == 5) {
            show_cart();
        }
        
        if (op == 6) {
            show_recom();
        }
        
        if (op == 7) {
            complete_purchase();
        }
        
        if (op == 8) {
            show_points();
        }
        
        if (op == 9) {
            printf("Seleccione una opción:\n\n");
            printf("1. Tutorial\n");
            printf("2. Preguntas frecuentes\n");
            scanf("%d", &op);

            if (op == 1) {
                tutorial();
            }

            if (op == 2) {
                faq();
            }
        }
    }
    return 0;
}