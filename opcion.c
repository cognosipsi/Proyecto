#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct{
    char id[10];      // Código del producto
    char name[60];   // Nombre del producto
    char brand[40];  // Marca del producto
    char price[10];       // Precio del producto
    char type[40];   // Tipo del producto
    int stock;       // Cantidad de productos
}product;            // Struct de productos

typedef struct{
    product product; // Struct de productos
    int to_buy;      // Cantidad de productos a comprar
}purchase;

char *strdup(const char *str) {
    char *aux = (char*) malloc(strlen(str)+1);
    strcpy(aux, str);
    return aux;
}

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i = 0, i = 0;
    int j = 0;
    while(tmp[i+1]!='\0'){
        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }
        if(open_mark || tmp[i]!= '/'){ // análisis separador, antes ","
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }
        if(tmp[i]== '/'){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }
        i++;
    }
    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }
    return NULL;
}

void import(HashMap *idMap, HashMap *typeMap, HashMap *brandMap) {
    FILE *fp = fopen("catalogo.txt", "r");
    char linea[1024];
    int i, j;
    product *info;
    const char *aux;
    char *tmp;
    List *ProductList;
    product *iterator;
    while (fgets (linea, 1023, fp) != NULL) {
        info = (product*) malloc(sizeof(product));
        for(i = 0; i < 6 ; i++) {
            tmp = strdup(linea);
            aux = get_csv_field(tmp, i);
            free(tmp);
            if (i == 0) {
                strcpy(info-> id, aux);
            }
            if (i == 1) {
                strcpy(info-> name, aux);
            }
            if (i == 2) {
                strcpy(info-> brand, aux);
            }
            if (i == 3) {
                strcpy(info-> price, aux);
                //info->price = atoi(aux);
            }
            if (i == 4) {
                strcpy(info-> type, aux);
            }
            if (i == 5) {
                info->stock = atoi(aux);
            }
        }
        insertMap(idMap, info->id, info);              
        //printf("%s %s %s %s %s %d\n",info->id,info->name,info->brand,info->price,info->type,info->stock);
        if(searchMap(brandMap, info-> brand) == NULL) {
            ProductList = create_list();
            push_back(ProductList, info);
            insertMap(brandMap, info->brand, ProductList);
        }
        else {
          push_back(searchMap(brandMap, info->brand), info);
        }
        if(searchMap(typeMap, info-> type) == NULL) {
            ProductList = create_list();
            push_back(ProductList, info);
            insertMap(typeMap, info->type, ProductList);
        }
        else {
            push_back(searchMap(typeMap, info-> type), info);
        }
        if(atoi(info-> id) == 550) break;
    }
    /*ProductList = create_list();
    ProductList = firstMap(brandMap);
    iterator = first(ProductList);
    while (ProductList != NULL) {
      iterator = first(ProductList);
      while(iterator != NULL) {
        printf("%s ", iterator->id);	
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("%s ", iterator->price);	
        printf("%s ", iterator->type);
        printf("%d ", iterator->stock);	
        printf("\n");	
        iterator = next(ProductList);
      }
      ProductList =nextMap(brandMap);
    }*/
}

void search_product(HashMap *idMap, List *L) {
    char search[40];
    int number = 1;
    product *iterator;
    printf("Ingrese la palabra a buscar (máximo 40 carácteres) :\n"); // Búsqueda por 
    scanf("%s", search);                                              // coincidencia
    iterator = firstMap(idMap);
    char *founded1;
    char *founded2;
    char *founded3;
    bool exist = false;
    while(iterator != NULL) {
      founded1 = strstr(search, iterator-> name);
      founded2 = strstr(search, iterator-> brand);
      founded3 = strstr(search, iterator-> type);
      if(founded1 != NULL || founded2 != NULL || founded3 != NULL) {
        exist = true;
      }
      if (exist){
              printf(" %s %s %s ", iterator-> name, iterator->brand, iterator->type);
      }
      iterator=nextMap(idMap);
    }
}

void search_type(HashMap *typeMap, List *L) {
    /*
    int num;
    printf("Seleccione la categoría según número (Entre 1 y 8) :\n");
    printf("1.-Pan y pasteleria\n2.-Fiambreria\n3.-Congelados\n4.-Carne\n5.-Frutas y verduras\n6.-Botilleria\n7.-Hogar\n8.-Farmacia y cuidado personal\n\n");
    scanf("%i ", &num);
    */
}

void search_brand(HashMap *brandMap, List *L) {
  int num = 1,num2=1;
  product *iterator;
  List *L = create_list();
  L=firstMap(brandMap);
  while(L != NULL) {
    iterator=first(L);
    printf("%d.- %s",num,iterator->brand);
    num++;    
    L=nextMap(brandMap);
  }
  printf("Seleccione la marca que quiere\n");
  scanf("%d ", &num);
  L=firstMap(brandMap);
  
  
}

void price_sort(List *L, TreeMap *t) {
    ;
}

void brand_sort(List *L, TreeMap *t) {}

void type_sort(List *L, TreeMap *t) {}

void az_sort(List *L, TreeMap *t) {}

void push_cart() {}

void pop_cart() {}

void show_cart() {}

void show_recom() {}

void complete_purchase() {}

void show_points() {}

void tutorial() {}

void faq() {}