#include <stdio.h>
#include <stdlib.h>
/*esame 19-09-2022 quello che ha fatto bishoy*/			//corretto
/*int verifica(oodo_albero* a, grafo* g)
che accetti in imput un puntatore a alla radice di un albero binario di interi e un puntatore g ad un 
grafo non orientato rappresentato tramite oggetti e riferimenti. La funzione restituisce 1 (cioè true) 
se esiste un nodo con due figli nell'albero la cui profondità è uguale al numero di nodi della componente 
connessa del grafo g che ha meno nodi altrimenti la funzione restituisce 0 (cioè false). Se uno 
(o entrambi) tra grafo e albero è vuoto (cioè uguale a NULL) la funzione ritorna 0 (false).*/



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

/*nodo di un albero*/
typedef struct nodo_abero_struc {
	int info;
	struct nodo_abero_struc* left;
	struct nodo_abero_struc* right;
	char nome;
}nodo_albero;


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

/*           n
 *          / \ 
 *         a   b
 *        /\    / 
 *       c d    e
 *         /\   /\
 *         f g h  i
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

 	/* questa componente ha 2 nodi e 1 arco */
 	newarco(g,n1,n2);

 	/* questa componente ha 3 nodi e 1 archi */
 	newarco(g,n3,n4);
 	newarco(g,n4,n5);
	
	/* questa componente ha 3 nodi e 3 archi */
	newarco(g,n6,n7);
	newarco(g,n7,n8);
	newarco(g,n8,n6);
	
	/* questa componente ha 3 nodi e 2 archi */
 	newarco(g,n9,n10);
 	newarco(g,n10,n11);
	
	
 	return g;
}
//-------------------------------------------------------
/****************************************************************************************************************************************************/

int is_foglia (nodo_albero* a) {
	if(a==NULL)
		return 0;
	if( (a->left==NULL) && (a->right==NULL))
		return 1;
	return 0;
}


//faccio il confrono e la verica in questa funzione chiamo una funzione d'appoggio che mi verifica se sono una foglia
int verifica_figli_visita (nodo_albero* a,int alt, int dim_gra) {	//dim_gra è la dimensione del sottografo piu grande
	if(a==NULL)
		return 0;
	printf("\nvisito [%c]",a->nome);
	int l= verifica_figli_visita(a->left,alt+1,dim_gra);
	int r= verifica_figli_visita(a->right,alt+1,dim_gra);
	if(alt==dim_gra && ((is_foglia(a->left)) && (is_foglia(a->right)) )) {
		printf("\nil nodo che soddisfa la condizione [%c]",a->nome);
		return 1;
	}
	return l || r;
}



void dfs(nodo* g,int c) {
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

int verifica (grafo* g, nodo_albero* a, int h) {
	if(g==NULL && a==NULL)
		return 0;
	if(g==NULL || a==NULL)
		return 0;
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
	
	int min=vett[1];
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d\n",i,vett[i]);
		if(vett[i]<min)
			min=vett[i];
	}
	printf("la componente minore ha %d nodi\n",min);
	
	if(verifica_figli_visita(a,h,min))
		return 1;
	return 0;
}





//---------------------main------------------------------
int main(int argc, char **argv){
	
	grafo* grap=costruisci_grafo();
	nodo_albero* alb=costrusci_albero();
	
	printf("\nil risultato %d",verifica(grap,alb,0));
	
}
//-------------------------------------------------------