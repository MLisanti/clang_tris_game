/******************************************************************************
Autore: Massimo Lisanti
Data: 22/08/2022

Gioco del tris interattivo da console
*******************************************************************************/

#include <stdio.h>

#define VUOTO ' '
#define G1 'x'
#define G2 'o'

void cancella_tris(char griglia[3][3]);
void mostra_griglia(const char griglia[3][3]);
void input_dati(char segno_attuale, int *riga, int *col);
void inserisci_segno(char griglia[3][3], int r, int c, char segno);
char controlla_esito(const char griglia[3][3]);
int controlla_vincita_segno(const char griglia[3][3], char segno);
int griglia_da_completare(const char griglia[3][3]);
int mossa_valida(const char griglia[3][3], int r, int c);


void test_vincita();
void test_griglia_da_completare();




int main()
{
    char tris[3][3];
	
    char segno_attuale = G1;
    int riga, colonna;
    int fine_gioco = 0;
    int valido;
    char vincitore;
    
    /*
     * test_vincita();
    test_griglia_da_completare();
    * */

    cancella_tris(tris);
    mostra_griglia(tris);
    
    do {
		
        do {
			/* input di valori */
			input_dati(segno_attuale, &riga, &colonna);
			
			/*controlla se la mossa è valida */
			valido = mossa_valida(tris, riga, colonna);
			if(!valido) {
				printf("Attenzione!! hai fatto una mossa non valida...\n\n");
			}
		} while (!valido);
		
        inserisci_segno(tris, riga, colonna, segno_attuale);
        
        printf("\n");
        printf("\n");
        
        
        /* mostra la griglia*/
        mostra_griglia(tris);
        
        
        /* controlla se qualcuno ha vinto, se la partita è patta o se non si possono mettere più segni */
        fine_gioco = !griglia_da_completare(tris);
        vincitore = controlla_esito(tris);
        
        if(!fine_gioco && vincitore == VUOTO) {
			
			/* partita continua, cambia il giocatore */
			if(segno_attuale == G1)
				segno_attuale = G2;
			else
				segno_attuale = G1;
				
				
		} else {
			/* altrimenti, se la griglia è stata completata oppure un giocatore ha vinto - lo segnala*/
			if(vincitore != VUOTO)
				printf("Ha vinto il giocatore '%c'!!", vincitore);
			else
				printf("partita patta!");
		}

	} while(!fine_gioco && vincitore == VUOTO);
        
    /* fine gioco */
    
    return 0;
}

/*
 * Richiesta dei dati
 * Controlla che i dati inseriti siano corretti
 * 
 * segno_attuale: input - segno da inserire nella griglia
 * riga:	output - riga scelta dal giocatore
 * col:		output - colonna scelta dal giocatore
 * 
 * POST: riga e colonna sono due valori interi, compresi tra 0 e 2
 * */
void input_dati(char segno_attuale, int *riga, int *col) {
	int ris_input, errore_input;
	
	do {
            printf("Dove vuoi inserire il segno %c? ", segno_attuale);
            ris_input = scanf("%d%d", riga, col);
            
            errore_input = ris_input != 2 || *riga < 0 || *riga > 2 || *col < 0 || *col > 2;
            if(errore_input)
                printf("Controlla meglio i dati! Devono essere due valori compresi tra 0 e 2!\n\n");
                
     } while(errore_input);
}

/*
 * Segnala se la griglia ha delle celle vuote
 * 
 * griglia:		input - matrice che rappresenta la griglia
 * */
int griglia_da_completare(const char griglia[3][3]) {
	for(int r=0; r<3; r++)
        for(int c=0; c<3; c++)
            if(griglia[r][c] == VUOTO) {
				return 1;
			}
	return 0;
}

/*
 * Cancella le celle di una griglia
 * 
 * griglia: 	output - matrice che rappresenta la griglia
 * */
void cancella_tris(char griglia[3][3]) {
    for(int r=0; r<3; r++)
        for(int c=0; c<3; c++)
            griglia[r][c] = VUOTO;
}

/*
 * Mostra la griglia a schermo
 * 
 * griglia:		input - matrice che rappresenta la griglia
 * */
void mostra_griglia(const char griglia[3][3]) {
    for(int r=0; r<3; r++) {
        
        for(int c=0; c<3; c++){
            printf("%2c%c%c |", ' ', griglia[r][c], ' ' );
        }
        printf("\n");    
        if(r < 2)
            printf("--------------------\n");
    }
        
}

