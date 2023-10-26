#include <stdio.h>
#include <stdlib.h>


typedef struct No{
    int info;
    struct No *prox;
}No;

typedef struct Lista{
    No *ini;
}Lista;

Lista* InicializaLista(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->ini = NULL;
    return l;
}

Lista* InsereLista(Lista* l, int info){
    No *novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->prox = l->ini;
    l->ini = novo;
    return l;
}

Lista* RemoverLista(Lista* l){
    No *aux = l->ini;
    l->ini = aux->prox;
    free(aux);
    return l;
}

void ImprimeLista(Lista* l){
    No *aux = l->ini;
    while(aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
}

int VaziaLista(Lista* l){
    return (l->ini == NULL);
}

int QntdLista(Lista* l){
    No *aux = l->ini;
    int cont = 0;
    while(aux != NULL){
        cont++;
        aux = aux->prox;
    }
    return cont;
}

int SomaLista(Lista* l){
    No* aux = l->ini;
    int soma = 0;
    while(aux != NULL){
        soma += aux->info;
        aux = aux->prox;
    }
    return soma;
}

void LiberaLista(Lista* l){
    No *aux = l->ini;
    while(aux != NULL){
        No *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(l);
}


Lista* UniaoLista(Lista* l1, Lista* l2) {
    Lista* l3 = InicializaLista();
    No* aux1 = l1->ini;
    No* aux2 = l2->ini;

    // Adiciona todos os elementos de l1 em l3
    while (aux1 != NULL) {
        if (!ExisteElemento(l3, aux1->info)) {
            InsereLista(l3, aux1->info);
        }
        aux1 = aux1->prox;
    }

    // Adiciona todos os elementos de l2 que não estão em l3
    while (aux2 != NULL) {
        if (!ExisteElemento(l3, aux2->info)) {
            InsereLista(l3, aux2->info);
        }
        aux2 = aux2->prox;
    }

    return l3;
}

int ExisteElemento(Lista* lista, int elemento) {
    No* aux = lista->ini;
    while (aux != NULL) {
        if (aux->info == elemento) {
            return 1; // Elemento encontrado na lista
        }
        aux = aux->prox;
    }
    return 0; // Elemento não encontrado na lista
}


int main(){
    Lista *l1 = InicializaLista();
    Lista *l2 = InicializaLista();
    Lista *l3 = InicializaLista();

    l1 = InsereLista(l1, 2);
    l1 = InsereLista(l1, 4);
    l1 = InsereLista(l1, 6);
    l1 = InsereLista(l1, 8);
    l1 = InsereLista(l1, 10);
    l1 = InsereLista(l1, 12);
    printf("Lista 1: ");
    ImprimeLista(l1);
    printf("\n");
    printf("Quantidade de nos na lista 1: %d",QntdLista(l1));
    printf("\nSoma dos nos da lista 1: %d",SomaLista(l1));

    printf("\n----------------------------------\n");

    l2 = InsereLista(l2, 3);
    l2 = InsereLista(l2, 6);
    l2 = InsereLista(l2, 9);
    l2 = InsereLista(l2, 12);
    l2 = InsereLista(l2, 15);
    l2 = InsereLista(l2, 18);
    printf("Lista 2: ");
    ImprimeLista(l2);
    printf("\n");
    printf("Quantidade de nos na lista 2: %d",QntdLista(l2));
    printf("\nSoma dos nos da lista 2: %d",SomaLista(l2));

    printf("\n----------------------------------\n");

    printf("Lista 3: ");
    l3 = UniaoLista(l1, l2);
    ImprimeLista(l3);
    printf("\n");
    printf("Quantidade de nos na lista 3: %d",QntdLista(l3));
    printf("\nSoma dos nos da lista 3: %d",SomaLista(l3));



    LiberaLista(l1);
    LiberaLista(l2);
    LiberaLista(l3);
    return 0;
}
