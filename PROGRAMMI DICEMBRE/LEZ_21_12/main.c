/* PROGRAMMA CHE RICERCA UNA SOTTOSEQUENZA (una sottomatrice) DI "n" ELEMENTI GENERICO IN UNA MATRICE E DIRE SE è CONTENUTA, STAMPA IL RISULTATO SU UN FILE 
possiamo considerarlo come una generalizzazione della ricerca di una sottosequenza in un vettore */

// IDEA 

// 1) devo scorrere tutta la matrice grande per guardare tutti i punti, 
// 2) analizzando ogni i-j esimo elemento della matrice devo trovare l'ancor point (punto di inizio, il primo valore della sottomatrice), se non è verificato non ha senso cercare la sottomatrice da quel punto
// 3) se è verificata la condizione 2 è possibile che siano presenti anche tutti gli altri valori della sottomatrice, quindi con altri 2 cicli for interni scorro la matrice grande per K, L (dimensioni della sottomatrice)
// AVRò quindi due coppie di cicli for la prima è per scorrere la matrice grande e trovare l'ancor point, la seconda coppia è una volta trovato l'ancor point scorro K x L per scorrere l'area che potrebbe essere corrispondente alla sottomatrice che sto cercando

// una soluzione per verificare che coincidono è, tramite un contatore, verificare quanti punti della sottomatricd coincidono con la matrice grande, se questi punti sono K x L allora vuol dire che la matrice è contenuta


// LEGGIAMO DA FILE 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 6 // numero righe 
#define M 8 // numero colonne
#define K 2// numero righe 
#define L 3 // numero colonne

int main(void) {

	int i= 0, j= 0, r, c, m[N][M], sm[K][L], count = 0, dimr, flag =0;
	FILE* fp;
	char nome[21];  // stringa per chiedere nome da File

	printf("Inserire nome del file matrice:\n");
	scanf("%s", nome);

	if ((fp = fopen(nome, "r")) == NULL) {   // apertura + controllo in una solo
		printf("ERRORE di apertura del file matrice.\n");
		exit(EXIT_FAILURE);
	}

    // LEGGIAMO MATRICE

	for (i = 0; i < N && feof(fp) != EOF; i++)  // funzione feof testa se siamo arrivati all' EOF
		for (j = 0; j < M; j++) 
			fscanf(fp, "%d", &m[i][j]); // leggo ogni intero e lo metto nella posizione i-j della matrice grande, farò questa operazione I*J VOLTE a meno che non ci sia un EOF prima

      dimr = i; // nel caso ci sia un EOF prima e quindi meno righe cosi aggiorno i che sarà la dimensione delle righe effettive
	  fclose(fp);

	  // ORA CONSIDERIAMO SOTTOMATRICE 

	  printf("Inserire nome del file della SOTTO-MATRICE:\n");
	  scanf("%s", nome);

	  if ((fp = fopen(nome, "r")) == NULL) {   // apertura + controllo in una solo
		  printf("ERRORE di apertura del file sotto-matrice.\n");
		  exit(EXIT_FAILURE);
	  }


	  for (i = 0; i < K && feof(fp) != EOF; i++)  // funzione feof testa se siamo arrivati all' EOF
		  for (j = 0; j < L; j++)
			 fscanf(fp, "%d", &sm[i][j]); // leggo ogni intero e lo metto nella posizione i-j della matrice grande, farò questa operazione I*J VOLTE a meno che non ci sia un EOF prima
	 
	  fclose(fp);
	  
	  // SCRIVIAMO I FILE SU UN FOGLIO DI OUTPUT

	  printf("Inserire nome file di Output:\n");
	  scanf("%s", nome);

	  if ((fp = fopen(nome, "w")) == NULL) {   // il file di output viene creato automaticamente, se esiste già viene sovrascritto // lo creerebbe anche se fosse vuoto perciò mettiamo il flag per far capire se è vuoto perchè deve essere vuoto o solo perchè non ha trovato
		  printf("ERRORE di apertura file output\n");
		  exit(EXIT_FAILURE);
	  }

	  // fino ad ora era la preparazione cioè apertura file e scrittura matrici tramite file ora iniziano le operazioni per la ricerca


	  // RICERCA SOTTOMATRICE ALL'INTERNO DELLA MATRICE  
	  // SPOSTAMENTO DALLA MATRICE GRANDE in una dimensione K x L 

	  for (i = 0; i < dimr; i++) {
		  for (j = 0; j < M; j++) {
			  if (m[i][j] == sm[0][0]) { // devo controllare se il punto i j corrisponde al primo punto della sottomatrice cioè l'ancor point sm[0][0]  è l'ancor point
				  count = 0;
				  for (r = 0; r < K && i + r < dimr; r++)    // i +r vuol dire che mi sposto da i fino a r e deve essere minore di dimr, cioè non posso uscire dalla dimensione della riga !!!  // indici per scorrere la sottomatrice K righe sottomatrice L colonne sottomatrice
					  for (c = 0; c < L && j + c < M; c++)
						  if (m[i+r][j+c] == sm[r][c])   // i è il punto di partenza r è lo spostamento, stessa cosa per le colonne// controllo se gli elementi coincidono
							  count++;
				  if (count == K * L) {   // se il count è uguale a k*l vuol dire che tutti gli elementi dall' ancor pointsono dentro la matrice quind

					  fprintf(fp, "Sottomatrice contenuta a partire dalle posizioni %d %d\n", i, j);
					  flag = 1;
				  }
			  }
		  }
	  }

	  if (flag == 0)
		  printf("La sottomatrice non e' contenuta nella matrice.\n");


	return 0;
}