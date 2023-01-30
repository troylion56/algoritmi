#include <stdio.h>
#include <stdlib.h>
/*esame 05-07-2022*/ 			//funziona

/*Discuti la complessità computazionale delle seguenti procedure nel caso peggiore fornendo O‐grande,
Omega e Theta in funzione del numero n di elementi dell’albero.
FUNZIONE(T)  T è un albero binario di interi 
L.head = NULL  L è una nuova lista (vuota) di interi 
FUNZ_RIC(T.root,L)
return L
FUNZ_RIC(v,L)
if( v==NULL ) return -1
if( ALTEZZA_SOTTOALBERO(v)%2 == 0 ) se l’altezza del sottalbero è pari 
AGGIUNGI_IN_TESTA(L,v.info)
FUNZ_RIC(v.left,L)
FUNZ_RIC(v.right,L)
ALTEZZA_SOTTALBERO(v)
if( v == NULL ) return -1
l = ALTEZZA_SOTTALBERO(v.left)
r = ALTEZZA_SOTTALBERO(v.right)
if (l >= r)
return 1 + l
else
return 1 + r
Assumi che AGGIUNGI_IN_TESTA faccia un numero di operazioni costante. Descrivi una tipologia di albero
in cui si verifica il caso peggiore e una tipologia di albero in cui il caso peggiore non si verifica (per esempio
si verifica il caso migliore).

funzione non fa niente ha semplicemente la complessita di fun_ric
fun ric si visita tutto l'albero quidni ha una complessita di theta(n)
aggiungi in testa fa sempre un numero di operazioni costante quindi indipendentemente dall'albere fa theta(1) 
altezza_sottoalbero costa theta(n)

quindi la complessita totale è theta(n)

*/






/*int verifica(grafo* g)
che accetti in input un puntatore g ad un grafo non orientato rappresentato tramite oggetti e riferimenti.
La funzione restituisce 1 (cioè true) se il grafo contiene almeno una componente connessa il cui numero di
nodi è pari al numero di componenti connesse del grafo stesso, altrimenti la funzione restituisce 0 (cioè
false). Se il grafo è vuoto (cioè uguale a NULL) la funzione ritorna 1 (true).*/



typedef struct elem_lista_nodi elem_nodi;
typedef struct elem_lista_archi elem_archi;

/*oggetto nodo del grafo singolo lo capisco dal campo color*/
typedef struct nodo_struct {
	elem_nodi* pos; // posizione nodo nella lista del grafo 
	elem_archi* archi; // lista archi incidenti
	int color;
}nodo;

/*oggetto nodo del arco singolo */
typedef struct arco_struct {
	elem_archi* pos; // pos. arco lista grafo
	nodo* from;
	nodo* to;
	elem_archi* frompos; // pos. arco nodo from
	elem_archi* topos; // pos. arco nodo to
}arco;

/*lista di oggetti nodi che metti nel grafo*/
typedef struct elem_lista_nodi {
	struct elem_lista_nodi* prev;
	struct elem_lista_nodi* next;
	nodo* info;
}elem_nodi; // elemento di una lista di nodi

/*lista di oggetti archi che metti nel grafo*/
typedef struct elem_lista_archi {
	struct elem_lista_archi* prev;
	struct elem_lista_archi* next;
	arco* info;
}elem_archi; // elemento di una lista di archi

/*questa è il grafo*/
typedef struct {
	int numero_nodi;
	int numero_archi;
	elem_archi* archi; // lista degli archiclTabCtrl
	elem_nodi* nodi; // lista dei nodi
}grafo;



/***************************************************************funzioni grafo*************************************************************************/
//----------------------new grafo-----------------------
/*funzione che fa l'inizializzazione di un grafo*/
grafo* new_grafo() {

	grafo* g = (grafo*)malloc(sizeof(grafo));

	g->nodi = NULL;
	g->archi = NULL;
	g->numero_nodi = 0;
	g->numero_archi = 0;

	return g;
}
//------------------------------------------------------

//--------------------newnodo---------------------
nodo* aggiungi_nodo (grafo* testa){
	nodo* newn=malloc(sizeof(nodo));
	newn->color=0;
	newn->archi=NULL;
	
	
	elem_nodi* newl=malloc(sizeof(elem_nodi));
	newl->info=newn;
	newn->pos=newl;
	newl->prev=NULL;
	newl->next=testa->nodi;
	
	if(testa->nodi!=NULL){
		testa->nodi->prev=newl;
	}
	testa->nodi=newl;
	testa->numero_nodi++;
	return newn;
}
//------------------------------------------------

