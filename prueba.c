#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prueba.h"

/*Método implementado para el control de los parámetros del comando psinfo.
* Recibe por parametros el vector de argumentos y la cantidad de elementos que tiene este.
*/    
int buscarInconsistencia(char *parametros[], int arg){
    //Declaración de variables
    char mensaje[50];
    char aux[2];
    aux[0] = ' ';
    aux[1] = '\0';
    int control = 0;
    int controlComando;
    int controlProceso;

    // Se valida que al tener 2 argumentos, solo se tenga el nombre del programa en C y el proceso del que se requiere la información.
    if(arg == 2 && parametros[1][0] == '-'){
        return -3;
    }

    //Se valida el tener más de dos argumentos y recibr un comando de la forma -X para decidir la acción a realizar
    if (arg > 2 && (parametros[1][0] != '-' && parametros[arg-1][0] != '-')){
        return -2;
    }

    //Se valida que no haya más de un cómando con la forma -X.
    if(parametros[1][0] == '-' && parametros[arg-1][0] == '-'){
        return -1;
    }
   

    for(int i = 1; i < arg; i++){
        /*Condicional que evalua que los comando de la forma -X solo estén en la primera o en la última posición, 
        * y que no sean diferentes de -l o -r.
        */
        if((i == 1 || i == arg-1) && parametros[i][0] == '-'){
            controlComando = 0;
            if(parametros[i][2] != '\0' && controlComando == 0 && (parametros[i][1] != 'l' || parametros[i][1] != 'r')){
               controlComando = 1;
               control++;
            }
            //Si todo está bien se guarda en un string con los parámetros que son válidos.
            if(controlComando == 0){
                strcat(mensaje, parametros[i]);
                strcat(mensaje, aux);
            }
        } else {
            /*Condicional que evalua que los argumentos que se refieren a los procesos sólo sean de forma númerica.
            */
            controlProceso = 0;
            for(int j = 0; j < strlen(parametros[i]); j++){             
                if((parametros[i][j] < '0' || parametros[i][j] > '9') && controlProceso == 0){
                    controlProceso = 1;
                    control++;
                }
            }
            //Si todo está bien se guarda en un string con los parámetros que son válidos.
            if(controlProceso == 0){
                strcat(mensaje, parametros[i]);
                strcat(mensaje, aux);
            }         
        }        
    }
    //Si se encontró un error, se muestra un mensaje con los parámetros que son válidos.
    if(control != 0){
        printf("Error al ingresar los parametros\n");
        printf("Parametros validos: %s\n", mensaje);
    }    
    return control;
}