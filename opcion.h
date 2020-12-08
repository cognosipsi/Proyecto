#ifndef OPCION_H
#define OPCION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "treemap.h"

void import(HashMap *, HashMap *, HashMap *);

void search_product(HashMap *, List *);

void search_type(HashMap *, List *L);

void search_brand(HashMap *, List *L);

void price_sort(List *, TreeMap *);

void brand_sort(List *, TreeMap *);

void type_sort(List *, TreeMap *);

void az_sort(List *, TreeMap *);

void push_cart();

void pop_cart();

void show_cart();

void show_recom();

void complete_purchase();

void show_points();

void tutorial();

void faq();

#endif