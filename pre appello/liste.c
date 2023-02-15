#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------STRUTTURE LISTE---------------------------------------------------------
//inzializzazione struttura della lista 
typedef struct lista{
	int info ;
	struct lista* next;				//puntatore all'elemento successivo della lista
}Lista;
typedef Lista* puntaLista;			//puntatore alla lista
//------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------FUNZIONE CHE COSTURISCE LE LISTE------------------------------------------------
//funzione che costruisce la lista poi la invoco nel main fa un inserimento in testa 
puntaLista costruisci_lista(){
    puntaLista p = NULL;
    int L[] = {5,4,3,2,1};
    for(int i = 0; i < 5; i++ ) {
        puntaLista temp = (puntaLista)malloc(sizeof(Lista*));
        temp->info = L[i];
        temp->next = p;
        p = temp;
    }
    return p;
}

//questa lista l'ho dichiarata perche mi serve per fare il confronto (ultima funzione) fa sempre un inserimento in testa
puntaLista costruisci_lista1(){
    puntaLista p = NULL;
    int L[] = {10,9,8,7,6};
    for(int i = 0; i < 5; i++ ) {
        puntaLista temp = (puntaLista)malloc(sizeof(Lista*));
        temp->info = L[i];
        temp->next = p;
        p = temp;
    }
    return p;
}

//questa funzione stampa la lista 
void stampaLista (puntaLista l) {
	if(l==NULL){
		printf("\nLa lista e' vuota\n\n");
		return;
	}
	else {
		puntaLista l;
		while(l!=NULL) {
			printf("[%d]",l->info);
			l=l->next;
		}
		printf("\n\n");
	}
}


//------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------FUNZIONI OPERAZIONI SU LE LISTE------------------------------------------------
/*funzione che verifica se l'ultimo elemento della lista è uguale al primo */
int ultimo_uguale_primo(puntaLista l){
	if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0; 
	int primo=l->info;
	puntaLista scorri=l;
	while(scorri->next!=NULL){
		//printf(" %d ",scorri->info); 
		scorri=scorri->next;
	}
	int ultimo=scorri->info;
	//printf("primo valore %d",primo);
	//printf(" ultimo valore%d",ultimo);
	 return primo==ultimo;
}

/*funzione che verifica se l'ultimo elemento della lista è maggiore del primo */
int ultimo_maggiore_primo(puntaLista l){
	if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0; 
	int primo = l->info;
	puntaLista scorri = l;
	while(scorri->next!=NULL){
		scorri=scorri->next;
		//printf("\n%d\n",scorri->info);
	}
	int ultimo= scorri->info;
	//printf("\nprimo valore della lista %d",primo);
	//printf("\nl'ultimo valore della lista %d",ultimo);
	if(ultimo>primo)
		return 1;
	return 0;
}

/*funzione che verifica che la lista sia in ordine decrescente*/
int lista_ordinata_decrescentemente(puntaLista l){
	if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0; 
	puntaLista precc= l; //inizializzo il precedente
	puntaLista succ= precc->next; //inizializzo il succ
	while(succ!=NULL){
		if(precc->info<succ->info)
			return 0 ;
		succ=succ->next;
		precc=precc->next;
	}
	return 1;
}

/*funzione che verifica che la lista sia in ordine crescente*/
int lista_ordinata_crescentemente(puntaLista l){
	if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0; 
	puntaLista precc= l; //inizializzo il precedente
	puntaLista succ= precc->next; //inizializzo il succ
	while(succ!=NULL){
		if(precc->info>succ->info)
			return 0 ;
		succ=succ->next;
		precc=precc->next;
	}
	return 1;
}

/*funzione che verifica che tutti gli elementi della lista hanno campo info pari alla lunghezza della lista*/
 int lunghezza_uguale_campoInfo(puntaLista l){
	 if(l==NULL) 
		 return 0;
	 puntaLista scorri= l;
	 int lenght=0;
	 while(scorri!=NULL){ //prima conto tuttu gli elementi della lista
		 lenght++;
		 scorri=scorri->next;
	 }
	 //printf("\nlunghezza lista %d",lenght);		//lo uso per il debugger
	 scorri=l;
	 while(scorri!=NULL){ //poi verifico che ogni elemento della lista è uguale alla lunghezza della lista
		 if(scorri->info!=lenght){
			 return 0;
		 }
		 scorri= scorri->next;
	 }
	 return 1;
 }

/*funzione che verifica se almeno un elemento della lista ha campo info pari alla lunghezza della lista*/
 int verifica_almeno_un_campoInfo_pari_lunghezza(puntaLista l){
	 if(l==NULL) 
		 return 0;
	 puntaLista scorri= l;
	 int lenght=0;
	 while(scorri!=NULL){
		 lenght++;
		 scorri=scorri->next;
	 }
	 scorri=l;
	 while(scorri!=NULL){
		 if(scorri->info==lenght) {
			 return 1;			//me ne basta uno 
		 }
		 scorri=scorri->next;	//se non trovo vado avanti
	 }
	 return 0;
 }
 
