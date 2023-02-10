
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>  // per sqrt()


/*************************************STRUTTURA******************************************/
typedef struct mia_struct {
   int key;
   int val;
   struct mia_struct* next;
} coppia;

typedef struct {
  coppia** T;
  int n;  // numero di coppie chiave-valore inserite
  int m;  // lunghezza della tabella
  double irr;
} struct_tabella;
typedef struct_tabella* tabella;
/***************************************************************************************/


#define RESET   "\033[0m"       /* reset Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[0;34m"    /* Blue */


tabella new_tabella() {

	tabella t = (tabella)malloc(sizeof(struct_tabella));
	t->n = 0;  // la tabella e' vuota
	t->m = 4;  // solo quattro righe
	t->T = (coppia**)calloc(t->m, sizeof(coppia*)); // e' gia' inizializzata a NULL
    t->irr = (sqrt(5.0)-1)*0.5;
    return t;
}


int hash_moltiplicativa(tabella t, int key) {

   key = key + 117;                   // per non avere un output prevedibile con lo zero 
   double result = key * t->irr;
   result = result - floor(result);   // tolgo la parte intera ottengo un num in (0,1)
   result = result * t->m;            // ottengo un numero in (0,m)
   result = floor(result);
   return result;
}


void insert(tabella t, int key, int val) {

   int riga = hash_moltiplicativa(t,key);  // riga dove inserire	
   coppia* c = t->T[riga];
   while(c != NULL) {
   	  if( c->key == key ) {  // era gia' in tabella
         c->val = val;       // sovrascrivo il valore
         return;
   	  }
   	  c = c->next;
   }
   // se sei qui vuol dire che non hai trovato la chiave

   if( ((float)t->n)/((float)t->m) > 3 ) {  // alfa > 3 procedo al raddoppio della tabella

       int vecchio_m = t->m;
       t->m = t->m*2;
       printf("raddoppio la tabella da %d a %d\n",vecchio_m,t->m);
       coppia** nuova = (coppia**)calloc(t->m,sizeof(coppia*));
	   int i;
	   for(i = 0; i < vecchio_m ; i++ ) {
		   coppia* c = t->T[i];
		   while( c != NULL ) {
		   	   int nuova_riga = hash_moltiplicativa(t,c->key);
			   coppia* c_new = (coppia*)malloc(sizeof(coppia));
			   c_new->key = c->key;
			   c_new->val = c->val;
			   c_new->next = nuova[nuova_riga];  // e' NULL se la lista era vuota
			   nuova[nuova_riga] = c_new;
               coppia* cancellami = c; 
		   	   c = c->next;
		   	   free(cancellami);  // dealloco gli elementi della lista
		   }
	   }
	   free(t->T);   // dealloco l'array precedente
	   t->T = nuova; // lo sostituisco con il nuovo array

   }
   c = (coppia*)malloc(sizeof(coppia));
   c->key = key;
   c->val = val;
   c->next = t->T[riga];  // e' NULL se la lista era vuota
   t->T[riga] = c;
   t->n = t->n + 1;       // aggiorno il numero di elementi inseriti  
}

int get_table(tabella t, int key);

void free_table(tabella t);

void print_tabella(tabella t) {

   int i;
   for(i = 0; i < t->m ; i++ ) {
	   printf("[%d]",i);
	   coppia* c = t->T[i];
	   while( c != NULL ) {
	   		printf("->(%d,%d)",c->key,c->val);
	        c = c->next;
	   }
	   printf("\n");
   }
   printf("\n");
}

void main() {

   tabella t = new_tabella();

   int i;
   for ( i = 0 ; i < 66 ; i++) {
   	   printf("INSERISCO %d,%d nella riga %d\n",i,i,hash_moltiplicativa(t,i));
   	   insert(t,i,i);
       print_tabella(t);
       printf("\n");
       getchar();
   }
   printf("\n");

   print_tabella(t);

}
