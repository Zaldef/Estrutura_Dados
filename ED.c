#include <stdlib.h>
#include <stdio.h>

struct no{
    int info;
    struct no* next;
};
typedef struct no Lista;

Lista* Inicializa(void);
Lista* Insere(Lista* A, int valor);
Lista* Remove(Lista* A);
void Impressao(Lista* A);
int vazia(Lista* A);

int main(){
    Lista *inicio;
    int a;
    inicio = Inicializa();
    Impressao(inicio);
    a = vazia(inicio);
    printf("\n%d\n",a);
    inicio = Inicializa();
    inicio = Insere(inicio, 73);
    inicio = Insere(inicio, 82);
    Impressao(inicio);
    a = vazia(inicio);
    printf("\n%d\n",a);

    return 0;
}

Lista* Inicializa(void){
    return NULL;
}

Lista* Insere(Lista* A, int valor){
    Lista *novo;
    novo = (Lista*)malloc(sizeof(Lista));
    novo->info = valor;
    novo->next = A;
    return novo;
}

Lista* Remove(Lista* A){
    Lista *aux;
    aux = A->next;
    free(A);
    return aux;
}

void Impressao(Lista* A){
    for (A; A != NULL; A = A->next){
        printf("\nend = %X\ninfo = %d\nnext = %X\n",A, A->info, A->next);
    }
}

int vazia (Lista* A){
 return (A == NULL);
}
