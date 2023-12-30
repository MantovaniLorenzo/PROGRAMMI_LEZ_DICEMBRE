

//QUESTO PROGRAMMA RIEMPE UN VETTORE DI STRUTTURE LEGGENDO I DATI, NOME MEDIA STUDENTE, DA UN FILE DI INPUNT
// POI IN MODO CICLICO SI DEVONO LEGGERE DA TASTIERA DEI NOMINATIVI CHE POI SI DEVONO CERCARE NEL VETTORE 
// E SE TROVATI VANNO CANCELLATI DAL VETTORE INSIEME A TUTTA LA STRUTTURA DI CUI COSTITUISCE CAMPO NOME
// ALLA FINE VIENE CALCOLATO L'ELEMENTO DEL VETTORE CON LA MEDIA PIù ALTA.

// LA SOLUZIONE CON ALLOCAZIONE DINAMNICA FORNISCE ANCHE LA PARTE DI CODICE PER RIALLOCARE IL VETTORE RIDUCENDO
// LO SPAZIO DI MEMORIA ALLOCATO OGNI VOLTA CHE L'ELEMENTO STRUTTURA CERCATO VIENE CANCELLATO DAL VETTORE

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#define M 31
	
	// definisco un nuovo tipo 
	typedef struct stud {
		char nome[M];
		float media;

	} /*studente*/;  // utilizzando typedef ora al posto di scrivere ogni volta struct stud posso scrivere studente
	
	
	int main(void) {
	
		int i, j, dim;
		struct stud* v;
		FILE* fp;
		char nome[21];
		char str[M];
		float max = FLT_MIN;

		printf("Inserire la dimensione del vettore:\n");
		scanf("%d", &dim);

		// allocazione vettore di struttura, come quella per interi 

		v = (struct stud*)malloc(dim * sizeof(struct stud));
		if (v == NULL) {
			printf("ERRORE DI ALLOCAZIONE");
			exit(EXIT_FAILURE);
		}

		// apertura FILE
		printf("Inserire nome file input:\n");
		scanf("%s", nome);

		fp = fopen(nome, "r");
		if (fp == NULL) {
			printf("ERRORE apertura file.\n");
			exit(EXIT_FAILURE);
		}

		//lettura da file 
		i = 0;
			while (i < dim && fscanf(fp, "%s%f", v[i].nome, &v[i].media) != EOF) {  // essendo una stringa il campo nome non ha bisogno dell & mentre il campo media essendo un float ne ha bisogno 
				i++;
			}
		dim = i;
		fclose(fp);


		// QUANDO SI PROCESSANO LE STRUTTURE (A MENO DI DETERMINATE OPERAZIONI) SI PROCESSANO I CAMPI IN MANIERA SEPARATA
		printf("Inserisci il nominativo da cancellare dal vettore:\n");

		while (scanf("%s", str) != EOF) { // IN QUESTO CASO ELIMINIAMO L'ELEMENTO STRUTTA IL CUI NOME COINCIDE CON IL CONTENUTO DI UNA STRINGA CHE PASSIAMO DA INPUT
			for (i = 0; i < dim; i++) 
				if (strcmp(v[i].nome, str) == 0) {
					//shift delle posizione CON STRUTTURE SI PUò SHIFTARE TUTTA LA STRUTTURA E NON SUI SINGOLI CAMPI
					for (j = i; j < dim - 1; j++) {
						v[j] = v[j+ 1];
					}
					dim--;
					if (dim != 0) {
						v = (int*)realloc(v, dim * sizeof(int));
						if (v == NULL) {
							printf("ERRORE di allocazione.\n");
							exit(EXIT_FAILURE);
						}
					}
					else
						printf("Dimensione vettore a 0\n");
					i--; // caso particolare in cui due elementi uguali da eliminare sono contigui
				}
				printf("Inserire il nominativo da cancellare dal vettore: \n");
				getchar();
			}

			for (i = 0; i < dim; i++) {
				if (v[i].media > max)
					max = v[i].media;
			}
			printf("Il massimo e': %.2f.\n", max);
			printf("Gli elementi del vettore sono: \n");
			for (i = 0; i < dim; i++) {
				printf("%s %.2f\n", v[i].nome, v[i].media);
			}
			return 0;
}
