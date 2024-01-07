//	PROGRAMMA CON LA STESSA FUNZIONALITà DI QUELLO VECCHIO MA IN QUESTO CASO ELIMINO PROPRIO GLI ELEMENTI PRESENTI NEL VETTORE 
// NEL PROGRAMMA DEFINITO PRECEDENTEMENTE INVECE LI IGNORAVO ATTRAVERSO IL VETTORE DI FLAG

// IL CONCETTO DELLA SOLUZIONE SI BASA SUL SOVRASCRIVERE I VALORI NON ACCETTATI CON QUELLI SUCCESSIVI ACCETTATI.

// DA FINIRE |_|_|_|_|_|_|_|_|_|_| PROVA CON REGISTRAZIONE 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {

	//allocazione del vettore

	int* v, i, dim, j, num;
	FILE* fp;          
	char nome[21];     
	printf("Definisci dimensione vettore: \n");
	scanf("%d", &dim);
	v = (int*)malloc(dim * sizeof(int));
	if (v == NULL) {
		printf("ERRORE di allocazione.\n");
		exit(EXIT_FAILURE);
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
	while (i < dim && fscanf(fp, "%d", &v[i]) != EOF) {  // la prima condizione è perchè se sono presenti più elementi (nel file) che la dim del vettore l'EOF arriverebbe dopo cosi siamo sicuri che ne legge il numero esatto
		i++;
	}
	dim = i;
	fclose(fp);

	// inserimento del valore da cancellare + cancellazione di esso (no ignoramento tramite vettore di flag)

	printf("Inserire il valore da cancellare dal vettore:\n");
	while (scanf("%d", &num) != EOF) {
		for ( i = 0; i < dim; i++) 
			if (v[i] == num) {
				for (j = i; j < dim - 1; j++) {
					v[j] = v[j + 1];
				}
				dim--;
				if (dim != 0) {
					v = realloc(v, dim * sizeof(int));
				}
			} i--;
		
		printf("Inserire il valore da cancellare dal vettore:\n");
	}

	// ricerca del massimo tra i valori rimanenti
	int max = INT_MIN;
	for (i = 0; i < dim; i++) {
			if (v[i] > max)
				max = v[i];
	}
	if (max = INT_MIN) {
		printf("Tutti i valori del vettore sono stati cancellati quindi non e' stato possibile trovare un massimo.\n");
	}
	else { printf("Il massimo e': %d\n", max);
	printf("Gli elementi del vettore sono:\n");
	for (i = 0; i < dim; i++) {
		printf("%d\n", v[i]);
	}
	}

	
	return 0;
}
