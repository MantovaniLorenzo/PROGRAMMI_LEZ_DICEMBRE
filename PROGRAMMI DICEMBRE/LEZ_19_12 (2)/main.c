/*Questo programma è come l'altro ma usa le stringhe al posto della struttura. Una volta elimate le stringhe
contenti le parole decise dall'utente da eliminare viene calcolata la strina massima più avanti in ordine alafabitoco


nell esercizio ci sono due soluzioni: una con allocazione statica del vettore, una con allocazione dinamica.
Per la soluzione con allocazione dinamica si fornisce anche la parte di codice per riallocare il vettore 
riducendo lo spazio di memoria allocato ogni volta che la strinfa cercata viene cancellata dal vettore 
(quest'ultima parte nnon è obbligatoria basta quindi eseguire dim-- in modo da scorrere il vettore 
condizionatamente fino all'ultima elemento buono)*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// SOLUZIONE CON ALLOCAZIONE STATICA 

#define M 31 // dimensione che ci indica quanto è grande AL MASSSIMO la parola/stringa
#define N 10 // dimensione che ci fa capire che gestiremo AL MASSIMO, N parole/stringhe 

// quindi abbiamo un vettore di N stringhe dove ciascuna di queste N stringhe contiene al masssimo M-1 caratteri (ultimo tappo)



int main(void) {
	char v[N][M];
	int i, j, dim, flag = 0;
	FILE* fp;
	char nome[21];
	char str[M], max[M];

	printf("Inserire nome file input: \n");
	scanf("%s", nome);

	fp = fopen(nome, "r");
	if (fp == NULL) {
		printf("ERRORE di apertura del file.\n");
		exit(EXIT_FAILURE);
	}

	i = 0;
	dim = N;
	while (i < dim && fscanf(fp, "%s", v[i]) != EOF) { // non ci vuole & perchè stringa
		i++;
	}
	dim = i; // nel caso in cui le stringhe nel file siano meno della dimensione N allocata per il vettore
	fclose(fp);


	printf("Inserire la stringa da cancellare dal vettore:\n");
	while (scanf("%s", str) != EOF && flag == 0) {
		for (i = 0; i < dim; i++)
			if (strcmp(v[i], str) == 0) {
				//shift a sx 
				for (j = i; j < dim - 1; j++) {
					strcpy(v[j], v[j + 1]);
				}
				dim--;
				if (dim == 0) {
					printf("Dimensione vettore a 0\n");
					flag = 1;
				}
				i--;
			}

		printf("Inserire il valore da cancellare dal vettore:\n");
	}
		strcpy(max, v[0]);
		for (i = 0; i < dim; i++) {
			if (strcmp(v[i], max) > 0)
				strcpy(max, v[i]);
		}

		printf("Il massimo e': %s\n", max);
		printf("Gli elementi del vettore sono:\n");
		for (i = 0; i < dim; i++) {
			printf("%s\n", v[i]);
		}

		return 0;

}

// SOLUZIONE CON ALLOCAZIONE DINAMICA 

/*
#define M 31

int main(void){

char** v;
int i, j, dim;
FILE *fp;
char nome[21];
char str[M];

printf("Inserire dimensione vettore: \n");
scanf("%d", &dim);

v = (char**)malloc(dim*sizeof(char*));
for(i = 0; i < dim; i++){
v[i] = (char*)malloc(M *sizeof(char));
}

printf("Inserire nome file input: \n);
scanf("%s", nome);

fp= fopen(nome, "r");
if(fp == NULL){
printf("Errore apertura file.\n");
exit(EXIT_FAILURE);
}

i= 0;
while(i < dim && scanf(fp, "%s", v[i]) != EOF){
i++;
}
dim = i;
fclose(fp);

printf("Inserire la stringa da cancellare dal vettore:\n");
	while (scanf("%s", str) != EOF) {
		for (i = 0; i < dim; i++)
			if (strcmp(v[i], str) == 0) {
				//shift a sx
				for (j = i; j < dim-1; j++) {
					strcpy(v[j], v[j + 1]);
				}
				free(v[dim-1]);  // libero l'ultimo elemento puntato cioè l'ultima stringa
				dim--;  // dim- 1 poicjè la dimensione è dim ma gli indici partono da 0 fino a dim-1 quindi l'ulitmo elemento è in pos indice dim-1 
				if (dim != 0) {
					v = (char**)realloc(v, dim * sizeof(char*));
					if(v == NULL){
					printf("ERRORE di allocazione);
					exit(EXIT_FAILURE);
					}
				}
				else 
				    printf("Dimensione vettore a 0\n);
				i--;
			}

		printf("Inserire il valore da cancellare dal vettore:\n");
	}
		strcpy(max, v[0]);
		for (i = 0; i < dim; i++) {
			if (strcmp(v[i], max) > 0)
				strcpy(max, v[i]);
		}

		printf("Il massimo e': %s\n", max);
		printf("Gli elementi del vettore sono:\n");
		for (i = 0; i < dim; i++) {
			printf("%s\n", v[i]);
		}

return 0;
}*/
