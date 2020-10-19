#include <stdbool.h>
#ifndef OTHER_H_INCLUDED
#define OTHER_H_INCLUDED

int borrar(char *textoBrai, char *texto, bool *NUMERAL, bool *MAYUS);

int guardar(char input[], char *textoBrai, char *texto);

int añadir(
    char input[], char *textoBrai, char *texto,
    bool *NUMERAL, bool *MAYUS
);

#endif