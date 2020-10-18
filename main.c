/*********************************************
Asegúrate de que tu editor esté configurado
con codificación UTF-8.

Compilar en GCC:
>$ gcc ./funciones/borrar.c ./funciones/guardar.c ./funciones/añadir.c main.c

Oliver Almaraz
oliver.almaraz@gmail.com
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "./funciones/funciones.h"

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
// inexistentes en español, o que requieren más de un signo para interpretarse se ignoran ("�").
	   		" ", "a", ",", "b", ".", "k",  ";",  "l", "�",  "c", "i", "f", "í", "m",  "s", "p",
			"@", "e", ":", "h", "*", "o",  "!",  "r", "�",  "d", "j", "g", ")", "n",  "t", "q",
			"�", "�", "?", "(", "-", "u",  "\"", "v", "�",  "�", "�", "�", "ó", "x",  "é", "�",
			"�", "�", "�", "ü", "�", "z",  "=",  "á", "|",  "�", "w", "ñ", "�", "y",  "ú", "�"
};
const char *nums[] = {
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
	bool MAYUS = false;
	bool NUMERAL = false;

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
			NUMERAL = false;
			continue;
		} else if (! strcmp(input, "\t\n")) {
			strcat(textoBrai, "\t");
			strcat(texto, "\t");
			NUMERAL = false;
			continue;
		} else if (! strcmp(input, " \n")) { // Si es un espacio
			strcat(textoBrai, "⠀");
			strcat(texto, " ");
			NUMERAL = false;
			continue;
		}
		
		/********************************************************
		 * input == "B" borra el último elemento de ambas partes
		*********************************************************/

		 else if (! strcmp(input, "b\n") || ! strcmp(input, "B\n")) {
			borrar(textoBrai, texto, diacríticos, &NUMERAL, &MAYUS);
		}
		
		/*****************************************************************
		 * input == "W" crea un documento y guarda el texto braille en él
		******************************************************************/

		 else if (! strcmp(input, "w\n") || ! strcmp(input, "W\n")) {
			guardar(input, textoBrai, texto);
		}

		/***********
		 * 'SALIR'
		************/
		 else if (! strcmp(input, "salir\n") || ! strcmp(input, "SALIR\n")) {
			free(texto);
			return 0;
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

		if ( ! strcmp(input, "jl")) { // Signo de mayúscula
			MAYUS = true;
			NUMERAL = false;
			strcat(textoBrai, braille[40]);
			continue;
		} else if ( ! strcmp(input, "jkls")) { // Numeral
			NUMERAL = true;
			MAYUS = false; // Previene un error del usuario
			strcat(textoBrai, braille[60]);
			continue;
		}

		/***********************************
		 * SI ES UNA LETRA O NÚMERO BRAILLE
		************************************/

		añadir(
			input, textoBrai, texto, diacríticos,
            perk, braille, &NUMERAL, &MAYUS,
            alpha, nums);
	}
}