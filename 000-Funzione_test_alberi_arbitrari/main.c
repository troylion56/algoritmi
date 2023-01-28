#include <stdio.h>
#include <stdlib.h>

//------------------------------------------STRUTTRE ALBERO-----------------------------------------------
/*nodo di un albero*/
typedef struct nodo_abero_struc {
	int info;
	struct nodo_abero_struc* parent;
	struct nodo_abero_struc* left;		// primo figlio (sinistro)
	struct nodo_abero_struc* right;		// fratello destro
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

//funzione che stanpa come è fatto l'albero in pre ordine
void stampa_albero_preordine(nodo_albero* a){

  if( a == NULL) 
  	return;
  printf("%d ",a->info);  
  nodo_albero* x = a->left;
  while( x != NULL ) {
      stampa_albero_preordine(x);
      x = x->right;
  }
}


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
       x = x->right;
   } 
   return cont;
}

//funzione che calcola l'altezza 
int altezza_albero(nodo_albero* a) {

    if( a == NULL ) 
		return -1;
    int max = -1;
    nodo_albero* x = a->left;
    while( x != NULL ) {
      int altezza_figlio = altezza_albero(x);
      if( altezza_figlio > max ) {
        max = altezza_figlio;
      }
      x = x->right;
    }
    return max + 1;
}

int verifica_binario(nodo_albero* a) {

  if ( a == NULL ) 
  	return 1;
  int contatore = 0;  // zero figli
  int i_sottoalberi_soddisfano = 1;  // true
  nodo_albero* x = a->left;
  while ( x != NULL ) {
     contatore++;
     i_sottoalberi_soddisfano = i_sottoalberi_soddisfano && verifica_binario(x);
     x = x->right;
  }
  return (contatore <= 2) && i_sottoalberi_soddisfano;
}

int grado_massimo(nodo_albero* a) {

  if ( a == NULL ) 
  	return 1;
  // verifico se io soddisfo la codizione
  int contatore = 0;  // zero figli
  nodo_albero* x = a->left;
  while ( x != NULL ) {
     contatore++;
     x = x->right;
  }
  int l = grado_massimo(a->left);
  int r = grado_massimo(a->right);
  int max = l;
  if( r > l ) 
	max = r;
  if( contatore > max ) 
  	return contatore;
  return max;
}




int main(int argc, char **argv)
{
	nodo_albero* alb=costrisci_albero_arbitrario();
	stampa_albero_preordine(alb);
	printf("\nconta i nodi del albero arbitrario:            %d",conta_nodi(alb));
	printf("\n restituisce l'altezza del albero arbitrario:  %d",altezza_albero(alb));
	printf("\n verificare se l'abero arbitario e' binario :  %d",verifica_binario(alb));
	printf("\nrestituisce il grado massimo di un albero     :  %d",grado_massimo(alb));
}