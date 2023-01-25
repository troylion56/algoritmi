#include <stdio.h>

//---------------------------strutture-------------------------------
typedef struct nodo {
	int n;
	struct nodo* next;
	struct nodo* prev;
}NODO;

typedef NODO* puntanodo;
//-------------------------------------------------------------------

//---------------------------new lista-------------------------------
puntanodo newlista (){
	puntanodo nuovo=calloc (1,sizeof(NODO));
	nuovo->next=NULL;
	nuovo->prev=NULL;
	return nuovo;
}
//-------------------------------------------------------------------

//---------------------------inserimento-----------------------------
void inserimento (puntanodo testa,int n){
	puntanodo nuovo=calloc (1,sizeof(NODO));
	while(testa->next!=NULL){
		testa=testa->next;
	}
	testa->next=nuovo;
	nuovo->prev=testa;
	nuovo->n=n;
}
//-------------------------------------------------------------------

//--------------------------stampalista------------------------------
void stampalista (puntanodo testa){
	testa=testa->next;
	printf("---------------------------------\n");
	for(int i=0;testa!=NULL;i++){
		printf("[%d] ",testa->n);
		testa=testa->next;
	}
	printf("\n---------------------------------\n");
}
//-------------------------------------------------------------------

//--------------------------stampa inversa---------------------------
void stampainversa (puntanodo testa){
	while(testa->next!=NULL){
		testa=testa->next;
	}
	printf("---------------------------------\n");
	while(testa->prev!=NULL){
		printf("[%d] ",testa->n);
		testa=testa->prev;
	}
	printf("\n---------------------------------\n");
}
//-------------------------------------------------------------------

//-------------------------main--------------------------------------
int main(int argc, char **argv)
{
	puntanodo head=newlista();
	for(int j=0;j<5;j++){
		inserimento (head,j);
		stampalista (head);
	}
	stampainversa (head);
	printf("\n\n\n");
	return 0;
}
//-------------------------------------------------------------------