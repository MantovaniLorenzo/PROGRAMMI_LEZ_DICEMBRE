#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define M 31

// PROGRAMMA CHE UTILIZZA VETTORI DI STRINGHE.
//IL VETTORE DI STRINGHE VENGONO VISTI COME MATRICI DURANTE L'ALLOCAZIONE 
// NELLE OPERAZIONI PERò VIENE USATO COME UN SEMPLICE VETTORE CHE VIENE USATO CON LE FUNZIONI DI LIBRERIA.

int main(void) {

	//allocazione del vettore

	char** v, i, dim, j;   // IL DOPPIO PUNTATORE SONO PER RIGHE E COLONNE, UNO SARà PER GLI ELEMENTI E L'ALTRO PER STRINGHE 
	FILE* fp;
	char nome[21];
	char str[M];
	printf("Definisci dimensione vettore: \n");
	scanf("%d", &dim);
	
	// per allocare dinamicamente una matrice si utilizza questa modalità (ce ne sono altre ma devi imparare questa)
	v = (char**)malloc(dim * sizeof(char)); // dimensione riga cioè numero elementi (sarebbe un vettore di puntatori)
	
	// per ciascun elemento riga punta a un vettore di caratteri
	
	for (i = 0; i < dim; i++) {
		v[i] = (char*)malloc(M * sizeof(char));  // M, numero colonne è il numero massimo di caratteri cioè quanto sono lunghe le stringhe. (possiamo sia chiederlo all'utente che prestabilirlo).
	}


	// apertura file 
	printf("Inserire nome FILE INPUT:");
	scanf_s("%s", nome, 20);
	fp = fopen(nome, "r");
	if (fp == NULL) {
		printf("ERRORE di apertura.\n");
		exit(EXIT_FAILURE);
	}

	//lettura file 
	i = 0;
	while (i < dim && fscanf(fp, "%s", v[i]) != EOF) {  // la prima condizione è perchè se sono presenti più elementi (nel file) che la dim del vettore l'EOF arriverebbe dopo cosi siamo sicuri che ne legge il numero esatto // non ci vuole l' & perchè ciascun elemento i-esimo è una stringa e quindi un vettore e quindi un indirizzo
		i++;
	}
	dim = i;
	fclose(fp);

	// inserimento del valore da cancellare + cancellazione di esso (no ignoramento tramite vettore di flag)

	printf("Inserire la stringa da cancellare dal vettore:\n");
	while (scanf("%s", str) != EOF) {
		for (i = 0; i < dim; i++) {
			if (strcmp(v[i], str) == 0) { // == 0 perchè se il confronto tra le stringhe sono uguali torna 0
				for (j = i; j < dim - 1; j++) {
					strcpy(v[j], v[j+1]);     // copio la stringa nella posizione prima tramite la strcpy
				}
				dim--;
				if (dim != 0) {
					v = realloc(v, dim * sizeof(char));
				}
			} i--;  // perchè nel caso particolare in cui ci siano due elementi uguali da cancellare che sono CONTIGUI tiro indietro gli indici cosi riparto dalla stessa posizione sostituita e non viene ignorato l'elemento 
		}
		printf("Inserire la stringa da cancellare dal vettore:\n");
	}

	// stampa elementi 

		printf("Gli elementi del vettore sono:\n");
		for (i = 0; i < dim; i++) {
			printf("%s\n", v[i]);
		}


	return 0;
}