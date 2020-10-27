/*
* Se borra el último elemento de ambas partes: texto y braille.
* Consideraciones especiales para signos que ocupan dos chars y
* para signos que hay que borrar juntos.
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "modules.h"

extern const char *diacríticos[];

int borrar(char *textoBrai, char *texto, bool *NUMERAL, bool *MAYUS) {

    if (textoBrai[strlen(textoBrai)-1] == '\n' || textoBrai[strlen(textoBrai)-1] == '\t') {
                // Para borrar tabulación o salto solo se borra el último char
                    textoBrai[strlen(textoBrai)-1] = '\0';
    }
     else { // Caracteres braille requieren borrar 3 chars

        if ( ! strcmp(textoBrai + (strlen(textoBrai)-3), "⠨")){ //se borra mayus
            *MAYUS = false;
            for (int i=0; i < 3; i++) {
                textoBrai[strlen(textoBrai)-1] = '\0';
            }
            return 0;
        }
        else if ( ! strcmp(textoBrai + (strlen(textoBrai)-3), "⠼")) {	 //se borra numeral
            *NUMERAL = false;
            for (int i=0; i < 3; i++) {
                textoBrai[strlen(textoBrai)-1] = '\0';
            }
            return 0;
        }

        for (int i=0; i <3; i++) {
            textoBrai[strlen(textoBrai)-1] = '\0';
        }
    }
    // Si después de borrar el último caracter braille quedó un s. numeral o de mayus:
    if (
        ( ! strcmp(textoBrai + (strlen(textoBrai)-3), "⠨")) || //mayus
        ( ! strcmp(textoBrai + (strlen(textoBrai)-3), "⠼"))	 //numeral
    ) {
        for (int i=0; i <3; i++) {
            textoBrai[strlen(textoBrai)-1] = '\0';
        }
        *NUMERAL = false; // Se desactiva NUMERAL si se borra el signo numeral
        // MAYUS no se desactiva porque de desactiva solo a la primera letra después de él
    }


    // Se borra también el texto normal
    
    // Primero el caracter de reemplazo para signo desconocido '�':
    if ( ! strcmp(texto + (strlen(texto)-3), "�") ) {
        for (int i=0; i<2; i++)
            texto[strlen(texto)-1] = '\0';
    }
    for (int i=0; i<14; i++) {
    // los signos diacríticos de interpretan como dos caracteres, se comparan como string
        if ( ! strcmp(texto + (strlen(texto)-2), diacríticos[i]) ) {
            texto[strlen(texto)-1] = '\0';
        }
    }
    texto[strlen(texto)-1] = '\0';

    // Si después de borrar ambas partes quedó un punto 5 como separador, se borra.
    if (
        ( ! strcmp(textoBrai + (strlen(textoBrai)-3), "⠐")) && // Punto 5
        texto[strlen(texto)-1] != '@' // no usado como '@'
    ) {
        for (int i=0; i <3; i++) {
            textoBrai[strlen(textoBrai)-1] = '\0';
        }
        *NUMERAL = true;
    }

    if ( isdigit(texto[strlen(texto)-1]) ){
        // Por si se borró s. de mayus o punto 5 solamente,
        // se regresa a seguir escribiendo nums.
        *NUMERAL = true;
    }

    return 0;
};