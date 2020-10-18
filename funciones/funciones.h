#include <stdbool.h>
#ifndef OTHER_H_INCLUDED
#define OTHER_H_INCLUDED

int borrar(char textoBrai[], char *texto, const char *diacríticos[], bool *NUMERAL, bool *MAYUS);

int guardar(char input[], char textoBrai[], char *texto);

int añadir(
        char input[], char textoBrai[], char *texto, const char *diacríticos[],
        const char *perk[], const char *braille[], bool *NUMERAL, bool *MAYUS,
        const char *alpha[], const char *nums[]
    );

#endif