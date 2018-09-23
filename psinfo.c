#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int buscarInconsistencia(char *parametros){
    char *ch = parametros;
    int counter = 0;
    
    while(*ch != '\0'){
        if(*ch == '-'){
            counter++;
        }
        ch++;
    }
    if(counter == 1){
        return 1;
    }
    return 0;
}

int reconocerComando(char *parametros){
    char *ch = parametros;
    
    while(*ch != '-'){
        ch++;
    }
    ch++;
    switch(*ch){
        case 'l':
            ch++;
            if(*ch == ' ' || *ch == '\0'){
                return 0;
            } 
            return -1;
        case 'r':
            ch++;
            if(*ch == ' ' || *ch == '\0'){
                return 1;
            }  
            return -1;
        default:
            return -1;
    }
}

int encontrarPosicion(char *parametros){
    int evitar = 0;
    char *ch = parametros;

    while(*ch != '-'){
        if(*ch == ' ' || *ch == '\0'){
            evitar++;
        }
        ch++;
    }    
    return evitar;
}

int main(int argc, char *argv[]){
    FILE *file;
    char ruta[50], fin[50]; 
    int auxi = 0;
    for(int i = 0; i < strlen(argv)-1; i++){ 
        auxi = auxi + buscarInconsistencia(argv[i]);
    }
    if(auxi > 1){
        printf("Error: Comando no reconocido");
        return 0;
    }
    if(argc == 2){
        printf("pid: %s \n", argv[1]);
        strcpy(ruta, "/proc/");
        strcpy(fin, "/status");
        strcat(ruta, argv[1]);
        strcat(ruta, fin);
        file = fopen(ruta, "r");
        if(!file){
            printf("Proceso no encontrado, verificar informacion \n");
            return 0;
        }
        imprimirInfo(file);
        fclose(file);
    }
    else if(argc > 2) {
        int comando = reconocerComando(*argv);
        int evitar;
        int i = 1;
        switch(comando){
            case 0:
                evitar = encontrarPosicion(*argv);
                if(evitar != 1 && evitar != argc-1){
                    printf("Error: Comando no reconocido\n");
                    return 0;
                } 
                printf("-- ¡¡¡Informacion recolectada!!! \n\n");
                while(argv[i] != NULL){
                    if(i != evitar){
                        printf("pid: %s \n", argv[i]);
                        strcpy(ruta, "/proc/");
                        strcpy(fin, "/status");
                        strcat(ruta, argv[i]);
                        strcat(ruta, fin);
                        file = fopen(ruta, "r");
                        if(!file){
                            printf("Proceso no encontrado, verificar informacion \n... \n");
                            i++;
                            continue;
                        }
                        imprimirInfo(file);
                        printf("... \n");
                        fclose(file);
                    }
                    i++;
                }                
                break;
            case 1:
                evitar = encontrarPosicion(*argv);
                if(evitar != 1 && evitar != argc-1){
                    printf("Error: Comando no reconocido\n");
                    return 0;
                }
                char *nArchivo = malloc(sizeof(char)*50);
                strcpy(nArchivo, "psinfo-report");
                while(argv[i] != NULL){
                    if(argv[i+1] != NULL){
                        strcat(nArchivo, "-");
                    }
                    if(i != evitar){
                        strcat(nArchivo, argv[i]);   
                    }
                    i++;
                }
                strcat(nArchivo, ".info");
                FILE *outFile = fopen(nArchivo, "w");
                i = 1;
                while(argv[i] != NULL){
                    if(i != evitar){
                        strcpy(ruta, "/proc/");
                        strcpy(fin, "/status");
                        strcat(ruta, argv[i]);
                        strcat(ruta, fin);
                        file = fopen(ruta, "r");
                        if(!file){
                            fprintf(outFile, "Proceso %s no encontrado \n... \n", argv[i]);
                            i++;
                            continue;
                        }
                        guardarInfo(file, outFile);
                        fclose(file);
                    }
                    i++;
                }
                printf("Archivo de salida generado: %s \n", nArchivo);
                fclose(outFile);
                free(nArchivo);
                break;                
            default:
                printf("Error: Comando no reconocido\n");
        }
    }  else {
        printf("Error: Comando no reconocido\n");
    } 
    return 0;
}