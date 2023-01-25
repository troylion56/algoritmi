#include <stdio.h>

typedef struct elem_lista_nodi elem_nodi;
typedef struct elem_lista_archi elem_archi;


typedef struct nodo_struct {
	elem_nodi* pos; // posizione nodo nella lista del grafo 
	elem_archi* archi; // lista archi incidenti
	int color;
}nodo;

typedef struct arco_struct {
	elem_archi* pos; // pos. arco lista grafo
	nodo* from;
	nodo* to;
	elem_archi* frompos; // pos. arco nodo from
	elem_archi* topos; // pos. arco nodo to
}arco;

typedef struct elem_lista_nodi {
	struct elem_lista_nodi* prev;
	struct elem_lista_nodi* next;
	nodo* info;
}elem_nodi; // elemento di una lista di nodi

typedef struct elem_lista_archi {
	struct elem_lista_archi* prev;
	struct elem_lista_archi* next;
	arco* info;
}elem_archi; // elemento di una lista di archi

typedef struct {
	int numero_nodi;
	int numero_archi;
	elem_archi* archi; // lista degli archi
	elem_nodi* nodi; // lista dei nodi
}grafo;




/****************FUNZIONI GRAFI**************/



/*semplice visita di un grafo*/
/*questo non distingue i sottografi*/
void dfs_ric (nodo* n) {
	n->color=1;		//marco il nodo come visitato
	elem_archi* la =n->archi;
	while(la!=NULL) {
		nodo* altro_nodo= la->info->from;
		if(altro_nodo==n)
			altro_nodo = la->info->to;
		if(altro_nodo->color==0)
			dfs_ric(altro_nodo);
		la=la->next;
	}
}



/* visita di un grafo e la coloro*/
/*quella che usiamo sempre o almeno lo usi al posto di quello sopra*/
void dfs_ric_colora (nodo* n,int c) {
	n->color=c; 		//marco il nodo come visitato
	elem_archi* la=n->archi;
	while(la!=NULL) {
		nodo* altro_nodo = la->info->from;
		if(altro_nodo==n)
			altro_nodo=la->info->to;
		if(altro_nodo->color==0)
			dfs_ric_colora(altro_nodo,c);
		la=la->next;
	}
}



/*funzione che conta i nodi di un grafo*/
int dfs_conta (nodo* n) {
	int cont=1;
	n->color=1;
	elem_archi* la = n->archi;
	while(la!=NULL) {
		nodo* altro_nodo = la->info->from;
		if(altro_nodo==n)
			altro_nodo = la->info->to;
		if(altro_nodo->color==0)
			cont= cont+dfs_conta(altro_nodo);
		la=la->next;
	}
	return cont;
}


/*ho scritto grafo* g anche se il tipo su telegram ha scritto grafo_oggetti quindi boh*/
/*funzione che colora tutti i grafi a zero*/
void dfs_grafo_oggetti (grafo* go, nodo* n) {
	elem_nodi* ln=go->nodi;
	while(ln!=NULL) {
		ln->info->color=0;
		ln=ln->next;
	}
	if(go->numero_nodi==0)
		return;
	dfs_ric(n);
}



/*numeri componeti connesse ad un grafo ad oggetti*/
int num_componeti_connesse_grafo_oggetti (grafo* go) {
	int comp_connesse=0;
	elem_nodi* ln= go->nodi;
	while(ln!=NULL) {
		ln->info->color=0;		//coloro tutto di zero
		ln=ln->next;
	}
	ln=go->nodi;
	while(ln!=NULL) {
		if(ln->info->color==0) {	//trovato un nodo smarcato
			comp_connesse= comp_connesse + 1;
			dfs_ric(ln->info);
		}
		ln=ln->next;
	}
	return comp_connesse;
}



/*numero componeti uguali su un grafo ad oggetti*/
int componeti_uguali (grafo* go) {
	int comp_connesse=0;
	elem_nodi*ln=go->nodi;
	while(ln!=NULL) {
		ln->info->color=0;		//coloro tutto di zero
		ln=ln->next;
	}
	ln=go->nodi;
	while(ln!=NULL) {
		if(ln->info->color==0) {//trovato un modo smarcato
			comp_connesse=comp_connesse+1;
			dfs_ric_colora(ln->info,comp_connesse);
		}
		ln=ln->next;
	}
	int* dim=(int)*calloc(comp_connesse+1,sizeof(int));
	ln=go->nodi;
	while(ln!=NULL) {
		dim[ln->info->color]++;
		ln=ln->next;
	}
	int j;
	for(j=2; j<=comp_connesse; j++) {
		if(dim[j] != dim[1]) {
			free(dim);
			return 0; 		//trova una componete connessa di dimensione diversa dalla prima
		}
	}
	free(dim);
	return 1;
}



/*funzione che trova il componente piu grande del grafo*/
int componente_max (grafo* g) {
	int max_nodi=0; 	//nodi della componente massima
	elem_nodi* ln=g->nodi;
	while(ln !=NULL) {
		ln->info->color=0;	//coloro tutto di 0
		ln=ln->next;
	}
	ln=g->nodi;
	while(ln!=NULL) {
		if(ln->info->color==0) {//ho trovato un nodo non visitato
			int cur_nodi=dfs_conta(ln->info);
			if(cur_nodi>max_nodi)
				max_nodi=cur_nodi;
		}
		ln=ln->next;
	}
	return max_nodi;
}



/*funzione che trova il componente piu piccola del grafo*/
int componete_min (grafo* g) {
	elem_nodi* ln=g->nodi;
	while(ln!=NULL) {
		ln->info->color=0; //colora tutto di 0
		ln=ln->next;
	}
	int min_nodi=g->numero_nodi;		//piu di cosi non si puo
	ln=g->nodi;
	while(ln!=NULL) {
		if(ln->info->color==0) {
			int cur_nodi=dfs_conta(ln->info);
			if(cur_nodi<min_nodi)
				min_nodi=cur_nodi;
		}
		ln=ln->next;
	}
	return min_nodi;
}


int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}
