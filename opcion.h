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

void search_product(HashMap *);

void search_type(HashMap *);

void search_brand(HashMap *);

void price_sort();

void brand_sort();

void type_sort();

void az_sort();

void push_cart();

void pop_cart();

void show_cart();

void show_recom();

void complete_purchase();

void show_points();

void tutorial();

void faq();

#endif