#include "map.h"

typedef struct Producto Producto;

typedef struct Carrito Carrito;

/*
    Funciones para importación desde CSV
*/

char* get_csv_field (char * tmp, int k);

void importarProductos(Map* productos, Map* productosPorMarca, Map* productosPorTipo, char* nombreArchivo);

/*
    Funciones para crear y agregar los productos
 */

void agregarProducto(Map* productos, Map* productosPorMarca, Map* productosPorTipo, char* nombre, char* marca, char* tipo, char* cantidad, char* precio);

void* crearProducto(char* nombre, char* marca, char* tipo, char* cantidad, char* precio);

/*
    Funciones para buscar
*/

void buscarPorCriterio(Map* criterio, char* key);

void anadirProducto(Map* productos, Map* productosPorMarca, Map* productosPorTipo);