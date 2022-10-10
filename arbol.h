
/*-----------------------
 | Arbol.h
 | Author: Leandro Blandi
 ------------------------*/

#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

struct _Arbol;
typedef struct _Arbol * Arbol;

/*---------------
 | Constructores
 ----------------*/

/// @pre: ninguno
/// @post: devuelve un Arbol
Arbol crearArbol(char nombre[], int edad, float altura);

/// @pre: se ingresa por teclado
/// @post: devuelve un Arbol
Arbol crearArbolPorTeclado();

/// @pre: debe existir el array
/// @post: devuelve un entero que sera usado en otras funciones
/// @return: -1 si no hay mas espacio, [-1 < n < 100] si hay espacio
int buscarPosicionLibre(Arbol arboles[]);


/*-----------------------------
 | Procedimientos individuales
 -----------------------------*/

 /// @pre: el Arbol debe ser 'no filtrable' (edad != -1)
/// @post: muestra todos los datos del Arbol por pantalla
void mostrarArbol(Arbol arbol);

 /// @pre: debe haber espacio, depende de buscarPosicionLibre() y debe existir el array
/// @post: agrega un Arbol en alguna posicion libre, por teclado
void agregarArbol(Arbol arboles[]);

 /// @pre: el Arbol a modificar debe existir
/// @post: modifica la edad y altura del Arbol a modificar
void modificarArbol(Arbol arboles[], char nombreArbol[]);

 /// @pre: el Arbol a 'eliminar' debe existir
/// @post: setea como 'filtrable' al Arbol
void eliminarArbol(Arbol arboles[], char nombreArbol[]);

/*---------------------------
 | Procedimientos de arreglo
 ----------------------------*/

/// @pre: debe existir el array
/// @post: setea las edades y las alturas en -1
void inicializarArboles(Arbol arboles[]);

/// @pre: debe existir el arreglo y cantidadAgregar > 0
/// @post: agrega una cantidad especifica de arboles en las posiciones libres
void agregarArboles(Arbol arboles[], int cantidadAgregar);

/// @pre: debe existir el array y los Arboles deben ser 'no-filtrables'
/// @post: muestra todos los datos de los Arboles en las posiciones
void mostrarArboles(Arbol arboles[]);


/*---------------------------
 | Procedimientos de archivo
 ----------------------------*/

/// @pre: debe existir 'arboles.txt', los Arboles deben ser 'no-filtrabes' y debe existir el array
/// @post: crea/sobreescribe el archivo 'arboles.txt' con todos los datos del arreglo separados por el delimitador '+'
void guardarArboles(Arbol arboles[]);

#endif // ARBOL_H_INCLUDED
