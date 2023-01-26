#include <stdio.h>
#include <stdlib.h>

//---------------------------strutture-------------------------------
typedef struct nodo {
	int n;
	struct nodo* next;
	struct nodo* prev;
}NODO;

typedef NODO* puntanodo;
//-------------------------------------------------------------------

//---------------------------new lista-------------------------------
puntanodo newlista (){
	puntanodo nuovo=calloc (1,sizeof(NODO));
	nuovo->next=NULL;
	nuovo->prev=NULL;
	return nuovo;
}
//-------------------------------------------------------------------

//---------------------------inserimento-----------------------------
void inserimento (puntanodo testa,int n){
	puntanodo nuovo=calloc (1,sizeof(NODO));
	while(testa->next!=NULL){
		testa=testa->next;
	}
	testa->next=nuovo;
	nuovo->prev=testa;
	nuovo->n=n;
}
//-------------------------------------------------------------------

//--------------------------stampalista------------------------------
void stampalista (puntanodo testa){
	testa=testa->next;
	printf("---------------------------------\n");
	for(int i=0;testa!=NULL;i++){
		printf("[%d] ",testa->n);
		testa=testa->next;
	}
	printf("\n---------------------------------\n");
}
//-------------------------------------------------------------------

//--------------------------stampa inversa---------------------------
void stampainversa (puntanodo testa){
	while(testa->next!=NULL){
		testa=testa->next;
	}
	printf("---------------------------------\n");
	while(testa->prev!=NULL){
		printf("[%d] ",testa->n);
		testa=testa->prev;
	}
	printf("\n---------------------------------\n");
}
//-------------------------------------------------------------------



//----------------------------inserimento-----------------------------
void aggiungi_in_testa(NODO* pld, int x) {

	NODO* li = (NODO*)malloc(sizeof(NODO));
	li->prev = NULL;   // lo aggiungo in testa
	li->next = (*pld);
	li->info = x;
	if( (*pld) != NULL )  {   // c'era gia' un elemento
		 (*pld)->prev = li;   // il suo prev deve puntare al nuovo elemento
    }
    (*pld) = li;
}
//-------------------------------------------------------------------



//----------------------------rimozione-----------------------------
void rimuovi(NODO* pld, int x) {

    NODO* li = (*pld);
    while( li != NULL ) {
    	if( li->info == x) {          // l'ho trovato e lo devo rimuovere
             if( li->prev == NULL) {  // sto rimuovendo il primo elemento
                  (*pld) = li->next;  // mi salto
             } else {                 // c'e' un elemento che mi precede
                  li->prev->next = li->next;
             }
             if( li->next != NULL) {  // c'e' almeno un elemento che segue
                  li->next->prev = li->prev;
             }
             free(li);
             break;     // cancello solo la prima occorrenza e poi esco dal while
    	} 
        li = li->next;
    }
}
//-------------------------------------------------------------------



//-------------------------main--------------------------------------
int main(int argc, char **argv)
{
	puntanodo head=newlista();
	for(int j=0;j<5;j++){
		inserimento (head,j);
		stampalista (head);
	}
	stampainversa (head);
	printf("\n\n\n");
	return 0;
}
//-------------------------------------------------------------------