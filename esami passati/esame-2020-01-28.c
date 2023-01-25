#include <stdio.h>
#include <stdlib.h>
/*esame 28-01-2020*/		//corretto
/*int verifica(nodo_albero* a, grafo* g)
che accetti in input un puntatore a alla radice di un albero di grado arbitrario di interi e un puntatore g ad
grafo non orientato rappresentato tramite oggetti e riferimenti. La funzione restituisce 1 se esiste nodo
dell’albero che ha tanti figli quanti sono i nodi di una componente connessa del grafo g, altrimenti la
funzione restituisce 0. Se uno (o entrambi) tra grafo e albero è vuoto (cioè uguale a NULL) la funzione
ritorna 0 */

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

//-------------------newalbero--------------------
nodo_albero* newalbero (int n,char nome){
	nodo_albero* new=malloc(sizeof(nodo_albero));
	new->left=NULL;
	new->right=NULL;
	new->info=n;
	new->nome=nome;
	return new;
}
//------------------------------------------------

//-------------------addfilgiosx------------------
nodo_albero* addfigliosx (nodo_albero* radice,int n,char nome){
	nodo_albero* new=malloc(sizeof(nodo_albero));
	radice->left=new;
	new->info=n;
	new->nome=nome;
	new->right=NULL;
	new->left=NULL;
	return new;
}
//------------------------------------------------

//------------------addfratellodx-----------------
nodo_albero* addfratellodx (nodo_albero* radice,int n,char nome){
	nodo_albero* new=malloc(sizeof(nodo_albero));
	radice->right=new;
	new->info=n;
	new->nome=nome;
	new->right=NULL;
	new->left=NULL;
	return new;
}
//------------------------------------------------

//--------------COSTRUSICI ALBERO-----------------
nodo_albero* costruisci_albero_arbitrario () {
	
	nodo_albero* root=newalbero(0,'R');
	
	nodo_albero* A=addfigliosx(root,1,'A');
	nodo_albero* B=addfratellodx(A,0,'B');
	nodo_albero* C=addfratellodx(B,0,'C');
	
	nodo_albero* D=addfigliosx(A,1,'D');
	nodo_albero* E=addfratellodx(D,0,'E');
	nodo_albero* F=addfigliosx(C,0,'F');
	nodo_albero* G=addfratellodx(F,1,'G');
	
	nodo_albero* H=addfigliosx(D,1,'H');
	nodo_albero* I=addfratellodx(H,1,'I');
	nodo_albero* L=addfratellodx(I,1,'L');
	nodo_albero* M=addfigliosx(F,0,'M');
	nodo_albero* N=addfigliosx(G,1,'N');
	return root;
}
 /*questo è l'albero costruito sopra
                        h
              r			0
		     /
			A-B-C       1
		   /   /
		  D-E  F-G      2
	     /     | |
		H-I-L  M N      3 */
//------------------------------------------------
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


//-------------------contafigli-------------------
int contafigli (nodo_albero* a){
	/*funzione di supporto che prende un nodo e ne conta i fratelli per determinare i figli del genitore*/
	if(a==NULL){
		return 0;
	}
	if(a->left==NULL){
		/*il nodo non ha figli*/
		return 0;
	}
	nodo_albero* temp=a->left;
	int conta=0;
	while(temp!=NULL){
		conta++;
		temp=temp->right;
	}
	return conta;
}
//------------------------------------------------



//-----------------visita albero-------------------
int visita (int* vett,int l,nodo_albero* radice){
	/*visita arbitraria*/
	if(radice==NULL){
		return 0;
	}
	printf("visito [%c]\n",radice->nome);
	int v=0;
	int figli=contafigli(radice);
	printf("[%c] ha %d figli\n",radice->nome,figli);
	for(int i=1;i<l;i++){
		printf("%d=%d\n",vett[i],figli);
		if(vett[i]==figli){
			v=1;
		}
	}
	nodo_albero* temp=radice->left;
	while(temp!=NULL){
		v=v || visita(vett,l,temp);
		temp=temp->right;
	}
	return v;
}
//------------------------------------------------


/*funzione che fa la visita di un grafo in maniera dfs*/
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

/*funzione che fa il confronto*/
int verifica (nodo_albero* a,grafo* g) {
	if(a==NULL && g==NULL) //se entrambi i puntatori sono NULL restituisco 1
		return 0;
	if(a==NULL || g==NULL) //se solo uno dei puntatori è NULL allora restituisco 0
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
	int* vett=(int*)calloc(colore,sizeof(int));
	
	//----------riempi vettore---------------
	elem_nodi* temp2=g->nodi;
	while(temp2!=NULL){
		vett [temp2->info->color]++;
		temp2=temp2->next;
	}
	//-------------------------
	
	//-------stampa il vettore-------------- 
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d\n",i,vett[i]);
	}
	//-------------------------------------
	
	/*studio l'albero*/
	int ver=visita(vett,colore,a);
	
	return ver;
}





int main(int argc, char **argv)
{
	grafo* graf=costruisci_grafo();
	nodo_albero* alb=costruisci_albero_arbitrario();
	printf("%d",verifica(alb,graf));
}
