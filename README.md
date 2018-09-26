# ComandoPsinfo
Comando desarrollado en c para listar procesos en linux.
Para ejecutar, se deben ejecutar los comandos:
     gcc -Wall *.c -c
     gcc -Wall -o psinfo *.o

Se tienen diferentes modos de utilizar el comando, Y se implementan de la siguiente manera:
    Con <proceso> se hace referencia a los procesos de los que se desea recuperar la información.
    Con <-X> se hace referencia al comando o instrucción que se desea realizar con esta información, siendo de la forma:
        -l: Para mostrar la información en consola.
        -r: Para guardar la información en un archivo.
    ./psinfo <proceso>
    ./psinfo <-X><proceso>...<proceso>
    ./psinfo <proceso>...<proceso><-X>