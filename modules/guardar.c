/*
* Se crea un documento .txt y se escriben en él
* los signos braille. El nombre del doc. por defecto
* se crea con una timestamp, pero se puede cambiar.
* Al terminar, se puede salir del programa o regresar
* a 'main' a continuar escribiendo.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modules.h"

int guardar(char input[], char *textoBrai, char *texto) {
    char nombre[25];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(nombre,"braille_%02d-%02d_%02d:%02d.txt", tm.tm_mday, tm.tm_mon + 1, tm.tm_hour, tm.tm_min);
    FILE *fptr = NULL;
    
    printf("\nSe creará el documento '%s' en el directorio actual:\n", nombre);
    system("pwd");
    printf("¿Quieres guardarlo con otro nombre o en otra ubicación? s/n\n");
    char resp[3];
    fgets(resp,3,stdin);
    
    if ( ! strcmp(resp, "s\n") || ! strcmp(resp, "S\n")) {
        char rutaAbsol[250] = "";
        printf("Ingresa la ruta absoluta (nombre incluido) del documento a crear (si existe será sobreescrito):\n");
        fgets(rutaAbsol, 250, stdin);
        rutaAbsol[strcspn(rutaAbsol, "\n")] = '\0';
        fptr = NULL;
        fptr = fopen(rutaAbsol, "w");

    } else {
        fptr = fopen(nombre, "w");
    }
    
    if (fptr == NULL) {
        printf("No se pudo crear el documento de texto.\nPresiona 'Enter' para continuar donde te quedaste.\n");
        fgets(input, 2, stdin);
        return 1;
        // No se retorna error para no perder el progreso en caso de error.
    }

    fprintf(fptr, "%s", textoBrai);
    fclose(fptr);
    printf("\n\n¡Documento guardado con éxito!\n\n");
    fptr = NULL;

    // No se termina el programa para no perder el progreso en caso de querer continuar.
    printf("Presiona 'Enter' para continuar escribiendo o escribe 'salir':\n");
    fgets(input, 8, stdin);
    if (! strcmp(input, "salir\n") || ! strcmp(input, "SALIR\n")) {
        free(texto);
        free(textoBrai);
        exit(0);
    }
    else
        return 0;
};