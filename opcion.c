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
    char id[3];      // Código del producto
    char name[60];   // Nombre del producto
    char brand[40];  // Marca del producto
    int price;       // Precio del producto
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
    int ini_i=0, i=0;
    int j=0;
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
    FILE *fp;
    char linea[1024];
    int i,j;
    product *info;
    const char *aux;
    char *tmp;
    List *ProductList;
    product *iterator;
    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL) {
        info = (product*) malloc(sizeof(product));
        for(i = 0 ; i < 6 ; i++) {
            if (i == 0) {
                strcpy(info->id, aux);
            }
            tmp = strdup(linea);
            aux = get_csv_field(tmp, i);
            free(tmp);
            if (i == 1) {
                strcpy(info->name, aux);
            }
            if (i == 2) {
                strcpy(info->brand, aux);
            }
            if (i == 3) {
                info->price = atoi(aux);
            }
            if (i == 4) {
                strcpy(info->type, aux);
            }
            if (i == 5) {
                info->stock=atoi(aux);
            }
        }
        
        insertMap(idMap, info->id, info);                 // Se guarda en el mapa "id" la id desde info
        if(searchMap(brandMap, info->brand)==NULL) {
            ProductList = create_list();
            push_back(ProductList, info);
            insertMap(brandMap, info->brand, ProductList);
        }
        else {
            push_back(searchMap(brandMap, info->brand), info);
        }
        if(searchMap(typeMap, info->type)==NULL) {
            ProductList = create_list();
            push_back(ProductList, info);
            insertMap(typeMap, info->type, ProductList);
        }
        else {
            push_back(searchMap(typeMap, info->type), info);
        }
    }
    iterator = firstMap(idMap);
    while (iterator != NULL) {	
        printf("%d ", (int)iterator->id);	
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("%d ", iterator->price);	
        printf("%s ", iterator->type);
        printf("%d ", iterator->stock);	
        printf("\n");	
        iterator = nextMap(idMap);	
    }
}

void search_product(HashMap *idMap) {
    char search[40];
    int number=1;
    product *iterator;
    printf("Ingrese la palabra a buscar (máximo 40 carácteres) :\n"); // Búsqueda por 
    scanf("%s", search);                                              // coincidencia
    iterator=firstMap(idMap);
    while(iterator!=NULL) {
      if(strstr(search,iterator->name) || strstr(search,iterator->type) || strstr(search,iterator->brand)) {
        
      }
    }
}

void search_type(HashMap *typeMap) {
    /*
    int num;
    printf("Seleccione la categoría según número (Entre 1 y 8) :\n");
    printf("1.-Pan y pasteleria\n2.-Fiambreria\n3.-Congelados\n4.-Carne\n5.-Frutas y verduras\n6.-Botilleria\n7.-Hogar\n8.-Farmacia y cuidado personal\n\n");
    scanf("%i ", &num);
    */
}

void search_brand(HashMap *brandMap) {
  /*int num = 1;
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
  scanf("%d ", &num);*/
}

void price_sort() {}

void brand_sort() {}

void type_sort() {}

void az_sort() {}

void push_cart() {}

void pop_cart() {}

void show_cart() {}

void show_recom() {}

void complete_purchase() {}

void show_points() {}

void tutorial() {}

void faq() {}