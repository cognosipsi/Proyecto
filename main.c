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
    int op2;
    HashMap *ProductMap = createMap(100);
    printf("¿Desea ver un tutorial?\n");
    printf("1. Si\n");
    printf("2. No\n");
    scanf("%d", &op);
    if(op == 1) {
        tutorial();
    }
    
    while(op != 7) {
        printf("Seleccione una opción:\n\n");
        printf("1. Buscar\n");
        printf("2. Mostrar carro\n");
        printf("3. Productos recomendados\n");
        printf("4. Finalizar compra\n");
        printf("5. Mostrar puntos acumulados\n");
        printf("6. Soporte de ayuda\n");
        printf("7. Cerrar aplicacion");
        scanf("%d", &op);
        if (op == 1) {
          while (op2 != 2) {
              printf("Seleccione una opción:\n\n");
              printf("1. Buscar por producto\n");
              printf("2. Buscar por tipo de producto\n");
              printf("3. Buscar por marca\n");
              scanf("%d", &op);

              if (op == 1) {
                  search_product(ProductMap);
              }
              if (op == 2) {
                  search_type();
              }
              if (op == 3) {
                  search_brand();
              }

              printf("Seleccione el orden deseado:\n\n");
              printf("1. Orden por precio\n");
              printf("2. Orden por marca\n");
              printf("3. Orden por tipo\n");
              printf("4. Orden alfabético\n");
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

              printf("Escriba 1 si desea agregar algun producto al carro\n");
              scanf("%d", &op);
              if (op == 1) {
                  push_cart();
              }
              printf("¿Desea seguir buscando?\n");
              printf("1. Sí\n");
              printf("2. No\n");
              scanf("%d", &op2);
          }
        }
        
        if (op == 2) {
            show_cart();
            printf("Escriba 1 si desea quitar del carro\n");
            scanf("%d", &op);

            if (op == 1) {
                pop_cart();
            }
        }
        
        if (op == 3) {
            show_recom();
        }
        
        if (op == 4) {
            complete_purchase();
        }
        
        if (op == 5) {
            show_points();
        }
        
        if (op == 6) {
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