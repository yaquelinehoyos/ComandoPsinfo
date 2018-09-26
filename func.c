#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

/*Como el archivo se lee caracter a caracter, éste método se encarga de convertir
un caracter a string para poder concaternarlo y guardarlo en la estructura
*/
void *concatenar(char *nom, char ch){
    char aux[2];
    aux[0] = ch;
    aux[1] = '\0';
    strcat(nom, aux);
    return 0;
}


/*El siguiente método se encarga de guardar la información solicitada 
de cada proceso en la estructura creada en el func.c 
*/
void imprimirInfo(FILE *file){

    //Declaración de variables
    InfoProceso *pInfo = malloc(sizeof(InfoProceso)); //Se pide espacio en memoria para la estructura pInfo
    int counter = 0;
    char ch;
    int flag = 0;

    //Se lee el archivo caracter a caracter
    while((ch = getc(file)) != EOF){
        if(ch == '\n'){
            counter++;  
            flag = 0;
        }
        switch(counter){
            case 0:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->nombre, ch);
                }
                break;
            case 2:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->estado, ch);
                }
                break;
            case 17:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tMemoria, ch);
                }
                break;
            case 25:
               if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tData, ch);
                }
                break; 
            case 26:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tStack, ch);
                }
                break;
            case 27:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tText, ch);
                }
                break;
            case 52:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->voluntarios, ch);
                }
                break;
            case 53:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->noVoluntarios, ch);
                }
                break;
        }
    }
    printf("Nombre del proceso: %s \n", pInfo->nombre);
    printf("Estado: %s \n", pInfo->estado);
    printf("Tamaño total de la imagen de Memoria: %s \n", pInfo->tMemoria);
    printf("Tamaño de la memoria en la region TEXT: %s \n", pInfo->tData);
    printf("Tamaño de la memoria en la region DATA: %s \n", pInfo->tStack);
    printf("Tamaño de la memoria en la region STACK: %s \n", pInfo->tText);
    printf("Numero de contextos realizados (Voluntarios y no voluntarios): %s %s \n", pInfo->voluntarios, pInfo->noVoluntarios);
    pInfo = NULL;
    free(pInfo);
}

void guardarInfo(FILE *file, FILE *outFile){
    InfoProceso *pInfo = malloc(sizeof(InfoProceso));
    int counter = 0;
    char ch;
    int flag = 0;
    while((ch = getc(file)) != EOF){
        if(ch == '\n'){
            counter++;  
            flag = 0;
        }
        switch(counter){
            case 0:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->nombre, ch);
                }
                break;
            case 2:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->estado, ch);
                }
                break;
            case 17:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tMemoria, ch);
                }
                break;
            case 25:
               if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tData, ch);
                }
                break; 
            case 26:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tStack, ch);
                }
                break;
            case 27:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->tText, ch);
                }
                break;
            case 52:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->voluntarios, ch);
                }
                break;
            case 53:
                if(ch == ':'){
                    flag = 1;
                    break;
                }
                if(flag == 1){
                    concatenar(pInfo->noVoluntarios, ch);
                }
                break;
        }
    }    
    fprintf(outFile, "Nombre del proceso: %s \n", pInfo->nombre);
    fprintf(outFile,"Estado: %s \n", pInfo->estado);
    fprintf(outFile, "Tamaño total de la imagen de Memoria: %s \n", pInfo->tMemoria);
    fprintf(outFile, "Tamaño de la memoria en la region TEXT: %s \n", pInfo->tData);
    fprintf(outFile, "Tamaño de la memoria en la region DATA: %s \n", pInfo->tStack);
    fprintf(outFile, "Tamaño de la memoria en la region STACK: %s \n", pInfo->tText);
    fprintf(outFile, "Numero de contextos realizados (Voluntarios y no voluntarios): %s %s \n", pInfo->voluntarios, pInfo->noVoluntarios);
    fprintf(outFile, "...\n");
    pInfo = NULL;
    free(pInfo);
}
