/*gli alberi a ricerca binaria hanno la caratteristica di stare tutto a sinistra*/
#include <stdio.h>
#include <stdlib.h>

/*nodo di un albero*/
typedef struct nodo_abero_struc {
	int info;
	struct nodo_abero_struc* left;
	struct nodo_abero_struc* right; //siccome arbitrario questo indica il fratello
	char nome;
}nodo_albero;

/***************************************************************funzioni albero*****************************************************************/
//----------------------new nodo-----------------------
nodo_albero* newnodo (nodo_albero** a){
	nodo_albero* new=malloc (sizeof(nodo_albero));
	new->right=NULL;
	new->left=NULL;
	new->info=12;
	new->nome='r';
	*a=new;
	printf("nodo creato con campo info = %d\n",new->info);
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
	nodo_albero* r=NULL;						//inizializzo r 
	
	newnodo (&r);
	
	nodo_albero* a=inserimentofiglioleft(r,0,'A');					//figlio left della n (a)
	nodo_albero* b=inserimentofilgioright(r,13,'B');					//filgio right della n (b)
	
	nodo_albero* c=inserimentofiglioleft(a,9,'C');					//filgio left di a (c)
	nodo_albero* d=inserimentofilgioright(a,11,'D');					//filgio right di a (d)
	
	nodo_albero* e=inserimentofilgioright(b,15,'E');					//filgio right di b (e)
	
	nodo_albero* f=inserimentofiglioleft(d,8,'F');					//figlio right di d (f)
	
	nodo_albero* g=inserimentofiglioleft(e,14,'G');					//figlio left di e (g)
	nodo_albero* h=inserimentofilgioright(e,17,'H');					//figlio right di e (h)
	
	nodo_albero* i=inserimentofiglioleft(f,4,'I');					//figlio left di f (i)

	nodo_albero* l=inserimentofiglioleft(h,16,'L');					
	nodo_albero* m=inserimentofilgioright(h,18,'M');

	nodo_albero* n=inserimentofiglioleft(i,3,'N');
	nodo_albero* o=inserimentofilgioright(i,6,'O');

	nodo_albero* p=inserimentofiglioleft(n,1,'P');
	nodo_albero* q=inserimentofilgioright(n,2,'Q');

	nodo_albero* s=inserimentofiglioleft(o,5,'S');
	nodo_albero* t=inserimentofilgioright(o,7,'T');
	
	return r;
	
} 

             /* r
			   / \ 
			 a     b
		   /  \      \
		  c   d        e
		     /       /   \
			f      g       h			                                                         
		   /             /   \
		  i             l     m		sinistra centro destra si riempie 
		/   \
	   n     o
     /  \  	 / \
	p   q   s   t */   
//-------------------------------------------------------
/****************************************************************************************************************************************************/

void ricorsiva (nodo_albero* a, int n, int* ver) {
	if (a!=NULL) {
		printf("visito: %c val: %d\n",a->nome,a->info);
		if(a->info==n) {
			*ver=1;
		}
		else {
			if(a->info<n) {
				ricorsiva (a->right,n,ver);
			}
			else{
				ricorsiva(a->left,n,ver);
			}
		}
	}
}

int supporto (nodo_albero* a, int n) {
	/*funzione che chiama la ricorsione*/
	int *ver;
	*ver=0;
	ricorsiva (a, n, ver);
	return *ver;
}



void solo_un_figlio_con_puntatore_esterno (nodo_albero* a, int* ver) {
	if(a==NULL)
		return ;
	if( (a->right==NULL && a->left!=NULL) || (a->right!=NULL && a->left==NULL))
		*ver ++;
	solo_un_figlio_con_puntatore_esterno(a->left,ver);
	solo_un_figlio_con_puntatore_esterno(a->right,ver);
}

int sup (nodo_albero*  a){
	int* ver;
	*ver=0;
	solo_un_figlio_con_puntatore_esterno(a,ver);
	return *ver;
}


int main () {
    nodo_albero* alb=costrusci_albero();
    printf("%d", supporto(alb,1));
	printf("%d",sup(alb));
}
 

/*
//funzione che calcola i nodi a profondita arbitrario
int profonditaArb (albero n,int v) {
	if(n==NULL)
		return 0;
	else{
		if(v==0)
			return 1;
		else 
			return profonditaArb(n->dx,v-1)+profonditaArb(n->sx,v);
	}
} */