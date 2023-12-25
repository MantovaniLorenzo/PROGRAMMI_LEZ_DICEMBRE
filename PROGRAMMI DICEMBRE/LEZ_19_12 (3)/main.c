// PROGRAMMA CHE DATA UNA RUBRICA DOBBIAMO POPOLARE LA RUBRICA, SE IL CLIENTE � GIA ALL'INTERNO DELLA RUBRICA
// dovremmo ipoteticamente aggiornare l'et�, SE NON C'� IL CLIENTE AGGIUNGERLO ALLA RUBRICA

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 31

typedef struct {
	char nome[M];
	char id[2];   // se c'� un carattere conviene leggerlo come stringa di 2 elementi 
	int eta;

}cliente;


int main(void) {
	FILE* fp;
	cliente* v;
	int dim, i, flag = 0;
	cliente elem;  // singolo elemento di tipo cliente elem � il nome della variabile
	char nome[M];

	printf("Inserire dimensione rubrica:\n"); // dimensione del vettore
	scanf("%d", &dim);

	v = (cliente*)malloc(dim * sizeof(cliente)); // sizeof(Cliente) 36 byte 31+1+4
	if (v == NULL) {
		printf("ERRORE di allocazione\n");
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
	while (i < dim && fscanf(fp, "%s%s%d%*s", v[i].nome, v[i].id, &v[i].eta) != EOF) { // leggo per ogni tipo della mia struct, & � davanti ad id e eta perch� non sono stringhe
	// SE nel file di input sono presenti anche pi� campi che non sono rilevanti al fine del programma � possibile saltarli con  !! %* e poi il formato salter� quello FUNZIONA PER QUALSIASI FORMATO DA SALTARE
		i++;
	}
	dim = i;
	fclose(fp);

	 // l' utente inserisce un nuovo nominativo CONDIZIONI COME QUELLE SOPRA
	// SE � PRESENTE nella rubrica leggo se non c'� aggiungo

	printf("Inserire il nome di un utente:\n");
	while (scanf("%s", nome) != EOF) {
		flag = 0;   // quando ricomincia il ciclo devo riaggiornare il flag quindi lo rimetto a 0 perch� senn� il ciclo looppa perch� � sempre a 1
		for (i = 0; i < dim && flag == 0; i++) {   // se questo non � vero non � detto che l'elemento non c'� ma solo che non � in posizione i-esima
			if (strcmp(v[i].nome, nome) == 0) {
				flag = 1; // se il nominativo c'� aggiorno il flag 
				printf("Inserire l'eta' aggiornata: \n");
				scanf("%d", &v[i].eta);
			}
		}                  // quindi con flag = 0 vuol dire che l'elemento non � presente in tutto il vettore
		if (flag == 0) {  // essendoci un && nella condizione mi esce quando una delle due � falsa quindi devo capire in quale caso mi trovo
			v = (cliente*)realloc(v, (dim + 1) * sizeof(cliente)); // devo copiare l� ultimo elemento perch� io ho gia riempito il vettore fino a dim-1 per� c'� il tappo quindi devo allungarlo
			strcpy(v[dim].nome, nome); // avendolo allungato ora posso farlo
			printf("Inserire anche l'id del nuovo cliente e l'eta':\n");
			scanf("%s%d", v[dim].id, &v[dim].eta);
			dim++;
		}

		printf("Inserire il nome di un utente:\n");

	}


	// stampa elementi 
	for (i = 0; i < dim; i++) {
		printf("%s %s %d\n", v[i].nome, v[i].id, v[i].eta);
	}

	return 0;
}