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
	new->info=3;
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
	
	nodo_albero* a=inserimentofiglioleft(n,5,'A');				//figlio left della n (a)
	nodo_albero* b=inserimentofilgioright(n,2,'B');				//filgio right della n (b)
	
	nodo_albero* c=inserimentofiglioleft(a,3,'C');					//filgio left di a (c)
	nodo_albero* d=inserimentofilgioright(a,4,'D');					//filgio right di a (d)
	
	nodo_albero* e=inserimentofilgioright(b,5,'E');					//filgio right di b (e)
	
	nodo_albero* f=inserimentofilgioright(d,6,'F');					//figlio right di d (f)
	
	nodo_albero* g=inserimentofiglioleft(e,7,'G');					//figlio left di e (g)
	nodo_albero* h=inserimentofilgioright(e,8,'H');					//figlio right di e (h)
	
	nodo_albero* i=inserimentofiglioleft(f,9,'I');					//figlio left di f (i)
	
	return n;
	
} 
//-------------------------------------------------------
/****************************************************************************************************************************************************/


int main (){
	nodo_albero* alb=costrusci_albero();
	printf("test");
}