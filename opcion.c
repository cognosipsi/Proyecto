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
    char name[60];    // Nombre del producto
    char brand[40];   // Marca del producto
    int price;        // Precio del producto
    char type[40];    // Tipo del producto
    int stock;        // Cantidad de productos
}product;             // Struct de productos

typedef struct{
    product producto; // Struct de productos
    int to_buy;       // Cantidad de productos a comprar
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
        if(open_mark || tmp[i]!= '/'){    // Se define el separador de textos como '/'
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

void import(HashMap *idMap, HashMap *typeMap, HashMap *brandMap) { //Se guardan en mapas distintos para facilitar el ordenamiento
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
                info->price = atoi(aux);
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



List *search_product(HashMap *idMap, List *L) {
    char search[60];
    product *iterator;
    printf("Ingrese la palabra a buscar (máximo 40 carácteres) :\n"); // Búsqueda por 
    scanf("%s", search);                                              // coincidencia
    iterator = firstMap(idMap);
    char *founded1;
    char *founded2;
    char *founded3;
    while(iterator != NULL) {
      founded1 = strstr(iterator-> name, search); //'strstr' solo se utiliza para confirmar que se encontro coincidecia (de la palabra buscada vs nombre del producto)
      founded2 = strstr(iterator-> brand, search);
      founded3 = strstr(iterator-> type, search);
      if(founded1 != NULL || founded2 != NULL || founded3 != NULL) { // Basta con que existe una vez cualquiera de las tres comparaciones para añadir el producto (ya sea por nombre, marca o tipo)
        push_back(L,iterator);
      }
      iterator = nextMap(idMap);
    }
    return L;
}

List *search_type(HashMap *typeMap, List *L) { //luego de cada forma de busqueda se implementa un ordenamiento que se decide por el usuario para la distribucion de productos
    int num = 1,num2=1;
    product *iterator;
    L=firstMap(typeMap);
    while(L != NULL) {
      iterator=first(L);
      printf("%d.- %s\n",num,iterator->type);
      num++;    
      L=nextMap(typeMap);
    }
    L=firstMap(typeMap);
    while(num2!=num) {
      num2++;
      L=nextMap(typeMap);
    }
    return L;
}

List *search_brand(HashMap *brandMap, List *L) {
    int num = 1,num2=1;
    product *iterator;
    L=firstMap(brandMap);
    while(L != NULL) {
      iterator=first(L);
      printf("%d.- %s\n",num,iterator->brand);
      num++;    
      L=nextMap(brandMap);
    }
    L=firstMap(brandMap);
    while(num2!=num) {
      num2++;
      L=nextMap(brandMap);
    }
    return L;
}

void price_sort(List *L, TreeMap *tm) {
    product *iterator = first(L);
    int i=1;
    int precio;
    while (iterator != NULL) {
      insertTreeMap(tm,/*iterator->price*/&iterator->price, iterator);
      iterator = next(L);
    }
    iterator = firstTreeMap(tm);
    while (iterator != NULL) {        
        printf("%d %s ",i, iterator->name);	
        printf("%s ", iterator->brand);	
        printf("$%d ", iterator->price);	
        printf("%d ", iterator->stock);
        i++;	
        printf("\n");	
        iterator = nextTreeMap(tm);
    }
}

void brand_sort(List *L, TreeMap *tmc) {
    product *iterator = first(L);
    int cont = 1;
    while (iterator != NULL) {
        insertTreeMap(tmc, iterator->brand, iterator);
        iterator = next(L);
    }
    iterator = firstTreeMap(tmc);
    while (iterator != NULL) {	
        printf("%d ", cont);
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("$%d ", iterator->price);	
        printf("%d ", iterator->stock);	
        printf("\n");	
        cont++;
        iterator = nextTreeMap(tmc);
    }
}

void type_sort(List *L, TreeMap *tmc) {
    product *iterator = first(L);
    int cont = 1;
    while (iterator != NULL) {
        insertTreeMap(tmc, iterator->type, iterator);
        iterator = next(L);
    }
    iterator = firstTreeMap(tmc);
    while (iterator != NULL) {
        printf("%d ", cont);
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("$%d ", iterator->price);	
        printf("%d ", iterator->stock);	
        printf("\n");	
        cont++;
        iterator = nextTreeMap(tmc);
    }
}

void az_sort(List *L, TreeMap *tmc) {
    product *iterator = first(L);
    int cont = 1;
    while (iterator != NULL) {
        insertTreeMap(tmc, iterator->name, iterator);
        iterator = next(L);
    }
    iterator = firstTreeMap(tmc);
    while (iterator != NULL) {
        printf("%d ", cont);
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("$%d ", iterator->price);	
        printf("%d ", iterator->stock);	
        printf("\n");
        cont++;
        iterator = nextTreeMap(tmc);
    }
}

List *push_cart(List *cart,TreeMap *tree) {
    product *iteration=firstTreeMap(tree);
    purchase *comprado;
    int op,num=1;
    printf("Ingrese el numero a la izquierda del nombre del producto para subirlo al carro\n");
    scanf("%d",&op);
    while(num != op){
      num++;
      iteration=nextTreeMap(tree);
    }
    op = 51;
    while (op >=iteration->stock || op < 0){ //la cantidad pedida no puede superar el stock disponible ni tampoco puede ser un numero negativo logicamente
      printf("ingrese la cantidad que quiera comprar del producto\n");
      scanf("%d", &op);
      if(op >50 ){
        printf("No puede ingresar más de %d productos iguales al carrito\n",iteration->stock);
      }
    }
    iteration->stock=iteration->stock-op;
    comprado->to_buy=op;
    comprado->producto=*iteration;   
    push_back(cart, comprado);
    comprado = first(cart);
    while(iteration != NULL) {
      printf("%s %d\n",comprado->producto.name,comprado->to_buy);
      iteration=next(cart);
    }
    return cart;    
}

void pop_cart(List *cart, TreeMap *tm) {
    product *iterator = firstTreeMap(tm);
    purchase *deleted;
    product *iter8tor = first(cart);
    int op;
    int num = 1;
    printf("Ingrese el numero del producto que desea quitar del carro:\n");
    scanf("%d", &op);
    
    while (op != num) { //se itera en el arbol para encontrar el producto
        iterator = nextTreeMap(tm);
        num++;
    }
    op = iterator->stock+1;
    while (op >= iterator->stock || op < 0) {
        printf("Ingrese la cantidad de productos que desea quitar del carro\n");
        scanf("%d", &op);
        if (op >= iterator->stock) {
            iterator->stock = 0;
            deleted->to_buy = 0;
        }
    }
    iterator->stock += op;  
    deleted->to_buy -= op;

    while (iter8tor != NULL) { 
        if (iter8tor == &deleted->producto) {
            pop_current(cart);
            return;
        }
        iter8tor = next(cart);
    }
}

void show_cart(List *cart) { // Muestra los articulos actuales encontrados en el carro de compras
    product *iterator = first(cart);
    while (iterator != NULL) {
        printf("%s ", iterator->name);	
        printf("%s ", iterator->brand);	
        printf("$%d ", iterator->price);	
        printf("%d ", iterator->stock);
        printf("\n");
        iterator = next(cart);
    }
}

int complete_purchase(List *L, int points) {
    int op, cuenta=0;
    int rut;
    printf("Esta seguro de finalizar la compra, ingrese 1 para finalizar\n");
    purchase *ite=first(L);
    scanf("%d",&op);
    if(op==1) {
      if(ite!=NULL) {
        cuenta=cuenta+ite->to_buy*ite->producto.price;
        printf("%s %d\n",ite->producto.name,ite->to_buy);
      }
      printf("Total a pagar: $%d\n",cuenta);
      return 7;    
    }
    return 4;
    printf("Presione 1 para acumular puntos\n");
    scanf("%d", &op);
    if (op == 1) {
        printf("Ingrese su rut\n");
        scanf("%d", &rut);
        points = cuenta/100;
    }
}

void show_points(int points) {
    printf("%d\n", points);
}

void tutorial() {
    int op;
    printf("Hola querido usuario, bienvenido al manual de ayuda provisto por Nopaluch:\n\n\n");
    printf("Esta aplicacion funciona a traves de un menu principal de 7 opciones con submenus que contendrán las distintas herramientas que ofrece la aplicación.\n\n");
    printf("Estas se le mostraran de la siguiente manera:\n");
    printf("  1. Opcion 1\n");
    printf("  2. Opcion 2\n");
    printf("  3. Opcion 3\n\n");
    printf("Para seleccionar una, deberá ingresar en la terminal el numero de la opcion que desea ejecutar y luegro presionar enter.\n\n");
    printf("En las opciones en las que se le pidan datos (como por ejemplo en la busqueda), debera ingresar una sola palabra.\n\n");
    printf("Por ejemplo para realizar una compra:\n");
    printf("  1. Seleccione la  opción 1 para buscar los productos.\n");
    printf("  2. Luego escoja el metodo de busqueda (por producto, por tipo de producto o por marca).\n");
    printf("  3. Indique el orden en el que desea que sean desplegados los productos (por precio, por marca, por tipo u orden alfabetico).\n");
    printf("  4. Ahora aparecerá una lista con productos que usted busco y en caso de querer agregar uno de estos al carro, debera ingresar 1 y luego el numero del producto deseado (al igual que con las opciones).\n");
    printf("  5. Si desea seguir buscando presione 2, sino presione 1\n");
    printf("  6. Al presionar 1 en el paso anterior, se volvera al menu principal, donde se seleccionara la opcion 4 para finalizar la compra\n\n\n");
    printf("¡Gracias por escoger Nopaluch!\n");
    printf("Ingrese 1 para terminar el tutorial\n");
    scanf("%d", &op);
    if (op == 1) return;
}

void faq() {
    int op;
    printf("-¿Que es Nopaluch?\n\n");
    printf("Nopaluch es una aplicacion de supermercado virtual donde se pueda comprar productos de manera más segura, sencilla y didáctica.\n\n");
    printf("Nopaluch es una aplicacion de supermercado virtual donde se pueda comprar productos de manera más segura, sencilla y didáctica.\n\n");
    printf("Funciona a traves del siguiente menu principal con 7 opciones:\n");
    printf("  1. Buscar.\n");
    printf("  2. Mostrar carro.\n\n");
    printf("  3. Productos recomendados.\n");
    printf("  4. Finalizar compra.\n");
    printf("  5. Mostrar puntos acumulados.\n");
    printf("  6. Soporte de ayuda.\n");
    printf("  7. Cerrar aplicación.\n\n");
    printf("  En este menú, las siguientes opciones poseen sus propias funciones (submenús):\n\n");
    printf("  1. Buscar:\n");
    printf("    a. Buscar por producto.\n");
    printf("    b. Buscar por tipo de producto.\n");
    printf("    c. Buscar por marca.\n");
    printf("    d. Orden por precio  (ascendente).\n");
    printf("    e. Orden por marca.\n");
    printf("    f. Orden por tipo.\n");
    printf("    g. Orden alfabético.\n\n");
    printf("    h. Agregar al carro.\n\n");
    printf("  2. Mostrar carro:\n");
    printf("    a. Quitar del carro.\n\n");
    printf("  6. Soporte de ayuda:\n");
    printf("    a. Tutorial\n\n");
    printf("    b. Preguntas frecuentes.\n\n\n");
    printf("  -¿Que limitaciones posee la aplicacion?\n\n");
    printf("  -Necesita de conexión a Internet para poder funcionar.\n");
    printf("  -No posee imágenes digitales (y junto con esto la publicidad).\n");
    printf("  -La interacción es únicamente a través del teclado, a diferencia de otras aplicaciones con interacción táctil.\n");
    printf("  -No se pueden realizar búsquedas de más de una palabra.\n\n\n");
    printf("-¿Como funcionan los puntos acumulados?\n\n");
    printf("Cada vez que se realiza una compra se le pregunta al usuario si desea acumular puntos, al acceder se le solicita su rut.\n\n");
    printf("Estos puntos corresponden al total de la compra dividido en 100 y como indica su nombre, se van acumulando (en cada compra).\n\n\n");
    printf("-¿Como se realiza una compra?\n\n");
    printf("  1. Seleccione la  opción 1 para buscar los productos.\n");
    printf("  2. Luego escoja el metodo de busqueda (por producto, por tipo de producto o por marca).\n");
    printf("  3. Indique el orden en el que desea que sean desplegados los productos (por precio, por marca, por tipo u orden alfabetico).\n");
    printf("  4. Ahora aparecerá una lista con productos que usted busco y en caso de querer agregar uno de estos al carro, debera ingresar 1 y luego el numero del producto deseado (al igual que con las opciones)\n");
    printf("  5. Si desea seguir buscando presione 2, sino presione 1\n");
    printf("  6. Al presionar 1 en el paso anterior, se volvera al menu principal, donde se seleccionara la opcion 4 para finalizar la compra\n\n\n");
    printf("-¿Como puedo acumular puntos?\n\n");
    printf("Al realizar una compra se le preguntara si desea acumular puntos, para  aceptar debera presionar 1.\n\n");
    printf("Luego se lo solicitara su rut, una vez ingresado le aparecera un mensaje diciendo Operacion exitosa.\n\n\n");
    printf("Ingrese 1 para terminar el tutorial\n\n");
    scanf("%d", &op);
    if (op == 1) return;
}