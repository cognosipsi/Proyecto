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

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}

int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}

int higher_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1>k2;
}

int main (void) {
    int op;
    int op2;
    HashMap *idMap = createMap(100);
    HashMap *brandMap = createMap(100);
    HashMap *typeMap = createMap(100);
    import(idMap,typeMap,brandMap);
    List *L = create_list();
    TreeMap *tm = createTreeMap(lower_than_int);
    TreeMap *tmc = createTreeMap(lower_than_string);
    printf("¿Desea ver un tutorial?\n");
    printf("1. Si\n");
    printf("2. No\n");
    scanf("%d", &op);
    if(op == 1) {
        tutorial();
    }
    List *cart=create_list();
    while(op != 7) {
        printf("Seleccione una opción:\n\n");
        printf("1. Buscar\n");
        printf("2. Mostrar carro\n");
        printf("3. Productos recomendados\n");
        printf("4. Finalizar compra\n");
        printf("5. Mostrar puntos acumulados\n");
        printf("6. Soporte de ayuda\n");
        printf("7. Cerrar aplicacion\n");
        scanf("%d", &op);
        if (op == 1) {
          while (op2 != 2) {
              L=create_list();
              printf("Seleccione una opción:\n\n");
              printf("1. Buscar por producto\n");
              printf("2. Buscar por tipo de producto\n");
              printf("3. Buscar por marca\n");
              scanf("%d", &op);

              if (op == 1) {
                  L = search_product(idMap, L);
              }
              if (op == 2) {
                  L = search_type(typeMap, L);
              }
              if (op == 3) {
                  L = search_brand(brandMap, L);
              }

              printf("Seleccione el orden deseado:\n\n");
              printf("1. Orden por precio\n");
              printf("2. Orden por marca\n");
              printf("3. Orden por tipo\n");
              printf("4. Orden alfabético\n");
              scanf("%d", &op);
              if (op == 1) {
                  price_sort(L, tm);
              }
              if (op == 2) {
                  brand_sort(L, tmc);
              }
              if (op == 3) {
                  type_sort(L, tmc);
              }
              if (op == 4) {
                  az_sort(L, tmc);
              }
              printf("Escriba 1 si desea agregar algun producto al carro\n");
              scanf("%d", &op2);
              if (op2 == 1) {
                  if(op==1) cart=push_cart(cart,tm);
                  else cart=push_cart(cart,tmc);
              }
              printf("¿Desea seguir buscando?\n");
              printf("1. Sí\n");
              printf("2. No\n");
              scanf("%d", &op2);
              if (op2 == 2) break;
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