#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "func.h"
#include "prueba.h"

// Variable global para el manejo de errores.
int errno;

/*El siguiente método se creó con la finalidad de reconocer el primer comando,
los comandos siguientes los ignora y ejecuta el primero. En caso de no reconocer
uno de los comandos -l o -r, retorna un -1 el cual nos imprime un error en el main.
Como argumento se le ingresan los *argv[] del main.
*/
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

/* El siguiente método se encarga de buscar la posición del camndo -l o -r, los cuales 
deben ir al principio o al final del ID de los procesos que se requiere listar.
Como argumento se le ingresan los *argv[] del main.
*/
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

    //Declaración de variables
    FILE *file;
    char ruta[50], fin[50]; 

    //Se buscan errores en los parámetros
    int errores = buscarInconsistencia(argv, argc);

    /*Si al buscar inconsistencias en los parámetros el retorno es diferente de 0, se realiza un manejo de errores
    * mediante el uso de la librería <errno.h>.
    */
    if(errores != 0){
        switch(errores){
            case -3:
                printf("Error al ingresar los parametros \nIngrese el ID del proceso que desea consultar\n");
                break;
            case -2:
                printf("Error al ingresar los parametros \nFalta acción a realizar: -l para mostrar la información         -r para guardar la información en archivo\n");
                break;
            case -1:
                printf("Error al ingresar los parametros \nIngrese un unico comando de la forma -X: -l para mostrar la información         -r para guardar la información en archivo\n");
                break;
        }
        errno = 1;
        fprintf(stderr, "Numero del error: %d\n", errno);
        perror("Error encontrado");
        return 0;
    }

    //En caso de sólo requerir la información de un sólo proceso
    if(argc == 2){

        //Se crea la ruta del archivo
        printf("pid: %s \n", argv[1]);
        strcpy(ruta, "/proc/");
        strcpy(fin, "/status");
        strcat(ruta, argv[1]);
        strcat(ruta, fin);
        file = fopen(ruta, "r");

        //Verificamos que el archivo exista
        if(!file){
            errno = 2;
            fprintf(stderr, "Numero del error: %d\n", errno);
            perror("Error encontrado");
            return 0;
        }

        //Llamamos el método que nos recolecta la información de cada proceso
        imprimirInfo(file);
        fclose(file); //Cerramos el archivo
    }

    //En caso de requerir la información de más de un proceso
    else if(argc > 2) {
        int comando = reconocerComando(*argv); //Reconocemos el comando -l o -r
        int evitar; 
        int i = 1;
        switch(comando){
            case 0:
                /* Reconocemos la posición del comando en los argumentos, 
                esto con el fin de ignorarlo y que no lo busque como proceso.  ANTES DEL SWITCH
                */
                evitar = encontrarPosicion(*argv);

                /* En caso de que el comando -l o -r no estén al principio o al final de los
                procesos, el programa imprime "Error"
                */
                if(evitar != 1 && evitar != argc-1){
                    errno = 1;
                    fprintf(stderr, "Numero del error: %d\n", errno);
                    perror("Error encontrado");
                    return 0;
                } 

                printf("-- ¡¡¡Informacion recolectada!!! \n\n");
                while(argv[i] != NULL){
                    if(i != evitar){

                        //Se crea la ruta del archivo
                        printf("pid: %s \n", argv[i]);
                        strcpy(ruta, "/proc/");
                        strcpy(fin, "/status");
                        strcat(ruta, argv[i]);
                        strcat(ruta, fin);
                        file = fopen(ruta, "r");

                        //Verificamos que el archivo exista
                        if(!file){
                            errno = 2;
                            fprintf(stderr, "Numero del error: %d\n", errno);
                            perror("Error encontrado");
                            printf("... \n");
                            i++;
                            continue;
                        }

                        //Llamamos el método que nos recolecta la información de cada proceso
                        imprimirInfo(file);
                        printf("... \n");
                        fclose(file); //Cerramos el archivo
                    }
                    i++;
                }                
                break;
            case 1:
                /* Reconocemos la posición del comando en los argumentos, 
                esto con el fin de ignorarlo y que no lo busque como proceso.  ANTES DEL SWITCH
                */
                evitar = encontrarPosicion(*argv);

                /* En caso de que el comando -l o -r no estén al principio o al final de los
                procesos, el programa imprime "Error"
                */
                if(evitar != 1 && evitar != argc-1){
                    errno = 1;
                    fprintf(stderr, "Numero del error: %d\n", errno);
                    perror("Error encontrado");
                    return 0;
                }

                // nArchivo es la variable que guarda el nombre del archivo a crear
                char *nArchivo = malloc(sizeof(char)*50);
                strcpy(nArchivo, "psinfo-report");

                //Creamos el nombre del archivo .txt donde guardaremos la información de los procesos
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

                //Creamos el archivo de salida con el nombre guardado en la variable nArchivo
                FILE *outFile = fopen(nArchivo, "w");
                i = 1; // La variable i la inicializamos en 1 porque el argumento argv[0] guarda el comando psinfo
                while(argv[i] != NULL){
                    if(i != evitar){

                        //Se crea la ruta del archivo
                        strcpy(ruta, "/proc/");
                        strcpy(fin, "/status");
                        strcat(ruta, argv[i]);
                        strcat(ruta, fin);
                        file = fopen(ruta, "r");

                        //Verificamos que el archivo exista
                        if(!file){
                            fprintf(outFile, "Proceso %s no encontrado \n... \n", argv[i]);
                            i++;
                            continue;
                        }

                        //Llamamos el método que nos recolecta en el archivo .txt la información de cada proceso
                        guardarInfo(file, outFile);
                        fclose(file); //Cerramos el archivo
                    }
                    i++;
                }
                
                printf("Archivo de salida generado: %s \n", nArchivo);
                fclose(outFile); //Cerramos el archivo .txt que creamos con la información de los procesos
                free(nArchivo); //Liberamos el espacio de memoria que solicitamos para la variable nArchivo
                break;  

            default:
                errno = 1;
                fprintf(stderr, "Numero del error: %d\n", errno);
                perror("Error encontrado");
                return 0;
        }
    }  else {
        errno = 1;
        fprintf(stderr, "Numero del error: %d\n", errno);
        perror("Error encontrado"); 
    } 
    return 0;
}