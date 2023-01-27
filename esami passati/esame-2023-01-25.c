#include <stdio.h>
#include <stdlib.h>
/*esame 2023-01-25 esame mio che probabilemnte devo rifare mannaggia al cazzo */	
/*nodo_albero* abr_da_grafo (grafo* g) 
che accetti in input un puntatore g ad un grafo non orientato rappresentato tramite oggetti e riferimenti in
cui si assume (non deve essere verificato dalla funzione) che ogni componente connessa di g abbia un numero 
di nodi diverso dalle altre. La funzione restituisce in output un puntatore alla radice di un albero binario 
di ricerca (di altezza qualsiasi) che memorizza le dimensioni (il numero di nodi) delle componenti connesse 
di g. Se il grafo è NULL o non ha nessun nodo, la funzione ritorna NULL*/	



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

 	newarco(g,n2,n3);

 	newarco(g,n4,n5);
 	newarco(g,n5,n6);
	

	newarco(g,n7,n8);
	newarco(g,n8,n9);
	newarco(g,n9,n10);
		
 	return g;

/* 		n1  n2-n3      n4-n5-n6       n7-n8-n9-n10*/

}
//-------------------------------------------------------
/****************************************************************************************************************************************************/


nodo_albero* nuovoNodo(int info) {
    nodo_albero* node = (nodo_albero*) malloc(sizeof(nodo_albero));
    node->info = info;
    node->left = NULL;
    node->right = NULL;
    return(node);
}


void stampaalbero (nodo_albero* root) {
	if(root !=NULL) {
		printf("\nnodo: %d \t",root->info);
		if (root->left!=NULL){
			printf("sx: %d \t",root->left->info);
		}
		if (root->right!=NULL){
			printf("dx: %d",root->right->info);
		}
		
		stampaalbero(root->left);
		stampaalbero(root->right);
	}
}


void aggiungi_nodo_albero(nodo_albero* root, int info) {
    if (info < root->info) {
        if (root->left != NULL) {
            aggiungi_nodo_albero(root->left, info);
        } 
		else {
            root->left = nuovoNodo(info);
			printf("\ncreo e aggiungo a sinistra: %d",info);
        }
    } 
	else if (info > root->info) {
        if (root->right != NULL) {
            aggiungi_nodo_albero(root->right, info);
        } 
		else {
            root->right = nuovoNodo(info);
			printf("\ncreo e aggiungo a destra: %d\n",info);
        }
    }
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

nodo_albero* abr_da_grafo (grafo* g) {
	if(g==NULL)
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
	
	int* vett=(int*)calloc(colore,sizeof(int));
	
	//----------riempi vettore---------------
	elem_nodi* temp2=g->nodi;
	while(temp2!=NULL){
		vett [temp2->info->color]++;
		temp2=temp2->next;
	}
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d\n",i,vett[i]);	
	}
	//-------------------------
    nodo_albero* root=nuovoNodo(vett[1]);
	for (int i=1;i<=colore;i++) {
		aggiungi_nodo_albero(root,vett[i]);
		printf("inserisco nell'lbero: %d\n",vett[i]);
	}
	stampaalbero(root);
	return root;
}


//---------------------main------------------------------
int main(int argc, char **argv){
	
	grafo* grap=costruisci_grafo();
	abr_da_grafo(grap);
}
//-------------------------------------------------------