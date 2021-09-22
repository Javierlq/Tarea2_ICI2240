#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/funciones.h"
#include "headers/list.h"


struct Producto {
    char* nombre;
    char* marca;
    char* tipo;
    int stock;
    int precio;
};

struct Carrito {
    char* nombre;
    int total;
};

void importarProductos(Map* productos, Map* productosPorMarca, Map* productosPorTipo, char* nombreArchivo) {
    {
    // Se abre el archivo de mundos csv en modo lectura "r"
    FILE *fp = fopen ("Archivo_100productos.csv", "r");

    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    char* nombre;
    char* marca;
    char* tipo;
    char* cantidad;
    char* precio;

    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL) { // Se lee la linea
        nombre = get_csv_field(linea, 0); // Se obtiene el nombre
        marca = get_csv_field(linea, 1);
        tipo = get_csv_field(linea, 2);
        cantidad = get_csv_field(linea, 3);
        precio = get_csv_field(linea, 4);

        printf("%s %s %s %s %s\n", nombre, marca, tipo, cantidad, precio);

        agregarProducto(productos, productosPorMarca, productosPorTipo, nombre, marca, tipo, cantidad, precio);
    }
}


}
//Funcion para leer el k-esimo elemento de un string (separado por comas)
char *get_csv_field (char * tmp, int k) {
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

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
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

void agregarProducto(Map* productos, Map* productosPorMarca, Map* productosPorTipo, char* nombre, char* marca, char* tipo, char* cantidad, char* precio) {
    List* productosList = searchMap(productos, nombre);
    Producto* auxProducto = NULL;
    int encontrado = 0;

    if (productosList == NULL) {
        productosList = create_list();
        insertMap(productos, nombre, productosList);
    }
    else {
        auxProducto = first(productosList);

        while (auxProducto != NULL) {
            if (strcmp(auxProducto->marca, marca) == 0) {
                encontrado = 1;
                break;
            }

            auxProducto = next(productosList);
        };
    }

    if (!encontrado) {
        auxProducto = crearProducto(nombre, marca, tipo, cantidad, precio);

        List* marcasList = searchMap(productosPorMarca, marca);

        if (marcasList == NULL) {
            marcasList = create_list();
            insertMap(productosPorMarca, marca, marcasList);
        }

        List* tiposList = searchMap(productosPorTipo, tipo);

        if (tiposList == NULL) {
            tiposList = create_list();
            insertMap(productosPorTipo, tipo, tiposList);
        }
        //printf("h %p %p %p %p\n", productosList, marcasList, tiposList, auxProducto);

        push_back(productosList, auxProducto);
        push_back(marcasList, auxProducto);
        push_back(tiposList, auxProducto);
    }
}

void* crearProducto(char* nombre, char* marca, char* tipo, char* stock, char* precio) {
    Producto* producto = malloc(sizeof(Producto));

    producto->nombre = malloc(sizeof(char) * strlen(nombre) + 1);
    producto->marca = malloc(sizeof(char) * strlen(marca) + 1);
    producto->tipo = malloc(sizeof(char) * strlen(tipo) + 1);

    strcpy(producto->nombre, nombre);
    strcpy(producto->marca, marca);
    strcpy(producto->tipo, tipo);

    producto->stock = atoi(stock);
    producto->precio = atoi(precio);

    return producto;    
}

void buscarPorCriterio(Map* criterio, char* key) {
    List* criterioList = searchMap(criterio, key);

    if (criterioList == NULL) {
        printf("No se pudo encontrar ningun producto con el filtro especificado.\n");
        return;
    }
    
    Producto* auxProducto = first(criterioList);
    int cont = 1;

    while (auxProducto != NULL) {
        printf("%d. %s, %s, %s, %d, %d\n", cont, auxProducto->nombre, auxProducto->marca, auxProducto->tipo, auxProducto->stock, auxProducto->precio);

        cont++;
        auxProducto = next(criterioList);
    }
}

void anadirProducto(Map* productos,Map* productosPorMarca,Map* productosPorTipo)
{
    char* nombre = (char*)malloc(sizeof(char)*256);
    char* marca = (char*)malloc(sizeof(char)*256);
    char* tipo = (char*)malloc(sizeof(char)*256);
    char* cantidad = (char*)malloc(sizeof(char)*10);
    char* precio = (char*)malloc(sizeof(char)*10);

    printf("Ingrese el nombre del producto: \n");
    scanf("%s", nombre);
    printf("Ingrese la marca del producto: \n");
    scanf("%s", marca);
    printf("Ingrese el tipo del producto: \n");
    scanf("%s", tipo);
    printf("Ingrese el stock del producto: \n");
    scanf("%s", cantidad);
    printf("Ingrese el precio del producto: \n");
    scanf("%s", precio);
    List* productosList = searchMap(productos, nombre);
    Producto* auxProducto = NULL;
    int encontrado = 0;

    if (productosList == NULL) {
        productosList = create_list();
        insertMap(productos, nombre, productosList);
    }
    else {
        auxProducto = first(productosList);

        while (auxProducto != NULL) {
            if (strcmp(auxProducto->marca, marca) == 0) {
                encontrado = 1;
                break;
            }

            auxProducto = next(productosList);
        };
    }

    if (!encontrado) {
        auxProducto = crearProducto(nombre, marca, tipo, cantidad, precio);

        List* marcasList = searchMap(productosPorMarca, marca);

        if (marcasList == NULL) {
            marcasList = create_list();
            insertMap(productosPorMarca, marca, marcasList);
        }

        List* tiposList = searchMap(productosPorTipo, tipo);

        if (tiposList == NULL) {
            tiposList = create_list();
            insertMap(productosPorTipo, tipo, tiposList);
        }
        //printf("h %p %p %p %p\n", productosList, marcasList, tiposList, auxProducto);

        push_back(productosList, auxProducto);
        push_back(marcasList, auxProducto);
        push_back(tiposList, auxProducto);
    }
}