/*funzione che conta i nodi della lista che hanno campo info minore del nodo successivo*/
int conta_nodi_minori_successivo(puntaLista l){
	if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0;  
	int cont=0;
	puntaLista precc=l;
	puntaLista succ = precc->next;
	while(succ!=NULL){
		if(precc->info<succ->info)
			cont++;
		succ=succ->next;
		precc=precc->next;
	}
	return cont;
}

/* lista che verifica se almeno una coppia di valori consecutivi di una lista sono uguali */
  int verifica_coppia_consecutiv_uguali(puntaLista l){
	  if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0; 
	  puntaLista scorri=l;
	  while(scorri->next!=NULL){
		  if(scorri->info==scorri->next->info){
			  return 1;
		  }
		  scorri=scorri->next;
	  }
	  return 0;
}

//funzione che verifica se vi sono doppioni in posizione qualsiasi in una lista nella lista
int verifica_doppioni(puntaLista l){
	if(l==NULL || l->next==NULL) //se la lista è vuota o ha solo un elemento
		return 0; 
	int trovato =0;
	puntaLista precc=l;
	while(precc!=NULL){
		puntaLista succ= precc->next;
		puntaLista precedente=precc;
		while(succ!=NULL){
			//printf("\n%d,%d",precc->info, succ->info);
			if(precc->info==succ->info) {
				trovato =1;
				precedente->next=succ->next;
				free(succ);
				succ=precedente->next;
			}
			else {
				precedente=succ;
				succ=succ->next;
			}
		}
		l=precc;
		precc=precc->next;
	}
	return trovato;
}


//funzione che ritorna il numeri dei valori che sono uguali tra due liste
int conta_elementi_comuni (puntaLista l1, puntaLista l2){
	if (l1 == NULL || l2 == NULL)
		return 0;
	int conta = 0;
	puntaLista scorr1 = l1;
	while (scorr1 != NULL){
		puntaLista scorri2 = l2;
		while (scorri2 != NULL){
			if (scorr1->info == scorri2->info){
				conta++;
				break;				// NB vengono considerati 1 le copie uguali
			}
			scorri2 = scorri2->next;
		}
		scorr1 = scorr1->next;
	}
	return conta;
}
//------------------------------------------------------------------------------------------------------------------------------ 

 
int verificadopp (puntaLista* l) {
	if(l==NULL || l->next)
		return 0;
	int trovato=0;
	puntaLista precc=l;
	while (precc!=NULL)
	{
		puntaLista succ=precc->next;
		puntaLista precedente=precc;
		while (succ!=NULL)
		{
			if(precc->info==succ->info){
				trovato=1;
				precedente->next=succ->next;
				free(succ);
				succ=precedente->next;
			}
			else {
				precedente=succ;
				succ=succ->next;
			}
			l=precc;
			precc=precc->next;
		}
		
	}
	return trovato;
	
}

 
//------------------------------------------------------------MAIN--------------------------------------------------------------
int main()
{
	printf("La prima lista: ");
	puntaLista l = costruisci_lista();
	stampaLista(l);

	printf("La seconda lista: ");
	puntaLista l1=costruisci_lista1();
	stampaLista(l1);

    printf("\nRestituisco true se il primo e' uguale dell'ultimo                                     : %d",ultimo_uguale_primo(l));
    printf("\nRestituisco true se il primo e' minore dell'ultimo                                     : %d",ultimo_maggiore_primo(l));
    printf("\nRestituisce true se la lista e' decrescente                                            : %d",lista_ordinata_decrescentemente(l));
    printf("\nRestituisce true se la lista e' crescente                                              : %d",lista_ordinata_crescentemente(l));
    printf("\nRestiruisce true se la tuttii valori della lista e' uguale alla lunghezza della lista  : %d",lunghezza_uguale_campoInfo(l));
    printf("\nRestiruisce true se almeno un valore della lista e' uguale alla lunghezza della lista  : %d",verifica_almeno_un_campoInfo_pari_lunghezza(l));
    printf("\nRestituisce il numero di nodi minori al successivo                                     : %d",conta_nodi_minori_successivo(l));
    printf("\nVerifica se la coppia successiva e' uguale                                             : %d",verifica_coppia_consecutiv_uguali(l));    
	printf("\nRestiruisce true se esiste un doppione                                                 : %d",verifica_doppioni(l));
	printf("\nRestituisco il numero di elementi uguali tra due liste                                 : %d",conta_elementi_comuni(l,l1));
	printf("\n\n\n");
	printf("%d",verificadopp(l1));
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------ 
