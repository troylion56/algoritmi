#include <stdio.h>
#include <stdlib.h>
/*esame 01-09-2020*/				//funziona
/*Scrivi in linguaggio C il codice della funzione int verifica(nodo* a) che accetti
in input un puntatore alla radice di un albero binario di interi e ritorni 1 se esiste un nodo
dell’albero che è radice di un sottoalbero che ha esattamente la metà dei nodi dell’intero
albero, altrimenti ritorna 0. Se i nodi dell’albero sono dispari la funzione verifica()
ritorna ovviamente 0.
Per esempio con l'albero in figura la funzione verifica() ritorna 1 perché il nodo
grigio è radice di un sottoalbero (evidenziato con il tratteggio) che ha 5 nodi, che sono
esattamente la metà dei nodi totali dell’albero (che ha in tutto 10 nodi).*/


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
	
	nodo_albero* e=inserimentofilgioright(b,5,'E');					//filgio right di b (e)
	
	nodo_albero* f=inserimentofilgioright(d,6,'F');					//figlio right di d (f)
	
	nodo_albero* g=inserimentofiglioleft(e,7,'G');					//figlio left di e (g)
	nodo_albero* h=inserimentofilgioright(e,8,'H');					//figlio right di e (h)
	
	nodo_albero* i=inserimentofiglioleft(f,9,'I');					//figlio left di f (i)
	
	return n;
	
	/*disegno l'albero binario
	        n
		   / \
	      A   B
		 / \   \
	    C  D    E
		    \   /\ 
		     F G  H
			 /
			I   */
} 
//-------------------------------------------------------
/****************************************************************************************************************************************************/

/*funzione che conta il numero di nodi*/
int numero_nodi (nodo_albero* a) {
	if(a==NULL)
		return 0;
	return 1+numero_nodi(a->left)+numero_nodi(a->right);
}

int verifica (nodo_albero* a) {
	if(a==NULL)
		return 0;
	if(numero_nodi(a)%2 !=0)
		return 0;
	if(numero_nodi(a->left)==(numero_nodi(a)/2))
		return 1;
	if(numero_nodi(a->right)==(numero_nodi(a)/2))
		return 1;
	return verifica(a->left) || verifica(a->right);
}

/*funzione main*/
int main(int argc, char **argv){
	
	nodo_albero* alb=costrusci_albero();
	printf("\noutout: %d",verifica(alb));
}