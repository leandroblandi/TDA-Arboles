#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

#define CANTIDAD_ARBOLES 100

int main()
{

    Arbol arboles[CANTIDAD_ARBOLES];

    inicializarArboles(arboles);

    agregarArbol(arboles);

    mostrarArboles(arboles);

    guardarArboles(arboles);

    return 0;
}