//----------------------newarco-------------------
arco* newarco (grafo* testa,nodo* from,nodo* to){
	arco* newa=malloc(sizeof(arco));
	newa->from=from;
	newa->to=to;
	
	elem_archi* newl1=malloc(sizeof(elem_archi));
	newl1->info=newa;
	newa->pos=newl1;
	newl1->prev=NULL;
	newl1->next=testa->archi;
	if(testa->archi!=NULL){
		testa->archi->prev=newl1;
	}
	testa->archi=newl1;
	testa->numero_archi++;
	
	elem_archi* newl2=malloc(sizeof(elem_archi));
	newl2->info=newa;
	newa->frompos=newl2;
	newl2->prev=NULL;
	newl2->next=newa->from->archi;
	if(newa->from->archi!=NULL){
		newa->from->archi->prev=newl2;
	}
	newa->from->archi=newl2;
	
	elem_archi* newl3=malloc(sizeof(elem_archi));
	newl3->info=newa;
	newa->topos=newl3;
	newl3->prev=NULL;
	newl3->next=newa->to->archi;
	if(newa->to->archi!=NULL){
		newa->to->archi->prev=newl3;
	}
	newa->to->archi=newl3;
	
	return newa;
}

//--------------------grafo del testo---------------------
grafo* costruisci_grafo() {

 	grafo* g = new_grafo();

 	nodo* n1 = aggiungi_nodo(g);
 	nodo* n2 = aggiungi_nodo(g);
 	nodo* n3 = aggiungi_nodo(g);
 	nodo* n4 = aggiungi_nodo(g);
 	nodo* n5 = aggiungi_nodo(g);
 	nodo* n6 = aggiungi_nodo(g);
 	nodo* n7 = aggiungi_nodo(g);
 	nodo* n8 = aggiungi_nodo(g);
 	nodo* n9 = aggiungi_nodo(g);
 	nodo* n10 = aggiungi_nodo(g);
 	nodo* n11 = aggiungi_nodo(g);
	nodo* n12 = aggiungi_nodo(g);
	nodo* n13 = aggiungi_nodo(g);

 	/* questa componente ha 3 nodi e 2 archi */
 	newarco(g,n1,n2);
 	newarco(g,n1,n3);

 	/* questa componente ha 4 nodi e 4 archi */
 	newarco(g,n4,n5);
 	newarco(g,n4,n6);
	newarco(g,n6,n5);
	newarco(g,n5,n7);
	
	/* questa componente ha 5 nodi e 4 archi */
 	newarco(g,n8,n9);
	newarco(g,n9,n10);
	newarco(g,n9,n11);
	newarco(g,n11,n12);
 	
 	return g;
}
//-------------------------------------------------------
/****************************************************************************************************************************************************/

/*classica visita di un grafo*/
void dfs (nodo* g,int c) {
	g->color=c;
	elem_archi* la=g->archi;
	while(la!=NULL) {
		nodo* altro_nodo=la->info->from;
		if(altro_nodo==g)
			altro_nodo=la->info->to;
		if(altro_nodo->color==0)
			dfs(altro_nodo,c);
		la=la->next;
	}
} 
/*potrei fare anche una funzione di supporto che trovare la dimensione ma visto che ho tutti i valori del vettore mi conviene 
 * semplicemnte fare il confronto tra questi */


/*funzione che fa la verifica*/
int verifica(grafo* g) {
	if(g==NULL)
		return 1;
	elem_nodi* scorri1=g->nodi;
	int colore=0;
	while(scorri1!=NULL) {
		if(scorri1->info->color==0) {
			colore++;
			printf("\ncolor: %d",colore);
			dfs(scorri1->info,colore);
		}
		scorri1=scorri1->next;
	}
	printf("\n");
	int* vett=(int*)calloc(colore+1,sizeof(int));
	
	//----------riempi vettore---------------
	elem_nodi* temp2=g->nodi;
	while(temp2!=NULL) {
		vett [temp2->info->color]++;
		temp2=temp2->next;
	}
	
	/*faccio anche una stampa cosi vedo i sottografi e con che colore li confronto*/
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d confornto con il colore %d\n",i,vett[i],colore);
		if(vett[i]==colore)
			return 1;
	}
	return 0;
}


int main(int argc, char **argv){
	
	grafo* graf=costruisci_grafo();
	printf("\noutput: %d",verifica(graf));
}