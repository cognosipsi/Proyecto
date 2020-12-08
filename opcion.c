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
    int id;         // Código del producto
    char name[60];  // Nombre del producto
    char brand[40]; // Marca del producto
    int price;      // Precio del producto
    char type[40];  // Tipo del producto
    int stock;      // Cantidad de productos
}product;           // Struct de productos

typedef struct{
    product product;// Struct de productos
    int to_buy;     // Cantidad de productos a comprar
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

void import(HashMap *ProductMap) {
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
        for(i = 0 ; i < 5 ; i++) {
            if (i == 0) {
                info->id = atoi(aux);
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
        }
        if(searchMap(ProductMap, info->id) == NULL) {
            ProductList = create_list();
            push_back(ProductList, info);
            insertMap(ProductMap, info->id, ProductList);
        }
        else {
            push_back(searchMap(ProductMap, info->id), info);
        }
    }
    while(ProductList!=NULL) {	
      first(ProductList);	
      iterator = (product*)malloc(sizeof(product));	
      iterator = first(ProductList);	
      while (iterator != NULL) {	
        printf("%d ", (int)iterator->id);	
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("%d ", iterator->price);	
        printf("%s ", iterator->type);	
        printf("\n");	
        iterator = next(ProductList);	
      }
}

void search_product() {}

void search_type() {}

void search_brand() {}

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