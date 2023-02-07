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
	new->info=0;
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
		printf("ho aggiunto il figlio left %d di %d\n",d,a->info);
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
	
	nodo_albero* a=inserimentofiglioleft(r,1,'A');					//figlio left della n (a)
	nodo_albero* b=inserimentofilgioright(r,1,'B');					//filgio right della n (b)
	
	nodo_albero* c=inserimentofiglioleft(a,0,'C');					//filgio left di a (c)
	nodo_albero* d=inserimentofilgioright(a,2,'D');					//filgio right di a (d)
	
	nodo_albero* e=inserimentofilgioright(b,0,'E');					//filgio right di b (e)
	
	nodo_albero* f=inserimentofiglioleft(d,3,'F');					//figlio right di d (f)
	
	nodo_albero* g=inserimentofiglioleft(e,3,'G');					//figlio left di e (g)
	nodo_albero* h=inserimentofilgioright(e,3,'H');					//figlio right di e (h)
	
	nodo_albero* i=inserimentofiglioleft(f,12,'I');					//figlio left di f (i)

	nodo_albero* l=inserimentofiglioleft(h,10,'L');					
	nodo_albero* m=inserimentofilgioright(h,3,'M');

	nodo_albero* n=inserimentofiglioleft(i,10,'N');
	nodo_albero* o=inserimentofilgioright(i,3,'O');

	nodo_albero* p=inserimentofiglioleft(n,10,'P');
	nodo_albero* q=inserimentofilgioright(n,3,'Q');

	nodo_albero* s=inserimentofiglioleft(o,10,'S');
	nodo_albero* t=inserimentofilgioright(o,3,'T');
	
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
		  i             l     m  
		/   \
	   n     o
     /  \    / \
	p   q   s   t */
//-------------------------------------------------------
/****************************************************************************************************************************************************/

/*************************************************************TUTTI I PRE ESAME (ALBERI)*************************************************************/



