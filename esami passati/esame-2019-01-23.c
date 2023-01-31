#include <stdio.h>
#include <stdlib.h>
//esame 23-01-2019				//da fare
/*int verifica_figli_componente(grafo* g, nodo_albero* a)
che accetti in input un puntatore ad grafo non orientato g rappresentato tramite oggetti e un puntatore a
alla radice di un albero di grado arbitrario di interi rapresentato tramite la struttura figlio‐sinistro
(left_child) e fratello destro (right_sibling). La funzione restituisce 1 se esiste un nodo
dell’albero a che ha tanti figli quanti sono i nodi della componente connessa più grande del grafo g,
altrimenti la funzione restituisce 0. Se grafo e albero sono entrambi vuoti (cioè uguali a NULL) la funzione
ritorna true. Se uno è vuoto e uno no, allora ritorna false.*/


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
nodo_albero* costrisci_albero_arbitrario () {
	
	nodo_albero* root=newalbero(0,'R');
	
	nodo_albero* A=addfigliosx(root,1,'A');
	nodo_albero* B=addfratellodx(A,0,'B');
	
	
	nodo_albero* C=addfigliosx(A,0,'C');
	nodo_albero* D=addfratellodx(C,1,'D');
	nodo_albero* E=addfratellodx(D,0,'E');
	nodo_albero* F=addfratellodx(E,0,'F');
	nodo_albero* G=addfigliosx(B,1,'G');
	
	nodo_albero* H=addfigliosx(E,1,'H');
	nodo_albero* I=addfratellodx(H,1,'I');
	nodo_albero* L=addfigliosx(G,1,'L');
	nodo_albero* M=addfratellodx(L,0,'M');
	
	nodo_albero* N=addfigliosx(I,1,'N');
	return root;
}
 /*questo è l'albero costruito sopra
                              h
              r			      0
		     /
			A_________B       1
		   /   	     /
		  C-D-E-F   G         2
	          /    /
			  H-I  L-M        3 
			    /              
			   N              4   */
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

 	/* questa componente ha 3 nodi e 3 archi */
 	newarco(g,n5,n4);
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


/*funzione richiesta dal problema*/
int verifica (grafo* g, nodo_albero* a) {
	if(a==NULL && g==NULL)
		return 1;
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
	
	int* vett=(int*)calloc(colore+1,sizeof(int));		//vettore dove inserisco tutti i valori dei sottografi (inserisco le dimensioni dei sottografi)
	
	//----------riempi vettore---------------
	elem_nodi* temp2=g->nodi;
	while(temp2!=NULL){
		vett [temp2->info->color]++;
		temp2=temp2->next;
	}
	//-------------------------
	
	//-------trova il massimo-----------
	int max=vett[1];
	for(int i=1;i<=colore;i++) {
		printf("vett [%d]=%d\n",i,vett[i]);
		if(vett[i]>max)
			max=vett[i];
	}
	//----------------------------------
	
	int nodi=;
	int* vett2=(int*)calloc(nodi,sizeof(int));
	int visita(vett,)
	
	
	
	//---------faccio il confronto--------

	//----------------------------------
	
	
	
	
	return 0;
}








//---------------------main------------------------------
int main(int argc, char **argv){
	
	grafo* graf=costruisci_grafo();
	nodo_albero* alb=costrisci_albero_arbitrario(); 
	printf("\noutput: %d",verifica(graf,alb));
	printf(" %d",fun_altezza(alb));
	printf("\n\n\n\n"); 
}
//-------------------------------------------------------
