#include <stdbool.h>
#ifndef MODULES
#define MODULES

int borrar(char *textoBrai, char *texto, bool *NUMERAL, bool *MAYUS);

int guardar(char input[], char *textoBrai, char *texto);

int añadir(
    char input[], char *textoBrai, char *texto,
    bool *NUMERAL, bool *MAYUS
);

#endif