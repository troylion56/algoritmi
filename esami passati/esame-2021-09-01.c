#include <stdio.h>
#include <stdlib.h>
/*esame 01-09-2021*/					//funziona

/*Discuti la complessità computazionale della seguente procedura nel caso peggiore fornendo O‐grande,
Omega e Theta in funzione del numero n di elementi dell’albero.
FUNZIONE(T)  T è un albero binario di interi 
L.head = NULL  L è una nuova lista (vuota) di interi 
FUNZ_RIC(T.root,L)
return L
FUNZ_RIC(v,L)
if(v==NULL) return
if((v.left == NULL) && (v.right == NULL))
AGGIUNGI_IN_CODA(L,v.info)
RIMUOVI_IN_TESTA(L)
else
AGGIUNGI_IN_TESTA(L,v.info)
RIMUOVI_IN_CODA(L)
FUNZ_RIC(v.left,L)
FUNZ_RIC(v.right,L)
Assumi che AGGIUNGI_IN_CODA e RIMUOVI_IN_CODA facciano un numero di operazioni proporzionale alla
lunghezza della lista corrente mentre AGGIUNGI_IN_TESTA e RIMUOVI_IN_TESTA facciano un numero di
operazioni costante

funzione esegue solo istruzioni di theta(1) apparte per la chiamta ricorsiva quindi avra la complessità di essa
funz_ric fa la visita completa quindi la complessita della ricorsione è theta(n) 
aggiungi in coda e rimuovi in coda fanno operazione theta(n)
aggiungi in testa e rimuovi in testa fanno un numero di operazioni costanti quindi theta(1)
quindi la complessita complessiva è theta(n) poiche essendo l'albero iniziale vuoto io per fare l'inserimento in coda 
o la rimozione faro comunque un solo passo*/




/* int verifica(nodo_albero* a, grafo* g)
che accetti in input un puntatore a alla radice di un albero binario di interi e un puntatore g ad un grafo
non orientato rappresentato tramite oggetti e riferimenti. La funzione restituisce 1 (cioè true) se la
profondità della foglia meno profonda dell’albero è uguale al numero di nodi della componente connessa
del grafo g che ha meno nodi, altrimenti la funzione restituisce 0 (cioè false). Se uno (o entrambi) tra grafo
e albero è vuoto (cioè uguale a NULL) la funzione ritorna 0 (false) */



//------------------------------------------------STRUTTURE GRAFO------------------------------------------
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
//--------------------------------------------------------------------------------------------------------

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
	nodo_albero* b=inserimentofilgioright(n,2,'B');				//filgio right della n (b)
	
	nodo_albero* c=inserimentofiglioleft(a,3,'C');					//filgio left di a (c)
	nodo_albero* d=inserimentofilgioright(a,4,'D');					//filgio right di a (d)
	
	nodo_albero* e=inserimentofiglioleft(b,5,'E');					//filgio left di b (e)
	
	nodo_albero* f=inserimentofiglioleft(d,6,'F');					//figlio left di b (f)
	nodo_albero* g=inserimentofilgioright(d,7,'G');					//figlio right di b (g)
	
	nodo_albero* h=inserimentofiglioleft(e,8,'H');					//figlio left di e (h)
	nodo_albero* i=inserimentofilgioright(e,9,'I');					//figlio right di e (i)
	
	nodo_albero* l=inserimentofiglioleft(g,10,'L');					//filgio left di g (l)
	
	return n;
	
} 
/*            n
 *          /   \ 
 *         a     b
 *        /\     / 
 *       c d     e
 *         /\    /\
 *         f g  h  i
 *           /
 *           l            */
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
 	nodo* n11 = aggiungi_nodo(g);

 	/* questa componente ha 3 nodi e 2 archi */
 	newarco(g,n1,n2);
 	newarco(g,n1,n3);

 	/* questa componente ha 3 nodi e 2 archi */
 	newarco(g,n5,n4);
 	newarco(g,n5,n6);
	
	/* questa componente ha 2 nodi e 2 archo */
 	newarco(g,n7,n8);
 	
 	
 	/* questa componente ha 3 nodi e 2 archi */
 	newarco(g,n9,n10);
 	newarco(g,n10,n11);
 	
 	return g;
}
/*       n1-n2   n5-n4  n7-n8   n9-n10-n11
 *       |       |                    
 *       n3      n6                           */
//-------------------------------------------------------
/****************************************************************************************************************************************************/



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



int foglia_meno_profnda (nodo_albero* a, int prof) {
	if(a==NULL)
		return -1;
	if(a->left==0 && a->right==0)
		return prof;
	int l=foglia_meno_profnda(a->left,prof+1);
	int r=foglia_meno_profnda(a->right,prof+1);
	if(l==-1)
		return r;
	if(r==-1)
		return l;
	if(l<r) 
		return l;
	return r;
}


/* funzione che fa la verifica*/
int verifica (nodo_albero* a,grafo* g) {
	if(a==NULL || g==NULL) {
		return 0;
	}
	if(a==NULL && g==NULL) {
		return 0;
	}
	
	//itera su la lista dei nodi anzi che su quella degli archi
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
	while(temp2!=NULL){
		vett [temp2->info->color]++;
		temp2=temp2->next;
	}
	//-------------------------
	
	//-------trovo il minimo---------------
	int min=vett[1];
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d\n",i,vett[i]);
		if(vett[i]<min)
			min=vett[i];
	}
	printf("la componente minore ha %d nodi\n",min);
	//-------------------------
	
	int dim_meno_albero=foglia_meno_profnda(a,0);		//salvo in una varaibile l'elemento del albero minore
	if(min==dim_meno_albero)							//confronto il minimo con la profondita minore 
		return 1;
	return 0;
}


//---------------------main------------------------------
int main(int argc, char **argv){
	
	grafo* graf=costruisci_grafo();
	nodo_albero* alb=costrusci_albero(); 
	int foglia=foglia_meno_profnda(alb,0);
	printf("\nla foglia meno profnda %d",foglia);
	
	printf("\noutput: %d",verifica(alb,graf));
	
	printf("\n\n\n\n"); 
}
//-------------------------------------------------------