#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

const char *braille[] = {
	//  	0 	  1 	2 	 3 	  4    5 	6 	 7     8    9    A     B    C    D    E 	F
/*U+280x*/ 	"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏",
/*U+281x*/ 	"⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟",
/*U+282x*/ 	"⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯",
/*U+283x*/ 	"⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿"
};
const char *perk[] = {
//	 0	   1	  2	      3	 	 4		5	  	6		 7		 8	    9	    A		 B		 C		 D		   E		 F
	" ",  "f",   "d",   "df",   "s",   "fs",   "ds",   "dfs",   "j",   "fj",   "dj",   "dfj",   "js",   "fjs",   "djs",   "dfjs",
	"k",  "fk",  "dk",  "dfk",  "ks",  "fks",  "dks",  "dfks",  "jk",  "fjk",  "djk",  "dfjk",  "jks",  "fjks",  "djks",  "dfjks",
	"l",  "fl",  "dl",  "dfl",  "ls",  "fls",  "dls",  "dfls",  "jl",  "fjl",  "djl",  "dfjl",  "jls",  "fjls",  "djls",  "dfjls",
	"kl", "fkl", "dkl", "dfkl", "kls", "fkls", "dkls", "dfkls", "jkl", "fjkl", "djkl", "dfjkl", "jkls", "fjkls", "djkls", "dfjkls"
};
const char *alpha[] = {
			"_", "a", ",", "b", ".", "k",  ";",  "l", "?",  "c", "i", "f", "í", "m",  "s", "p",
			"@", "e", ":", "h", "*", "o",  "!",  "r", "?",  "d", "j", "g", ")", "n",  "t", "q",
			"?", "?", "?", "(", "-", "u",  "\"",  "v", "?",  "?", "?", "?", "ó", "x",  "é", "?",
			"?", "?", "?", "ü", "?", "z",  "=",  "á", "|",  "?", "w", "ñ", "?", "y",  "ú", "?"
};
char *nums[] = {
  // a	b	c	d	 e	  f		g	h	  i	   j
	"⠁","⠃","⠉","⠙","⠑","⠋","⠛","⠓","⠊","⠚",
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
};

