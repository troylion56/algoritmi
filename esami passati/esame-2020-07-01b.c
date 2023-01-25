#include <stdio.h>
#include <stdlib.h>
/*easame 1-07_2020 b*/						//corretta
/*Scrivi in linguaggio C il codice della funzione int conta(nodo* a) che accetti in input un
puntatore alla radice di un albero di grado arbitrario di interi. La funzione restituisce il
numero dei nodi dell’albero che hanno un valore del campo info pari al numero dei
discendenti del nodo stesso.
Per esempio per l'albero in figura la funzione conta() restituisce 2 perché ci sono due nodi
(quello rosso e quello grigio) che hanno un valore del campo info (rappresentato affianco
al nodo) esattamente uguale al numero dei loro discendenti.
*/

/*nodo di un albero*/
typedef struct nodo_abero_struc {
	int info;
	struct nodo_abero_struc* left;
	struct nodo_abero_struc* right; //siccome arbitrario questo indica il fratello
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
	
	nodo_albero* root=newalbero(3,'R');
	
	nodo_albero* A=addfigliosx(root,5,'A');
	nodo_albero* B=addfratellodx(A,20,'B');
	
	
	nodo_albero* C=addfigliosx(A,0,'C');
	nodo_albero* D=addfratellodx(C,6,'D');
	nodo_albero* E=addfratellodx(D,3,'E');
	nodo_albero* F=addfigliosx(B,5,'F');
	
	nodo_albero* G=addfigliosx(D,2,'G');
	nodo_albero* H=addfigliosx(F,3,'H');
	nodo_albero* I=addfratellodx(H,30,'I');
	
	nodo_albero* L=addfigliosx(G,11,'L');
	return root;
}
 /*questo è l'albero costruito sopra
                              h
              r			      0
		     /
			A_________B       1
		   /   	     /
		  C-D-E     F         2
			/      /
		    G     H-I         3 
		    /              
			L                  4   */
//-------------------------------------------------------
/****************************************************************************************************************************************************/



/*funzione che conta quanti discendenti ci sono da un nodo*/
int numero_discendeni (nodo_albero* a) {
	if(a==NULL)
		return 0;
	int discendenti=0;
	nodo_albero* temp=a->left;
	while(temp!=NULL) {
		discendenti++;
		discendenti=discendenti+numero_discendeni(temp);
		temp=temp->right;
	}
	return discendenti;
}

/*funzione che fa la visita e verifica*/
/*lo percorro come se fosse un+albero binario perchè devo solo contare i nodi*/
int conta(nodo_albero* a){
	if(a==NULL)
		return 0;
	int count=0;
	if(numero_discendeni(a)==a->info) {
		count=count+1;
		printf("\n%c %c il nodo che ha campo info uguale ai discendenti e il campo info vale: %d",a->nome,138,a->info);
	}
	return count+conta(a->left)+conta(a->right);
}

/*la visita si puo fare come un albero binario perche devo solo contare i nodi*/



int main(int argc, char **argv){
	nodo_albero* alb=costruisci_albero_arbitrario();
	printf("numero di discendenti da r %d\n",numero_discendeni(alb));
	int quanti=conta(alb);
	printf("\nIl numero di nodi che rispettano la condizione sono: %d",quanti);
	printf("\n\n\n\n");
}