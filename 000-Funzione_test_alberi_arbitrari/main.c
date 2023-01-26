#include <stdio.h>
#include <stdlib.h>

//------------------------------------------STRUTTRE ALBERO-----------------------------------------------
/*nodo di un albero*/
typedef struct nodo_abero_struc {
	int info;
	struct nodo_abero_struc* parent;
	struct nodo_abero_struc* left;
	struct nodo_abero_struc* right;
	char nome;
}nodo_albero;
//--------------------------------------------------------------------------------------------------------

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
	nodo_albero* C=addfratellodx(B,0,'C');
	
	nodo_albero* D=addfigliosx(A,1,'D');
	nodo_albero* E=addfratellodx(D,0,'E');
	nodo_albero* F=addfigliosx(C,0,'F');
	nodo_albero* G=addfratellodx(F,1,'G');
	
	nodo_albero* H=addfigliosx(D,1,'H');
	nodo_albero* I=addfratellodx(H,1,'I');
	nodo_albero* L=addfratellodx(I,1,'L');
	nodo_albero* M=addfigliosx(F,0,'M');
//	nodo_albero* N=addfigliosx(G,1,'N');
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

int conta_nodi(nodo_albero* n) {
    if (n == NULL) 
		return 0;
    return 1 + conta_nodi(n->left) + conta_nodi(n->right);
 }

//funzione che conta i nodi in post ordine 
int contaNodiPost(nodo_albero* a) {
	if( a == NULL ) 
		return 0;
   int cont = 1;   // intanto c'è il nodo a
   nodo_albero* x = a->left;
   while ( x != NULL ) {
	cont = cont + contaNodiPost(x);
       x = x->right_sibling;
   } 
   return cont;
}


int main(int argc, char **argv)
{
	nodo_albero* alb=costrisci_albero_arbitrario();
	printf("\n%d",conta_nodi(alb));
}