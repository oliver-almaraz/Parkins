/*
Si es una letra, número o signo de puntuación,
se añade el signo braille a 'textoBrai' y el equivalente
en texto español a 'texto'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "modules.h"

extern const char *diacríticos[];
extern const char *perk[];
extern const char *braille[];
extern const char *alpha[];
extern const char *nums[];

int añadir(
        char input[], char *textoBrai, char *texto,
        bool *NUMERAL, bool *MAYUS
    ) {

    for (register int i = 0; i <= 64; i++) {

        if (! strcmp(input, perk[i])) { // strcmp() retorna 0 si son idénticas
            // Se añade el signo braille a textoBrai
            strcat(textoBrai, braille[i]);

            // Y se añade el signo del alfabeto a 'texto'

            // Si es el punto 5 seguido de números
            if (*NUMERAL && i == 16) {
                *NUMERAL = false;
            }
                else if (*MAYUS) {
                // Primero ver si es diacrítico
                for (int j=0; j<7; j++) {
                    if ( ! strcmp(alpha[i], diacríticos[j])) {
                        strcat(texto, diacríticos[j+7]);
                        *MAYUS = true;
                        *NUMERAL = false;
                        return 0; // salir de los bucles anidados para que no imprima más de un caracter.
                    }
                }
                // Si no...
                char mayus[2] = "";
                mayus[0] = toupper(*alpha[i]);
                strcat(texto, mayus);
                *MAYUS = false;
                *NUMERAL = false;
            }
                else if (*NUMERAL && *alpha[i] >=97 && *alpha[i] <=106) {
                    // Si NUMERAL está activado y es un número
                for (int j=0; j<10; j++) {
                    if (nums[j] == braille[i]) {
                        strcat(texto, nums[j+10]);
                        return 0;
                    }
                }
            } 
                else if (*NUMERAL && *alpha[i] >=107 && *alpha[i] <=122) { // Si NUMERAL y se escribe una letra minus. fuera del rango a-j
                *NUMERAL=false;
                strcat(texto, alpha[i]);
            }
                else if (*NUMERAL &&
                        (
                            ! strcmp(input, "dks") || // '+'
                            ! strcmp(input, "dls") || // '*'
                            ! strcmp(input, "kls") // '/'
                        )
                        ) {

                    // Si es un signo matemático
                if ( ! strcmp(input, "dks") )
                    strcat(texto, "+");
                else if ( ! strcmp(input, "dls") )
                    strcat(texto, "*");
                else if ( ! strcmp(input, "kls") )
                    strcat(texto, "/");
                *NUMERAL = false;
            }
                else {
                strcat(texto, alpha[i]);
                *NUMERAL = false;
            }
        }
	}
    return 0;
};
