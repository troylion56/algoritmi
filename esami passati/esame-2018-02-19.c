#include <stdio.h>
#include <stdlib.h>
/*
Discuti la complessità computazionale nel caso peggiore (in termini di O‐grande, Omega e Theta) delle
seguenti procedure in funzione del numero n di elementi dell’albero. Assumi che AGGIUNGI_IN_CODA e
CERCA_IN_CODA facciano entrambe un numero di operazioni proporzionali alla lunghezza della lista
passata in input.
FUNZIONE(T) T è un albero binario di interi 
L.head = NULL /L è una nuova lista (vuota) di interi 
FUNZ_RIC(T.root,L)
return L
FUNZ_RIC(v,L)
if(v==NULL) return
if(CERCA_IN_CODA(L,v.info) == FALSE)
AGGIUNGI_IN_CODA(L,v.info)
FUNZ_RIC(v.left,L)
FUNZ_RIC(v.right,L) 

la funzione funzione non fa nulla l'unica operazione che fa è chiamare funz_ric quindi avra la complessita di quella 
funz_ric fa una ricorsione quindi è tetha(n) poi in piu fa la funzione cerca in coda ma essendo vuota la complessità 
totale sara tetha(n^2) perche piano piano fai l'aggiunta inizialmente è vuota */




/*esame 19-02-2018			*/ //corretto
/*int verifica(grafo_oggetti* g, nodo_albero* a)
che accetti in input un puntatore ad grafo non orientato g rappresentato tramite oggetti e un puntatore a
alla radice di un albero binario di interi. La funzione restituisce 1 se il numero di nodi della componente
connessa più grande (cioè con più nodi) del grafo è uguale alla profondità del nodo con indice (campo info)
più alto dell’albero, altrimenti restituisce 0.
Assumi che l’albero contenga tutti valori interi distinti e non negativi */
/*allora non cio capito un cazzo quindi per me è la profondita del nodo con campo info piu grande*/

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

//------------------------------------------STRUTTRE ALBERO-----------------------------------------------
/*nodo di un albero*/
typedef struct nodo_abero_struc {
	int info;
	struct nodo_abero_struc* left;
	struct nodo_abero_struc* right;
	char nome;
}nodo_albero;
//--------------------------------------------------------------------------------------------------------

/***************************************************************funzioni albero*****************************************************************/
//----------------------new nodo-----------------------
nodo_albero* newnodo (nodo_albero** a){
	nodo_albero* new=malloc (sizeof(nodo_albero));
	new->right=NULL;
	new->left=NULL;
	new->info=2;
	new->nome='r';
	*a=new;
	printf("nodo creato\n");
 }
//-------------------------------------------------------

//-------------inserimento figlio sinistro---------------
nodo_albero* inserimentofiglioleft (nodo_albero* a,int d,char nome){
	if(a->left!=NULL)
		printf("ERRORE\n");
	else{
		a->left=malloc(sizeof(nodo_albero));
		a->left->info=d;
		a->left->left=NULL;
		a->left->right=NULL;
		a->left->nome=nome;
		printf("ho aggiunto il figlio left %d di %d \n",d,a->info);
		return a->left;
	}
}
//-------------------------------------------------------



//-------------inserimento figlio destro---------------
nodo_albero* inserimentofilgioright (nodo_albero* a,int d,char nome){
	if(a->right!=NULL)
		printf("ERRORE\n");
	else{
		a->right=malloc(sizeof(nodo_albero));
		a->right->info=d;
		a->right->left=NULL;
		a->right->right=NULL;
		a->right->nome=nome;
		printf("ho aggiunto il figlio right %d di %d\n",d,a->info);
		return a->right;
	}
}
//-------------------------------------------------------



//----------------costruisco l'albero--------------------