int main() {

	setlocale(LC_ALL, "");

    char input[8]; // 6 puntos + \n y el pilón
	char textoBrai[3000] = ""; // Tamaño = 1 byte por char, cada letra braille contiene 3 bytes.
	char *texto = (char*)calloc(1000, sizeof(char));
	_Bool MAYUS = 0;
	_Bool NUMERAL = 0;

	while (1) {
		system("clear");
		printf(
			"╔═════════════════════════════════════════════════════════════════════════════════╗\n"
			"║⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿ OUTPUT BRAILLE ⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿║\n"
			"╚═════════════════════════════════════════════════════════════════════════════════╝\n"
			"%s\n\n\n"
			"╔═════════════════════════════════════════════════════════════════════════════════╗\n"
			"║⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿ OUTPUT TEXTO ⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿║\n"
			"╚═════════════════════════════════════════════════════════════════════════════════╝\n"
			"%s\n\n\n\n\n"
			"╔═════════════════════════════════════════════════════════════════════════════════╗\n"
			"║ Usa tu teclado Qwerty como Perkins o escribe 'b' para BORRAR el último elemento.║\n"
			"║ Para BORRAR un elemento solo de la parte de BRAILLE, escribe 'r',               ║\n"
			"║ y para BORRAR un elemento solo de la parte de TEXTO, escribe 't'.               ║\n"
			"║ Escribe 'w' para GUARDAR el texto braille completo a un documento.              ║\n"
			"║ Para SALIR sin guardar escribe 'salir'                                          ║\n"
			"╚═════════════════════════════════════════════════════════════════════════════════╝\n", textoBrai, texto);
		
		fgets(input, 8, stdin);

		// Los saltos de línea y tabulaciones se pasan tal cual
		if (! strcmp(input, "\n")) {
			strcat(textoBrai, "\n");
			strcat(texto, "\n");
			NUMERAL = 0;
			continue;
		} else if (! strcmp(input, "\t\n")) {
			strcat(textoBrai, "\t");
			strcat(texto, "\t");
			NUMERAL = 0;
			continue;
		}
		 else if (! strcmp(input, "b\n") || ! strcmp(input, "B\n")) { // Borrar el útimo elemento
			if (textoBrai[strlen(textoBrai)-1] == '\n' || textoBrai[strlen(textoBrai)-1] == '\t')
			// Para borrar tabulación o salto solo se borra el último char
				textoBrai[strlen(textoBrai)-1] = '\0';
			else // Caracteres braille requieren borrar 3 chars
				for (int i=0; i <3; i++)
					textoBrai[strlen(textoBrai)-1] = '\0';
			// Se borratambién el texto normal
			texto[strlen(texto)-1] = '\0';
		}
		 else if (! strcmp(input, "r\n") || ! strcmp(input, "R\n")) { // R borra solo de la parte de BRaille
			if (textoBrai[strlen(textoBrai)-1] == '\n' || textoBrai[strlen(textoBrai)-1] == '\t')
			// Para borrar tabulación o salto solo se borra el último char
				textoBrai[strlen(textoBrai)-1] = '\0';
			else // Caracteres braille requieren borrar 3 chars
				for (int i=0; i <3; i++)
					textoBrai[strlen(textoBrai)-1] = '\0';

		} else if (! strcmp(input, "t\n") || ! strcmp(input, "T\n")) { // T borra solo de la parte de texto
			texto[strlen(texto)-1] = '\0';
		}
		else if (! strcmp(input, "SALIR\n") || ! strcmp(input, "salir\n")) { // Salir
			free(texto);
			exit(0);
		}

		// escribir "w" crea un nuevo archivo y escribe los contenidos en braille en él.
		 else if (! strcmp(input, "w\n") || ! strcmp(input, "W\n")) {

			char nombre[25];
			time_t t = time(NULL);
  			struct tm tm = *localtime(&t);
  			sprintf(nombre,"braille_%02d-%02d_%02d:%02d.txt", tm.tm_mday, tm.tm_mon + 1, tm.tm_hour, tm.tm_min);
			

			FILE *fptr = fopen(nombre, "w");

			if (fptr == NULL) {
				printf("No se pudo crear el documento de texto.\nPresiona 'Enter' para continuar donde te quedaste.\n");
				fgets(input, 2, stdin);
				continue;
				// No se retorna error para no perder el progreso en caso de error.
			}

			printf("\nCreando el documento '%s' en el directorio actual:\n", nombre);
			system("pwd");
			fprintf(fptr, "%s", textoBrai);
			fclose(fptr);
			printf("\n\n¡Documento guardado con éxito!\n\n");

			// No se termina el programa para no perder el progreso en caso de querer continuar.
			printf("Presiona 'Enter' para continuar escribiendo o escribe 'salir':\n");
			fgets(input, 8, stdin);
			if (! strcmp(input, "salir\n") || ! strcmp(input, "SALIR\n")) {
				free(texto);
				exit(0);
			}
			else
				continue;
		}
		 else
			input[strcspn(input, "\n")]  = '\0'; // Se elimina el \n

			// Se ordena alfabéticamente el input
			char temp;
			int i, j;
			int n = strlen(input);
			for (i = 0; i < n-1; i++) {
				for (j = i+1; j < n; j++) {
					if (input[i] > input[j]) {
							temp = input[i];
							input[i] = input[j];
							input[j] = temp;
					}
				}
		}

		if (! strcmp(input, "jl")) { // Signo de mayúscula
			MAYUS = 1;
			NUMERAL = 0;
			strcat(textoBrai, braille[40]);
			continue;
		} else if (! strcmp(input, "jkls")) { // Numeral
			NUMERAL = 1;
			strcat(textoBrai, braille[60]);
			continue;
		}

		for (int i = 0; i <= 64; i++) {
			if (! strcmp(input, perk[i])) { // strcmp() retorna 0 si son idénticas
				// Se añade el signo braille a textoBrai
				strcat(textoBrai, braille[i]);

				if (i == 0 || i == 16) // Si es el espacio o el punto 5
					NUMERAL = 0;

				// y el signo del alfabeto a texto

				if (MAYUS) {
					char mayus = toupper(*alpha[i]);
					char *pMayus = &mayus;
					strcat(texto, pMayus);
					MAYUS = 0;
					NUMERAL = 0;
				}
				 else if (NUMERAL && *alpha[i] >=97 && *alpha[i] <=106) { // Si NUMERAL está activado y la letra está en el rango a-j
				 	for (j=0; j<10; j++) {
					 	if (nums[j] == braille[i]) {
							strcat(texto, nums[j+10]);
							continue;
						}
					}
				} 
				else {
					strcat(texto, alpha[i]);
					continue;
				}
			}
		}
	}
}