//----------------------------------------------------------VISITA SEMPLICE-------------------------------------------------------------
/*funzione che va la semplie visita la visita da sola in se per se non serve a niente*/
/*reminder la visita la facciamo tendenzialmente sempre in tutte le funzioni di spporto*/
void visita (nodo_albero* a) {
	if (a==NULL)
		return ;
	else{
		visita(a->left);
		visita(a->right);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------FUNZIONE SUI NODI---------------------------------------------------
/*funzione che conta quanti nodi hanno uno e un solo figlio */
int solo_un_figlio (nodo_albero* a) {
	if(a==NULL)
		return 0;
	int conta=0;
	if( (a->right==NULL && a->left!=NULL) || (a->right!=NULL && a->left==NULL))
		conta ++;
	return conta+solo_un_figlio(a->right)+solo_un_figlio(a->left);
}

/*funzione che conta tutti i nodi di un albero*/
int nodi_albero (nodo_albero* a) {
	if(a==NULL)
		return 0;
	else
		return 1+nodi_albero(a->right)+nodi_albero(a->left);
}

/*funzione fa la somma del campo info di tutti i nodi*/
int somma (nodo_albero* a) {
	if(a==NULL)
		return 0;
	else
		return a->info+somma(a->left)+somma(a->right);
}
//--------------------------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------------------------
/*funzione che fa la ricerca di un valore*/
int ricercaValore (nodo_albero* a,int v) {
	if(a==NULL)
		return 0;
	int verificato=0;
	printf("\n%d",a->info);
	if(a->info==v) {
		verificato=1;
	}
	return verificato || ricercaValore(a->left,v) || ricercaValore(a->right,v);
}
int ricercaValoreric (nodo_albero* a) {
	return ricercaValore(a,12);
}
//--------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------FUNZIONI SULLE FOGLIE-----------------------------------------------------------
/*funzione che verifica se sono una foglia*/
int is_foglia (nodo_albero* a){
	if (a == NULL) 
		return 0;
	if (a->left == NULL && a->right == NULL)	//sono una foglia
		return 1;
	return 0;
}

/*funzione che verifica quanti nodi hanno figli foglie puo essere anche uno ha una funzione di supporto che verifica se è una foglia*/
/*reminder non conta quanti figli ma conta quanti nodi ha figli foglie*/
int conta_nodi (nodo_albero* a){
	if (a == NULL)
		return 0;
	int conta = 0;
	if (is_foglia(a->left) || is_foglia(a->right))	//se ho un figlio foglia conta
		conta++;
	return conta + conta_nodi(a->left) + conta_nodi(a->right);
}

/*funzione che conta solo se ha esattamente due figli foglie non puo essere solo uno ha una funzione di supporto che verifica se è una foglia*/
int conta_figli_due_nodi (nodo_albero* a) {
	if(a==NULL)
		return 0;
	int conta=0;
	if(is_foglia(a->left) && is_foglia(a->right)) 		//deve averne per forza due
		conta++;
	return conta+conta_figli_due_nodi(a->left) + conta_figli_due_nodi(a->right);
}

/*funzione che restituisce 1 se ci sta un nodo che ha due figli foglie altimenti 0 ha una funzione di supporto che verifica se è un a fogli*/
int verifica_figli_due_nodi (nodo_albero* a) {
	if(a==NULL)
		return 0;
	if(is_foglia(a->left) && is_foglia(a->right))
		return 1;
	return verifica_figli_due_nodi(a->left) || verifica_figli_due_nodi(a->right);
}


/*funzione che conta quante foglie ha il campo info =10*/
int conta_foglie_dieci (nodo_albero* a) {
	if(a==NULL)
		return 0;
	int conta=0;
	if(is_foglia(a) && (a->info==10))
		conta++;
	return conta + conta_foglie_dieci(a->left)+conta_foglie_dieci(a->right);
}

/*funzione che conta quante foglie ha il campo info =0*/
int conta_foglie_zero (nodo_albero* a) {
	if(a==NULL)
		return 0;
	int conta=0;
	if(is_foglia(a) && (a->info==0))
		conta++;
	return conta + conta_foglie_zero(a->left)+conta_foglie_zero(a->right);
}

/*funzione conta le foglie*/
int conta_foglie (nodo_albero* a) {
	if(a==NULL)
		return 0;
	int conta=0;
	if(is_foglia(a))
		conta++;
	return conta+conta_foglie(a->left)+conta_foglie(a->right);
}

/*funzione che verifica se ci sono esattamente 10 foglie se è cosi ti torna 1 fa uso della funzione contafoglie*/
int esattamente_dieci_foglie (nodo_albero* a) {
	if(a==NULL)
		return 0;
	if(conta_foglie(a)==10)
		return 1;
	return 0;
}

/*funzione che verifica se ci sta una foglia destra nell'albero*/
int verifica_esiste_foglia_destra (nodo_albero* a) {
	if(a==NULL)
		return 0;
	if(is_foglia(a->right))
		return 1;
	return verifica_esiste_foglia_destra(a->left) || verifica_esiste_foglia_destra(a->right);
}
//--------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------OPERAZIONI SU PROFONDITA E ALTEZZA ---------------------------------------------------
/*funzione che ritorna la profondita meno profonda di un albero binario*/
/*reminder la chiamo dal main passandogli la profondita iniziale posso fare la stessa cosa facendo cio*/
int foglia_meno_profonda (nodo_albero* a, int prof) {
	if(a==NULL)
		return -1;
	if(a->left==0 && a->right==0)
		return prof;
	int l=foglia_meno_profonda(a->left,prof+1);
	int r=foglia_meno_profonda(a->right,prof+1);
	if(l==-1)
		return r;
	if(r==-1)
		return l;
	if(l<r) 
		return l;
	return r;
}
int foglia_meno_profonda_ric(nodo_albero* a) {
	return foglia_meno_profonda(a,0);
}

/*Verifica se tutti i nodi di un albero hanno campo info uguale all'altezza del nodo.*/
int verifica_tutti_info_altezza (nodo_albero* a, int altezza) {
	int verifica=1;
	if(a==NULL)
		return 1;
	if(a->info!=altezza)
		verifica=0;
	//printf("\nnodo: %c\tinfo: %d\th: %d\n",a->nome,a->info,altezza);
	return verifica && verifica_tutti_info_altezza(a->left,altezza+1) && verifica_tutti_info_altezza(a->right,altezza+1);
}
int verifica_tutti_info_altezza_ric(nodo_albero* a){
	return verifica_tutti_info_altezza(a,0);
}

/*quanti nodi di un albero binario hanno campo info uguale alla distanza dalla radice (è un altro modo per dire profndita)*/
/*Troy mannaggia al cazzo non farti fragare da ste cose eh*/
/*qui l'ho fatto che viene chiamato dal main*/
int nodi_info_uguale_altezza(nodo_albero* a, int prof){
    int quanti=0;
    if(a==NULL)
        return 0;
    if(a->info==prof)
        quanti++;
    return quanti + nodi_info_uguale_altezza(a->left, prof+1) + nodi_info_uguale_altezza(a->right, prof+1);
}

/*funzione che conta quanti nodi hanno il campo info uguale all'altezza del nodo */
/*questa l'ho fatta che viene chiamata da un'altra funzione che passa a e la prof iniziale*/
int nodi_info_uguale_altezza_ric_nodo_cambia(nodo_albero* a, int altezza){
    int conta=0;
    if(a==NULL)
        return 0;
    if(a->info==altezza)
        conta++;
	//printf("\nnodo: %c\tinfo: %d\th: %d\n",a->nome,a->info,altezza);
    return conta + nodi_info_uguale_altezza_ric_nodo_cambia(a->left, altezza+1) + nodi_info_uguale_altezza_ric_nodo_cambia(a->right, altezza+1);
}
/*funzione principale*/
int nodi_info_uguale_altezza_nodo_cambia(nodo_albero* a){
    return nodi_info_uguale_altezza_ric_nodo_cambia(a,0);
}

/*Verifica se tutti i nodi di un albero hanno campo info uguale all'altezza del albero usa la funzione altezza*/
/*per fare cio mi scrivo una funzione d'appoggio che mi calcola l'altezza* è equivalente a dire la profondita*/
int fun_altezza (nodo_albero* a) {
	if(a==NULL)
		return -1;
	int l=fun_altezza(a->left);
	int r=fun_altezza(a->right);
	if(l<r)
		return r+1;
	return l+1;			//se fosse stato un albero arbitrario return r
}

/*questa è la funzione posso chiamarla direttamente dal main scrivendo alb e altezza(alb)*/
int verifica_info_alt_albero (nodo_albero* a,int altezza){
	int verifica=1;
	if (a==NULL)
		return 1;
	if(a->info!=altezza)
		verifica=0;
	/*con questa scritta verifico i valori di info e lo confronto con la sua altezza*/
	//printf("\nnodo: %c\tinfo: %d\th: %d\n",a->nome,a->info,h); 			//attivala solo se non ti aspetti il valore trovato
	int l=verifica_info_alt_albero(a->left,altezza);
	int r=verifica_info_alt_albero(a->right,altezza);
	return  l && r && verifica;
}

int verifica_info_alt_albero_ric (nodo_albero* a) {
	int h=fun_altezza(a);
	return verifica_info_alt_albero(a,h);
}
//--------------------------------------------------------------------------------------------------------------------------------------



//-------------verifica se l'albero è un cammino-------------
int sono_un_cammino(nodo_albero* a) {

	if( a == NULL ) 
  		return 1; // suppongo che un albero vuoto sia un cammino
	if( (a->left == NULL) && (a->right == NULL) )
  		return 1;
	if( (a->left != NULL) && (a->right != NULL) ) 
		return 0;  // due figli
	// se sono qui uno tra a->left e a->right e' diverso da NULL e l'altro e' uguale a NULL
  	if( a->left != NULL ) 
		return sono_un_cammino(a->left);
  	return sono_un_cammino(a->right); 
}
//-------------------------------------------------------



//---------------------main------------------------------
int main(int argc, char **argv){
	
	nodo_albero* alb=costrusci_albero();
	
	printf("\nRestituisco true se esiste un valore richiesto (cerco 12)                	: %d",ricercaValoreric(alb));
	printf("\nRestituisce quanti nodi ci stanno in un albero                          	: %d", nodi_albero(alb));
	printf("\nrestituisco quanti nodi hanno solamente un figlio                        	: %d",solo_un_figlio(alb));
	printf("\nCalcola la somma dei valori di tutti i nodi                              	: %d",somma(alb));
	printf("\nLa profndita meno profonda                                              	: %d ",foglia_meno_profonda_ric(alb));
	printf("\nNodi che hanno figli foglie                                              	: %d",conta_nodi(alb));
	printf("\nNodi che hanno esattamente due figli foglie                              	: %d",conta_figli_due_nodi(alb));
	printf("\nRestituisco true se ci sono esattamente 10 foglie                        	: %d",esattamente_dieci_foglie(alb));
	printf("\nRestituisco true se ci sta un nodo che ha due figli foglie               	: %d",verifica_figli_due_nodi(alb));
	printf("\nRestituisco true se ci sta una foglia destro                             	: %d",verifica_esiste_foglia_destra(alb));
	printf("\nFoglie con campo info=10                                                	: %d",conta_foglie_dieci(alb));
	printf("\nFoglie con campo info=0                                                  	: %d",conta_foglie_zero(alb));
	printf("\nConta folgie                                                             	: %d",conta_foglie(alb));
	printf("\nAltezza dell'albero                                                     	: %d",fun_altezza(alb));
	printf("\nNodi che hanno campo info uguale alla distanza dalla radice              	: %d",nodi_info_uguale_altezza(alb,0));
	printf("\nquanti nodi hanno altezza info = al altezza nodo                         	: %d",nodi_info_uguale_altezza_nodo_cambia(alb));
	printf("\nRestituisco true se tutti i nodi->info sono uguali all'altezza del nodo  	: %d",verifica_tutti_info_altezza_ric(alb));
	printf("\nRestituisco true se tutti i nodi->info sono uguali all'altezza totale    	: %d",verifica_info_alt_albero_ric(alb));
	printf("\nverifica se sono un cammino                                              	: %d",sono_un_cammino(alb));
	printf("\n\n\n\n");
}
//-------------------------------------------------------





