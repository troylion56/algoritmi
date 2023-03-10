#include <stdio.h>
#include <stdlib.h>
/*esame 04-02-2019			*/ //corretto
/*Scrivi in linguaggio C il codice della funzione
int verifica(int h, nodo_albero* a, grafo* g)
che accetti in input un intero h, un puntatore a alla radice di un albero binario di interi e un puntatore g ad
grafo non orientato rappresentato tramite oggetti e riferimenti. La funzione restituisce 1 se il numero di
nodi dell’albero a che sono radici di un sottoalbero di profondità h sono tanti quanti sono i nodi della
componente più piccola del grafo g, altrimenti la funzione restituisce 0. Se grafo e albero sono entrambi
vuoti (cioè uguali a NULL) la funzione ritorna 1. Se uno è vuoto e uno no, allora ritorna 0. Se non ci sono
sottoalberi di profondità h in a (cioè se il loro numero è 0) la funzione ritorna 0*/

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
	
	nodo_albero* c=inserimentofilgioright(a,0,'C');					//filgio right di a (c)
	nodo_albero* d=inserimentofilgioright(b,1,'D');					//filgio right di b (d)
	
	nodo_albero* e=inserimentofiglioleft(d,9,'E');					//filgio left di a (e)
	nodo_albero* f=inserimentofilgioright(d,0,'F');					//figlio right di b (f)

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

 	/* questa componente ha 2 nodi e 1 archi */
 	newarco(g,n1,n2);

 	/* questa componente ha 3 nodi e 3 archi */
 	newarco(g,n3,n4);
 	newarco(g,n4,n5);
	newarco(g,n5,n6);
	
	/* questa componente ha 4 nodi e 3 archi */
 	newarco(g,n7,n8);
 	newarco(g,n8,n9);
	newarco(g,n9,n10);
 	
 	return g;
}
//-------------------------------------------------------
/****************************************************************************************************************************************************/

//funzione che calcola la profondita di un albero
int pro_albero (nodo_albero* a) {
	if(a==NULL)
		return -1;
	int l=pro_albero(a->left);
	int r=pro_albero(a->right);
	if(l>r)
		return l+1;
	return r+1;
}



//funzione che calcola il numero di sottoalberi dell'albero passato in esame
int numero_sottoalbero (nodo_albero* a, int alt) {
	if(a==NULL)
		return 0;
	int ris=numero_sottoalbero(a->left,alt)+numero_sottoalbero(a->right,alt);
	if(pro_albero(a)==alt)
		ris++;
	return ris;
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


int verifica(int h, nodo_albero* a, grafo* g) {
	if(a==NULL && g==NULL)
		return 1;
	if(a==NULL || g==NULL)
		return 0;
	elem_nodi* scorri=g->nodi;
	int colore=0;
	while(scorri!=NULL) {
		if(scorri->info->color==0) {
			colore++;
			dfs(scorri->info,colore);
		}
		scorri=scorri->next;
	}
	
	/*alloco memoria al vettore*/
	int* vett=(int*)calloc(colore+1,sizeof(int));
	
	//-----riempo il vettore----------
	elem_nodi* temp2=g->nodi;
	while(temp2!=NULL) {
		vett[temp2->info->color]++;
		temp2=temp2->next;
	}
	//------------------------------
	
	//------cerco il moìinore-------
	int min=vett[1];
	for(int i=1;i<=colore;i++){
		if(vett[i]<min)
			min=vett[i];
	}
	//-----------------------------
	
	printf("Il componete minore %d\n",min);
	if(min==numero_sottoalbero(a,h))
		return 1;
	 return 0;
}


int main() {
	nodo_albero* alb=costrusci_albero();
	grafo* gra=costruisci_grafo();
	printf("\noutput: %d",verifica(2,alb,gra));
}

