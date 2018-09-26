#ifndef FUNC_H_
#define FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Se crea la estructura con los datos necesarios de cada proceso
typedef struct InfoProceso {
    char nombre[100];
    char estado[100];
    char tMemoria[100];
    char tText[100];
    char tData[100];
    char tStack[100];
    char voluntarios[100];
    char noVoluntarios[100];

} InfoProceso;

//Declaración de métodos
void imprimirInfo(FILE *file);
void guardarInfo(FILE *file, FILE *outFile);

#endif