
/*-----------------------
 | Arbol.c
 | Author: Leandro Blandi
 ------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

#define CANTIDAD_ARBOLES 100


struct _Arbol
{
    char nombre[25];
    int edad;
    float altura;
};


/*---------------
 | Constructores
 ----------------*/

Arbol crearArbol(char nombre[], int edad, float altura)
{
    Arbol arbol = malloc(sizeof(struct _Arbol));

    strcpy(arbol->nombre, nombre);
    arbol->edad = edad;
    arbol->altura = altura;

    return arbol;
}

Arbol crearArbolPorTeclado()
{
    char nombre[25];
    int edad;
    float altura;

    printf("\nIngrese nombre del arbol: ");
    fflush(stdin);
    strtok(fgets(nombre, 25, stdin), "\n");

    printf("\nIngrese la edad de \"%s\": ", nombre);
    scanf("%d", &edad);

    printf("\nIngrese la altura para \"%s\": ", nombre);
    scanf("%f", &altura);

    return crearArbol(nombre, edad, altura);

}


/*-----------------------------
 | Procedimientos individuales
 -----------------------------*/

int buscarPosicionLibre(Arbol arboles[])
{
    int posicionLibre = -1;

    for(int i = 0; i < CANTIDAD_ARBOLES; i++)
    {
        if(arboles[i]->edad == -1)
        {
            posicionLibre = i;
            i = CANTIDAD_ARBOLES;
        }
    }
    return posicionLibre;
}


void mostrarArbol(Arbol arbol)
{
    // Si el Arbol es 'no-filtrable'
    if(arbol->edad != -1)
    {
        printf("\nArbol:");
        printf("\n\tNombre: %s", arbol->nombre);
        printf("\n\tEdad: %d", arbol->edad);
        printf("\n\tAltura: %.2f", arbol->altura);
    }
}


void agregarArbol(Arbol arboles[])
{

    int posicionLibre = buscarPosicionLibre(arboles);

    if(posicionLibre != -1)
    {
        arboles[posicionLibre] = crearArbolPorTeclado();
    }
}


void modificarArbol(Arbol arboles[], char nombreArbol[])
{
    for(int i = 0; i < CANTIDAD_ARBOLES; i++)
    {
        if(strcmp(arboles[i]->nombre, nombreArbol) == 0)
        {
            printf("\nIngrese nueva edad para \"%s\" (actual: %d): ", arboles[i]->nombre, arboles[i]->edad);
            scanf("%d", &arboles[i]->edad);

            printf("\nIngrese nueva altura para \"%s\" (actual: %.2f): ", arboles[i]->nombre, arboles[i]->altura);
            scanf("%f", &arboles[i]->altura);
        }
        else
        {
            printf("\nNo se encontro arbol con nombre \"%s\", pruebe con otro nombre", nombreArbol);
        }
    }
}


void eliminarArbol(Arbol arboles[], char nombreArbol[])
{
    for(int i = 0; i < CANTIDAD_ARBOLES; i++)
    {
        if(strcmp(arboles[i]->nombre, nombreArbol) == 0)
        {
            // Lo seteamos como 'filtrable'
            strcpy(arboles[i]->nombre, "");
            arboles[i]->edad = -1;
            arboles[i]->altura = -1.00;
        }
    }
}

/*---------------------------
 | Procedimientos de arreglo
 ----------------------------*/

void inicializarArboles(Arbol arboles[])
{
    for(int i = 0; i < CANTIDAD_ARBOLES; i++)
    {
        // Arboles 'filtrables'
        arboles[i] = crearArbol("", -1, -1.00);
    }
}

void agregarArboles(Arbol arboles[], int cantidadAgregar)
{
    for(int i = 0; i < cantidadAgregar; i++)
    {
        agregarArbol(arboles);
    }
}

void mostrarArboles(Arbol arboles[])
{
    for(int i = 0; i < CANTIDAD_ARBOLES; i++)
    {
        mostrarArbol(arboles[i]);
    }
}


/*---------------------------
 | Procedimientos de archivo
 ----------------------------*/

void guardarArboles(Arbol arboles[])
{
    FILE * archivoArboles = fopen("./arboles.txt", "w");

    if(archivoArboles != NULL)
    {
        for(int i = 0; i < CANTIDAD_ARBOLES; i++)
        {
            // Si el arbol es 'no-filtrable'
            if(arboles[i]->edad != -1)
            {
                fprintf(
                    archivoArboles,
                    "%s+%d+%.2f\n",
                    arboles[i]->nombre,
                    arboles[i]->edad,
                    arboles[i]->altura
                );
            }
        }
    }
    fclose(archivoArboles);
}