nodo_albero* costrusci_albero () {
	nodo_albero* n=NULL;						//inizializzo n
	
	newnodo (&n);
	
	nodo_albero* a=inserimentofiglioleft(n,1,'A');				//figlio left della n (a)
	nodo_albero* b=inserimentofilgioright(n,1,'B');				//filgio right della n (b)
	
	nodo_albero* c=inserimentofiglioleft(a,0,'C');					//filgio left di a (c)
	nodo_albero* d=inserimentofilgioright(a,1,'D');					//filgio right di a (d)
	
	nodo_albero* e=inserimentofilgioright(b,9,'E');					//filgio right di b (e)
	
	nodo_albero* f=inserimentofilgioright(d,0,'F');					//figlio right di d (f)
	
	nodo_albero* g=inserimentofiglioleft(e,1,'G');					//figlio left di e (g)
	nodo_albero* h=inserimentofilgioright(e,0,'H');					//figlio right di e (h)
	
	nodo_albero* i=inserimentofiglioleft(f,8,'I');					//figlio left di f (i)
	
	
	return n;
	
} 
//-------------------------------------------------------
/****************************************************************************************************************************************************/


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

 	/* questa componente ha 3 nodi e 2 archi */
 	newarco(g,n1,n2);
	newarco(g,n1,n3);

 	/* questa componente ha 3 nodi e 3 archi */
 	newarco(g,n4,n5);
 	newarco(g,n5,n6);
	newarco(g,n6,n4);
	
	/* questa componente ha 4 nodi e 3 archi */
 	newarco(g,n7,n8);
 	newarco(g,n8,n9);
	newarco(g,n9,n10);
 	
 	return g;
}
//-------------------------------------------------------
/****************************************************************************************************************************************************/


//funzione che restituisce il massimo tra due elementi
int massimo(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}


//funzione che trova l'elemento massimo dell'albero facendo la visita
int massimo_albero(nodo_albero* a) {
	if ( a == NULL ) 
		return -1;		//non ritorno niente
	int l = massimo_albero(a->left);			//vado a cercare ricorsivamente sul sotto albero sinistro
	int r = massimo_albero(a->right);		//vado a cercare ricorsivemente sul sotto albero destro
return massimo(a->info,massimo(l, r));	//faccio il confronto tra quello attuale e il massimo di lef e right
}




//funzione che ritorna la profondita del nodo con il magigor valore 
int profondita_nodo(nodo_albero* a, int id,int prof) {
	if (a == NULL) 
		return -1;
	if (a->info == id) 
		return prof;
	int l = profondita_nodo(a->left, id,prof+1);
	int r = profondita_nodo(a->right, id,prof+1);
	int max = massimo(l, r);
	if (max == -1) 
		return -1; // non lo abbiamo trovato
	else 
		return max+1;
}
//funzione che chiama ricorsivamente quella sopra
int profondita_nodo_ric (nodo_albero* a) {
	return profondita_nodo(a,massimo_albero(a),0);
}


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




int verifica (grafo*g,nodo_albero* a) {
	//questo lo dico io nel testo non c'è scritto assumo che tutti e due devono avere almeno un nodo altimento restituisco 0
	if(a==NULL && g==NULL)
		return 0;
	if(a==NULL || g==NULL)
		return 0;
	elem_nodi* scorri1=g->nodi;
	int colore=0;
	while(scorri1!=NULL) {
		if(scorri1->info->color==0) {
			colore++;
			printf("color: %d\n",colore);
			dfs(scorri1->info,colore);
		}
		scorri1=scorri1->next;
	}
	printf("\n");
	
	/*ora alloco memoria al vettore*/
	int* vett=(int*)calloc(colore+1,sizeof(int));
	
	//----------riempi vettore---------------
	elem_nodi* temp2=g->nodi;
	while(temp2!=NULL) {
		vett[temp2->info->color]++;
		temp2=temp2->next;
	}
	//-----------------------------------
	
	//----------trovo il componete piu grande---------------
	int max=vett[1];
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d\n",i,vett[i]);
		if(vett[i]>max)
			max=vett[i];
	}
	//--------------------------------------
	
	printf("Il sottografo piu grande ha %d nodi\n",max);
	if(max==profondita_nodo_ric(a))
		return 1;
	return 0;
}

int main(int argc, char **argv)
{
	grafo* graf=costruisci_grafo();
	nodo_albero* alb=costrusci_albero();
	printf("\nIl valore piu grande: %d",massimo_albero(alb));
	printf("\nLa profondita di quel nodo: %d\n",profondita_nodo_ric(alb));
	printf("\noutput: %d",verifica(graf,alb));
}