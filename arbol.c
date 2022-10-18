
/*-----------------------
 | Arbol.c
 | Author: Leandro Blandi
 ------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

#define CADENA_SIN_PARSEAR 30
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
    gets(nombre);

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
    int encontrado = -1;
    for(int i = 0; i < CANTIDAD_ARBOLES; i++)
    {
        if(strcmp(arboles[i]->nombre, nombreArbol) == 0)
        {
            printf("\nIngrese nueva edad para \"%s\" (actual: %d): ", arboles[i]->nombre, arboles[i]->edad);
            scanf("%d", &arboles[i]->edad);

            printf("\nIngrese nueva altura para \"%s\" (actual: %.2f): ", arboles[i]->nombre, arboles[i]->altura);
            scanf("%f", &arboles[i]->altura);
        }
    }
    if(encontrado == -1)
    {
        printf("\nNo se encontro arbol con nombre \"%s\", pruebe con otro nombre", nombreArbol);
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

Arbol parsearArboles(char datosSinParsear[30])
{
    int posPrimerDelimitador = -1;
    int posSegundoDelimitador = -1;

    char nombreArbol[25] = "";
    char edadArbol[5] = "";
    char alturaArbol[5] = "";

    // Buscamos primer delimitador
    for(int i = 0; i < CADENA_SIN_PARSEAR; i++)
    {
        if(datosSinParsear[i] == '+')
        {
            posPrimerDelimitador = i;
            i = CADENA_SIN_PARSEAR;
        }
    }

    // Buscamos segundo delimitador
    for(int i = posPrimerDelimitador + 1; i < CADENA_SIN_PARSEAR; i++)
    {
        if(datosSinParsear[i] == '+')
        {
            posSegundoDelimitador = i;
            i = CADENA_SIN_PARSEAR;
        }
    }

    // Separamos los datos: nombre
    for(int i = 0; i < posPrimerDelimitador; i++)
    {
        nombreArbol[i] = datosSinParsear[i];
    }
    nombreArbol[strlen(nombreArbol)] = '\0';

    // Separamos los datos: edad
    for(int i = posPrimerDelimitador + 1; i < posSegundoDelimitador; i++)
    {
        edadArbol[i - posPrimerDelimitador - 1] = datosSinParsear[i];
    }
    edadArbol[strlen(edadArbol)] = '\0';

    // Separamos los datos: altura
    for(int i = posSegundoDelimitador + 1; i < strlen(datosSinParsear); i++)
    {
        alturaArbol[i - posSegundoDelimitador - 1] = datosSinParsear[i];
    }
    alturaArbol[strlen(alturaArbol)]= '\0';

    return crearArbol(nombreArbol, atoi(edadArbol), atof(alturaArbol));
}


 void cargarArboles(Arbol arboles[])
 {
    FILE * archivoArboles = fopen("arboles.txt", "r");

    char datos[30] = "";

    int i = 0;

    while((fgets(datos, CADENA_SIN_PARSEAR, archivoArboles)) && (i < CANTIDAD_ARBOLES))
    {
        arboles[i] = parsearArboles(datos);
        i++;
    }
 }
