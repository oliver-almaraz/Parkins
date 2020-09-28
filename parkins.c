#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

const char *braille[] = { // Todas las combinaciones posibles de seis puntos ordenados según su representación Unicode
	//  	0 	  1 	2 	 3 	  4    5 	6 	 7     8    9    A     B    C    D    E 	F
/*U+280x*/ 	"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏",
/*U+281x*/ 	"⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟",
/*U+282x*/ 	"⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯",
/*U+283x*/ 	"⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿"
};
const char *perk[] = { // Equivalentes en combinación Perkins (f=punto 1, d=2, s=3, j=4, k=5, l=6) ordenados alfab.
//	 0	   1	  2	      3	 	 4		5	  	6		 7		 8	    9	    A		 B		 C		 D		   E		 F
	" ",  "f",   "d",   "df",   "s",   "fs",   "ds",   "dfs",   "j",   "fj",   "dj",   "dfj",   "js",   "fjs",   "djs",   "dfjs",
	"k",  "fk",  "dk",  "dfk",  "ks",  "fks",  "dks",  "dfks",  "jk",  "fjk",  "djk",  "dfjk",  "jks",  "fjks",  "djks",  "dfjks",
	"l",  "fl",  "dl",  "dfl",  "ls",  "fls",  "dls",  "dfls",  "jl",  "fjl",  "djl",  "dfjl",  "jls",  "fjls",  "djls",  "dfjls",
	"kl", "fkl", "dkl", "dfkl", "kls", "fkls", "dkls", "dfkls", "jkl", "fjkl", "djkl", "dfjkl", "jkls", "fjkls", "djkls", "dfjkls"
};
const char *alpha[] = { // Las letras que corresponden a un solo signo. Signos poco comunes,
// inexistentes en español, o que requieren más de un signo para interpretarse se ignoran ("?").
	   		" ", "a", ",", "b", ".", "k",  ";",  "l", "?",  "c", "i", "f", "í", "m",  "s", "p",
			"@", "e", ":", "h", "*", "o",  "!",  "r", "?",  "d", "j", "g", ")", "n",  "t", "q",
			"?", "?", "?", "(", "-", "u",  "\"", "v", "?",  "?", "?", "?", "ó", "x",  "é", "?",
			"?", "?", "?", "ü", "?", "z",  "=",  "á", "|",  "?", "w", "ñ", "?", "y",  "ú", "?"
};
char *nums[] = {
  // a	b	c	d	 e	  f		g	h	  i	   j
	"⠁","⠃","⠉","⠙","⠑","⠋","⠛","⠓","⠊","⠚",
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
};
const char *diacríticos [] = {
  "á", "é", "í", "ó", "ú", "ü", "ñ",
  "Á", "É", "Í", "Ó", "Ú", "Ü", "Ñ"
};
int main() {

	setlocale(LC_ALL, "");

    char input[8]; // 6 puntos + \n y el pilón
	char textoBrai[3000] = ""; // Tamaño = 1 byte por char, cada letra braille contiene 3 bytes.
	char *texto = (char*)calloc(1000, sizeof(char));
	_Bool MAYUS = 0;
	_Bool NUMERAL = 0;

	while (1) {
		inicio:
		system("clear");
		printf(
			"╔═════════════════════════════════════════════════════════════════════════════════╗\n"
			"║⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿ 𝐁𝐑𝐀𝐈𝐋𝐋𝐄 ⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿║\n"
			"╚═════════════════════════════════════════════════════════════════════════════════╝\n"
			"%s\n\n\n"
			"╔═════════════════════════════════════════════════════════════════════════════════╗\n"
			"║⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿ 𝐓𝐄𝐗𝐓𝐎 ⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿║\n"
			"╚═════════════════════════════════════════════════════════════════════════════════╝\n"
			"%s\n\n\n\n\n"
			"╔═════════════════════════════════════════════════════════════════════════════════╗\n"
			"║ Usa tu teclado Qwerty como Perkins para ingresar 𝐮𝐧 𝐬𝐢𝐠𝐧𝐨 𝐚 𝐥𝐚 𝐯𝐞𝐳 y presiona   ║\n"
			"║ '𝐞𝐧𝐭𝐞𝐫', también puedes ingresar espacios, tabulaciones y saltos de linea.      ║\n"
			"║                     F = punto 1, D=2, S=3 J=4, K=5, L=6.                        ║\n"
			"╟─────────────────────────────────────────────────────────────────────────────────╢\n"
			"║ '𝐛' = 𝐁𝐎𝐑𝐑𝐀𝐑 último elemento de ambas partes (𝐭𝐞𝐱𝐭𝐨 𝐲 𝐛𝐫𝐚𝐢𝐥𝐥𝐞).                 ║\n"
			"║ '𝐫' = 𝐁𝐎𝐑𝐑𝐀𝐑 último elemento 𝐬𝐨𝐥𝐨 de la parte de 𝐛𝐫𝐚𝐢𝐥𝐥𝐞.                       ║\n"
			"║ '𝐰' = 𝐆𝐔𝐀𝐑𝐃𝐀𝐑 el texto braille completo en un documento.                        ║\n"
			"║ '𝐬𝐚𝐥𝐢𝐫' = 𝐒𝐀𝐋𝐈𝐑 sin guardar.                                                    ║\n"
			"╚═════════════════════════════════════════════════════════════════════════════════╝\n", textoBrai, texto);
		
		fgets(input, 8, stdin);

		/******************************************************
		 * Los saltos de línea y tabulaciones se pasan tal cual
		*******************************************************/

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
		} else if (! strcmp(input, " \n")) { // Si es un espacio
			strcat(textoBrai, "⠀");
			strcat(texto, " ");
			NUMERAL = 0;
			continue;
		}
		
		/********************************************************
		 * input == "B" borra el último elemento de ambas partes
		*********************************************************/

		 else if (! strcmp(input, "b\n") || ! strcmp(input, "B\n")) {
			if (textoBrai[strlen(textoBrai)-1] == '\n' || textoBrai[strlen(textoBrai)-1] == '\t') {
			// Para borrar tabulación o salto solo se borra el último char
				textoBrai[strlen(textoBrai)-1] = '\0';
			} else { // Caracteres braille requieren borrar 3 chars
				for (int i=0; i <3; i++) {
					textoBrai[strlen(textoBrai)-1] = '\0';
				}
			}
			// Se borra también el texto normal
			for (int i=0; i<14; i++) {
	// los signos diacríticos de interpretan como dos caracteres, de compara el último de 2
				if (texto[strlen(texto)-1] == diacríticos[i][1]) {
					texto[strlen(texto)-1] = '\0';
				}
			}
			texto[strlen(texto)-1] = '\0';
			continue;
		}
		 // R borra solo de la parte de Braille
		 else if (! strcmp(input, "r\n") || ! strcmp(input, "R\n")) {
			if (textoBrai[strlen(textoBrai)-1] == '\n' || textoBrai[strlen(textoBrai)-1] == '\t') {
			// Para borrar tabulación o salto solo se borra el último char
				textoBrai[strlen(textoBrai)-1] = '\0';
			}
			else { // Caracteres braille requieren borrar 3 chars
				for (int i=0; i <3; i++) {
					textoBrai[strlen(textoBrai)-1] = '\0';
				}
			}
			continue;

		}

		/*****************************************************************
		 * input == "W" crea un documento y guarda el texto braille en él
		******************************************************************/

		 else if (! strcmp(input, "w\n") || ! strcmp(input, "W\n")) {

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
				continue;
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
				exit(0);
			}
			 else
				continue;
		}
		/***********
		 * 'SALIR'
		************/
		 else if (! strcmp(input, "salir\n") || ! strcmp(input, "SALIR\n")) {
			free(texto);
			exit(0);
		}

		/*************************
		 * SI ES UN SIGNO BRAILLE
		**************************/
		
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

		/***********************************
		 * SI ES UNA LETRA O NÚMERO BRAILLE
		************************************/

		for (int i = 0; i <= 64; i++) {
			if (! strcmp(input, perk[i])) { // strcmp() retorna 0 si son idénticas
				// Se añade el signo braille a textoBrai
				strcat(textoBrai, braille[i]);

				// Y se añade el signo del alfabeto a 'texto'

				// Si es el punto 5 seguido de números
				if (NUMERAL && i == 16) {
					NUMERAL = 0;
				}
				 else if (MAYUS) {
					// Primero ver si es diacrítico
					for (int j=0; j<7; j++) {
						if ( ! strcmp(alpha[i], diacríticos[j])) {
							strcat(texto, diacríticos[j+7]);
							MAYUS = 0;
							NUMERAL = 0;
							goto inicio; // salir de los bucles anidados para que no imprima más de un caracter.
						}
					}
					// Si no...
					char mayus[2] = "";
					mayus[0] = toupper(*alpha[i]);
					strcat(texto, mayus);
					MAYUS = 0;
					NUMERAL = 0;
				}
				 else if (NUMERAL && *alpha[i] >=97 && *alpha[i] <=106) { // Si NUMERAL está activado y la letra está en el rango a-j
				 	for (j=0; j<10; j++) {
					 	if (nums[j] == braille[i]) {
							strcat(texto, nums[j+10]);
							goto inicio;
						}
					}
				} 
				 else if (NUMERAL && *alpha[i] >=107 && *alpha[i] <=122) { // Si NUMERAL y se escribe una letra minus. fuera del rango a-j
					NUMERAL=0;
					strcat(texto, alpha[i]);
				}
				 else {
					strcat(texto, alpha[i]);
				}
			}
		}
	}
}