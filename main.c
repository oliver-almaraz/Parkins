/*********************************************
/ DESCRIPCIÓN:
/  	Este programa se ejecuta desde la terminal,
/ recibe un input de 6 teclas simultáneas que
/ interpreta como una entrada de signo braille
/ en una máquina Perkins (ver 'signos.c').
/ En la parte superior de la terminal muestra los
/ signos braille y en la inferior su equivalente
/ en texto español. Permite guardar los signos
/ braille escritos en un documento de texto.
/ También se pueden borrar los últimos signos de
/ ambas partes (texto y braille), con ciertas
/ consideraciones especiales.
/ 	De momento no funciona en Windows debido a
/ la codificación de las terminales, habrá que
/ hacer una interfaz gráfica (GTK3?).
/ Asegúrate de que tu editor esté configurado
/ con codificación UTF-8.
/ 
/ Compilar en GCC:
/ >$ gcc ./modules/signos ./modules/borrar.c ./modules/guardar.c ./modules/añadir.c main.c
/ 
/ Oliver Almaraz
/ oliver.almaraz@gmail.com
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "./modules/modules.h"

int main() {

	setlocale(LC_ALL, "");

    char input[8]; // 6 puntos + \n y el pilón
	char *textoBrai = (char*)calloc(3500, sizeof(char)); // Tamaño = 1 byte por char, cada letra braille contiene 3 bytes.
	char *texto = (char*)calloc(1000, sizeof(char));
	bool MAYUS = false;
	bool NUMERAL = false;

	while (true) {
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
			borrar(textoBrai, texto, &NUMERAL, &MAYUS);
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
			free(textoBrai);
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
			strcat(textoBrai, "⠨");
			continue;
		} else if ( ! strcmp(input, "jkls")) { // Numeral
			NUMERAL = true;
			MAYUS = false; // Previene un error del usuario
			strcat(textoBrai, "⠼");
			continue;
		}

		/***********************************
		 * SI ES UNA LETRA O NÚMERO BRAILLE
		************************************/

		añadir(
			input, textoBrai, texto,
            &NUMERAL, &MAYUS
        );
	}
}