/*
* Inserisce un segno tra 'x', 'o' nella griglia, alle posizioni R e C
* 
* PRE: 
* valori r, c sono interi compresi tra 0 e 2
* segno è un valore tra 'x', 'o'
* 
* griglia:		output - matrice che rappresenta la griglia
* r, c:			input - le coordinate scelte
* segno:		input - valore da porre nella griglia
*/
void inserisci_segno(char griglia[3][3], int r, int c, char segno) {
    griglia[r][c] = segno;
}

/*
 * Controlla che il segno dato in input abbia vinto la partita
 * PRE: segno_test è uno tra 'x' oppure 'o'
 * POST: torna un valore bool
 * 
 * griglia:		input - matrice che rappresenta la griglia
 * segno_test:	input - segno da verificare
 * */
int controlla_vincita_segno(const char griglia[3][3], char segno_test) {
	char vincitore = VUOTO;
	int r, c;
	/*righe*/
	for(r=0; r<3; r++) {
		if(griglia[r][0] == segno_test && griglia[r][1] == segno_test && griglia[r][2] == segno_test)
			vincitore = segno_test;
	}
		
	/*colonne*/
	if(vincitore == VUOTO) {
		for(c=0; c<3; c++)
			if(griglia[0][c] == segno_test && griglia[1][c] == segno_test && griglia[2][c] == segno_test)
				vincitore = segno_test;
	}
		
	/*diagonali*/
	if(vincitore == VUOTO) {
		if(griglia[0][0] == segno_test && griglia[1][1] == segno_test && griglia[2][2] == segno_test)
			vincitore = segno_test;
	}
	
	if(vincitore == VUOTO) {
		if(griglia[0][2] == segno_test && griglia[1][1] == segno_test && griglia[2][0] == segno_test)
			vincitore = segno_test;
	}
		
	return vincitore == segno_test;
}

/*
* Controlla l'esito di una partita, data la griglia
* PRE : la griglia dev'essere riempita totalmente
* POST: torna un valore 'x', 'o', oppure ' ' (patta)
* 
* griglia:		input - matrice che rappresenta la griglia
*/
char controlla_esito(const char griglia[3][3]) {
	char vincitore = VUOTO;
	
	if(controlla_vincita_segno(griglia, G1))
		vincitore = G1;
	else if(controlla_vincita_segno(griglia, G2))
		vincitore = G2;
	
	return vincitore;
}

/*
 * Controlla se la mossa che si sta per fare è valida
 * PRE: valori r e c compresi tra 0 e 2
 * POST: un valore VERO o FALSO
 * */
int mossa_valida(const char griglia[3][3], int r, int c) {
	return griglia[r][c] == VUOTO;
}

/***************
 * TEST
*****************/

void test_griglia_da_completare() {
	char tris[3][3] = { 
		{'o','x','x'}, 
		{'x','o','o'}, 
		{'o',VUOTO,'x'} 
	};
	
	mostra_griglia(tris);
	/*cancella_tris(tris);*/
	
	printf("completare? %d\n", griglia_da_completare(tris));
}

void test_vincita() {
	char tris[3][3] = { 
		{'o','x','x'}, 
		{'x','o','o'}, 
		{'o','x','x'} 
	};
	
     mostra_griglia(tris);
     printf("Ha vinto %c? %d \n", G1, controlla_vincita_segno(tris, G1));
     printf("Ha vinto %c? %d \n\n", G2, controlla_vincita_segno(tris, G2));
     
     printf("La funzione torna il valore: '%c'\n", controlla_esito(tris));
     printf("\n\n");
     
     char tris2[3][3] = { 
		{'o','x','x'}, 
		{'x','o','o'}, 
		{'o','x','o'} 
	};
	
     mostra_griglia(tris2);
     printf("La funzione torna il valore: '%c'\n", controlla_esito(tris2));
     printf("\n\n");
     
     char tris3[3][3] = { 
		{'o','x','x'}, 
		{'x','x','o'}, 
		{'x','x','o'} 
	};
	
     mostra_griglia(tris3);
     printf("La funzione torna il valore: '%c'\n", controlla_esito(tris3));
     
     printf("\n\n");
}
