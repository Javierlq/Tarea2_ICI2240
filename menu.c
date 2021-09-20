#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers/menu.h"
#include "headers/funciones.h"
#include "headers/map.h"


/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

void initMenu() {
    Map* productos = createMap(is_equal_string);
    Map* productosPorMarca = createMap(is_equal_string);
    Map* productosPorTipo = createMap(is_equal_string);
    // Cola para el carrito
    setSortFunction(productos, lower_than_string);
    setSortFunction(productosPorMarca, lower_than_string);
    setSortFunction(productosPorTipo, lower_than_string);
    
    int choice;

    while(choice != 0) {
        printf(" ---------------------------------------------------------------------- \n");
        printf("|                                                                      |\n");
        printf("|         MENU OPCIONES                                                |\n");
        printf("|                                                                      |\n");
        printf("|         1: Importar productos desde un archivo CSV                   |\n");
        printf("|         2: Exportar productos a un archivo CSV                       |\n");
        printf("|         3: Agregar un producto                                       |\n");
        printf("|         4: Buscar un producto por tipo                               |\n");
        printf("|         5: Buscar un producto por marca                              |\n");
        printf("|         6: Buscar un producto por nombre                             |\n");
        printf("|         7: Mostrar todos los productos                               |\n");
        printf("|         8: Agregar al carrito de compras                             |\n");
        printf("|         9: Concretar compra                                          |\n");
        printf("|         0: Salir                                                     |\n");
        printf("|                                                                      |\n");
        printf(" ----------------------------------------------------------------------\n");

        choice = getChoice();

        switch (choice) {
            case 1:
                importarProductos(productos, productosPorMarca, productosPorTipo, "Archivo_100productos.csv");
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                buscarPorCriterio(productosPorTipo, "aseo");
                break;
            case 5:
                buscarPorCriterio(productosPorMarca, "ballerina");
                break;
            case 6:
                buscarPorCriterio(productos, "shampoo 1 L");
                break;
            case 7:
                break;
            case 8:
                break;
            case 9: 
                break;
            case 10:
                break;
        }
    };  
}

/*
    Función que solicita la opción al usuario. Se verifica que la opción ingresada sea un número y no un char o una cadena.
*/

int getChoice() {
    int validInput = 0;
    char inputChoice[3];

    while(validInput == 0) {
        scanf("%2s", inputChoice);
    
        if(isdigit(*inputChoice)){
            return atoi(inputChoice);
        } else {
            printf("La opcion que ingresaste no es valida.");
        }
    }
}
