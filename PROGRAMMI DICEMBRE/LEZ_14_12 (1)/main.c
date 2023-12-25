#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//PROGRAMMA (base del programma lez_12_12_2023) CON CUI L'UTENTE IN MODO ITERATIVO PUò SCEGLIERE VARI VALORI CHE VERRANNO TOLTI E POI VENGONO ANALIZZATI SOLO I RESTATI (leggiamo da file per allenare questo concetto)

// !!!!!  PROGRAMMA SIMIL ULTIMO DEL PARZIALE !!!!!!


int main(void) {

	int* v, i, * v_flag, dim, num;
	FILE* fp;           // usiamo file perchè abbiamo detto che leggiamo i dati da FILE per allenarli
	char nome[21];     // stringa in cui andrò a mettere il nome del file per aprirlo, dimensione del file massimo 20 caratteri, l'uno in più serve per il tappo 

	printf("Definisci dimensione vettore: \n");
	scanf("%d", &dim);

	v = (int*)malloc(dim * sizeof(int));

	if (v == NULL) {
		printf("ERRORE di allocazione.\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserire nome FILE INPUT:");
	scanf_s("%s", nome, 20);  // poichè ho usato la scanf_s devo ANCHE dare la dimensione massima.

	fp = fopen(nome, "r");  // aperto il file in modalità lettura (copio, leggo e basta)
	if (fp == NULL) { // come per la malloc proteggo e controllo se il file è stato aperto correttamente, cioè se è stato localizzato, cioè se l'utente magari ha sbagliato il nome del file. 
		printf("ERRORE di apertura.\n");
		exit(EXIT_FAILURE);
	}


	// copiamo il contenuto da file perchè l'accesso dei file è sequenziale e quindi complesso, quindi li copio in un altro tipo di struttura.
	// stessa cosa su OUTPUT se devo memorizzare diversi risultati li copio in un file che quando viene salvato ricorda. 


	// i FILE li uso quando ho tante informazioni, quindi dovrò fare tante letture con altrettante chiamate di funzioni e quindi userò un ciclo, così riuscirò a leggere tutto il file in modo sequenziale.



	// FINO A QUA NON HO ANCORA FATTO NULLA DI QUELLO CHE è L'OBIETTIVO DELL'ESERICIZIO STO SOLO FACENDO TUTTO QUELLO CHE MI SERVE PRIMA DELLE VARIE OPERAZIONI

	// Stiamo solo leggendo il FILE

	// IMPORTANTE QUESTO APPORCCIO DI LETTURA FILE SI USA PER QUALUNQUE TIPO DI VETTORE ABBIAMO, CHE SIA STRUTTURA, STRINGHE etc.
	i = 0;
	while (i < dim && fscanf(fp, "%d", &v[i]) != EOF) {  // devo riempire un vettore di interni, è come la scanf ma ha il parametro del FILE da cui prenderà i dati, prima però controllo che ci sia spazio nel vettore, cosi se il FILE è comunque pioù lungo il ciclo termina comunque (LO METTO PRIMA PERCHè L'ORDINE DELL & è IMPORTANTE, L' & RISULTA FALSO APPENA UNA DELLE DUE è FALSA COSI NEL CASO SFORI NON PROVA A METTERE L'ULTIMA ROBA IN MEMORIA NON ALLOCATA)
	// ricordiamo che la fscanf aggiorna ad ogni chiamata il puntatore a FILE, cioè fp, cioè una volta che avrà letto il primo elemento e lo avrà messo all' 0-esima posizione, aggiorna fp cosi punta direttamente all'elemento dopo. ( nel nostro caso sarà uno spazio/un a capo perchè è un file di testo, ma la fscanf li salta di base perchè abbiamo messo %d che non sono INTERI quindi li salta)
		i++;
	}
	fclose(fp);


	// ora in qualunque modo io abbia allocato non è importante, ora opero su un vettore.
	// ORA STO INIZIANDO A FARE LE OPERAZIONI LEGATE ALL'OBIETTIVO DEL PROGRAMMA.

	// USIAMO UN VETTORE DI APPOGGIO DI FLAG CHE QUANDO INCONTRO ELEMENTI CHE VOGLIO ELIMINARE AGGIORNA IL FLAG COSI CON UN CONTROLLO QUESTI ELMENTI NON VERRANNO CONSIDERATI. 


	v_flag = (int*)calloc(dim, sizeof(int)); // USO LA CALLOC CHE è UNA FUNZIONE CHE ALLOCA IL VETTORE(come la malloc) MA INIZIALIZZA DIRETTAMENTE TUTTI GLI ELEMENTI A 0
	if (v_flag == NULL) {
		printf("ERRORE di allocazione.\n");
		exit(EXIT_FAILURE);
	}

	// CICLO CHE PERMETTE ALL'UTENTE DI SCEGLIERE DIVERSI VALORI DA NON CONSIDERARE.

	printf("Inserire il valore da cancellare dal vettore:\n");

	while (scanf("%d", &num) != EOF) {
		for (int i = 0; i < dim; i++) {
			if (v[i] == num) {
				v_flag[i] = 1;
				printf("Inserire il valore da cancellare dal vettore:\n");
			}
		}
	}

	// FACCIAMO ESEMPIO IN CUI DEVO CALCOLARE IL MASSIMO TRA GLI ELEMENTI RIMASTI (toltI quellI scelto da utente).

	int max = INT_MIN;
	for (i = 0; i < dim; i++) {
		if (v_flag[i] == 0) // se il vettore dei flag ha 0 allora il numero è buono, se avesse 1 sarebbe l'elemento oscurato, cioè che l'elemento in posizine i-esima corrisponde a quello scelto dall'utente da eliminare
			if (v[i] > max)
				max = v[i];
	}

	printf("Il massimo e': %d\n", max);
	printf("Gli elementi del vettore sono:\n");
	for (i = 0; i < dim; i++) {
		if (v_flag[i] == 0)
			printf("%d\n", v[i]);
	}

	return 0;
}