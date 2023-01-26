#include <stdio.h>


/* Funzione di ordinamento, implementa il SELECTION SORT */
void selection_sort(int* A, int lung){
    /* Scorri la sequenza a partire dall'i-esimo elemento */
    for(int i=0; i<lung-1; i++){
        int min = i;
        /* Confronta l'i-esimo elemento con i successivi */
        for(int j=i+1; j<lung; j++){
            /* L'elemento corrente j è minore del i-esimo? */
            if(A[j]<A[min])
                min = j;    // aggiorna il min all'indice i-esimo
            // Altrimenti non fare nulla
        }
        /* Hai visitato tutte gli elementi della seconda sottosequenza */
        /* Fai lo scambio */
        int temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

/* Funzione di ordinamento, implementa l'INSERTION SORT */
void insertion_sort(int* A, int lung){
    /* Scorri la sequenza a partire dall'i-esimo elemento */
    for(int i=0; i<lung; i++){
        int key = A[i];
        int j = i-1;    // j è il precedente del corrente i-esimo
        /* Confronta la key con i precedenti */
        while(j>-1 && A[j]>key){    // fintanto che j è maggiore di -1 e l'elemento precedente è maggiore di quello corrente
            A[j+1] = A[j]; // Se l'elemento precedente (j) è > di quello corrente (j+1) scambiali
            j = j-1;    // decrementa j e passa al precedente del precedente
        }
        /* Sei uscito dal while, quindi hai fatto tutti i confronti */
        A[j+1] = key;   // la chiave (elemento corrente) va al posto attuale
    }
}

/* Funzione di ordinamento, implementa BUBBLE SORT */
void bubble_sort(int* A, int lung){
    int passata = 1;
    int elemento = lung-1;  // ultimo elemento non ordinato
    /* Scorri tutta la sequenza fintanto che fai passate valide */
    while(elemento>0 && passata){
        /* fai una passata */
        for(int i=0; i<elemento; i++)
            /* L'elemento successivo a quello corrente è minore di quello corrente? */
            if(A[i+1] < A[i]){
                int temp = A[i];
                A[i] = A[i+1];
                A[i+1] = temp;
                passata = 1;
            }
        elemento--; // decrementa, hai ordinato un elemento
    }
}

/* Funzione di ordinamento, implementa MERGE SORT - RICORSIVO */
void merge_sort(int* A, int p, int r){
    /* Fintanto che p < q trova un punto a metà della sequenza da dividere in 2, quando p == q allora il vettore è di dimensione 1 
     * quindi quando il vettore è di dimensione 1 inizia la fusione */
    if(p<r){
        /* dividi l'Array in 2 parti */
        int punto_medio = (p+r)/2;
        merge_sort(A, p, punto_medio);   // vettore della prima metà da p ad m
        merge_sort(A, punto_medio+1, r);   // vettore della seconda metà da m+1 a q
        merge(A, p, punto_medio, r);    // fusione delle due sottosequenze
    }
}

void merge(int* A, int p, int p_m, int r){
    // p_m sarebbe 'q' ossia il punto medio nell'Array
    int n1 = p_m - p + 1;   // lunghezza prima parte della sequenza
    int n2 = r - p_m;       // lunghezza seconda parte della sequenza
    /* Crea due Array: L[0..n1] e R[0..n2] */
    int L[n1], R[n2];
    /* Scorri tutto il primo Array L */
    for(int i=0; i<n1; i++)
        L[i] = A[p+i];  // copia la prima sequenza
    /* Scorri tutto il secondo Array R */
    for(int j=0; j<n2; j++)
        R[j] = A[p_m+j+1];  // copia la seconda sequenza
    /* iteratori per i due array + iteratore k per la fusione */
    int i, j, k;
    i = 0;  // iteratore per array L
    j = 0;  // iteratore per array R
    k = p;
    /* Scorri l'array per fare la fusione */
    while(i<n1 && j<n2){
        /* Se l'elemento corrente della 1° seq è minore o uguale dell'elem della 2° seq */
        if(L[i] <= R[j]){
            A[k] = L[i];    // metti nell'array di fusione l'elemento minore corrente della prima sequenza
            i++;
        }else{  // altrimenti l'elemento corrente della 1° seq è maggiore dell'elemento corrente della 2° seq
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

/* Funzione di ordinamento, implementa il QUICK SORT */
// Forward declaration
int scambia(int* A, int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    
    return temp;
}

// Forward declaration
int partition(int* A, int p, int r){
    int i = p;  // i è il primo elemento > di A[r] = pivot
    /* Scorri l'array */
    for(int j=p; j<r; j++){
        /* Se l'elemento corrente con indice j è minore uguale del pivot */
        if(A[j]<=A[r])
            scambia(A, i, j);   // scambiali
    }
    scambia(A, i, r);   // il pivot va al centro
    return i;   // ritorna la posizione del pivot
}

void quick_sort(int* A, int p, int r){
    if(p<r){
        int p_m = partition(A, p, r);
        quick_sort(A, p, p_m-1);    // sulla prima metà dell'Array
        quick_sort(A, p_m+1, r);    // sulla seconda metà dell'Array
    }
}

int main(int argc, char **argv)
{
	int lung;   // Dimensione dell'array
    /* Leggi quanti interi si vuole inserire */
    printf("\nQuanti interi vuoi introdurre?\n");
        scanf("%d", &lung);
        
    int A[lung];    // Dichiarazione array 'A'
    /* Leggi quali interi si vuole inserire */
    for(int i=0; i<lung; i++){
        printf("Inserisci il %d%c intero: ", i+1, 167);
        scanf("%d", &A[i]);
    }
    
    printf("\nSelection sort\n");
    /* Invocazione funzione selection sort */
    selection_sort(A, lung);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
    
    printf("\nInsertion sort\n");
    /* Invocazione funzione insertion sort */
    insertion_sort(A, lung);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
    
    printf("\nBubble sort\n");
    /* Invocazione funzione bubble sort */
    bubble_sort(A, lung);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
    
    printf("\nMerge sort\n");
    /* Invocazione funzione merge sort */
    merge_sort(A, 0, lung-1);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
    
    printf("\nQuick sort\n");
    /* Invocazione funzione quick sort */
    quick_sort(A, 0, lung-1);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
}
