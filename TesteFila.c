#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no *prox;
}No;

typedef struct fila{
    No *ini;
    No *fim;
}Fila;

typedef struct pilha{
    No *topo;
}Pilha;

Pilha* criarPilha(){
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void Push(Pilha *p, int info){
    No *novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->prox = p->topo;
    p->topo = novo;
}

int pop(Pilha *p){
    No *aux = p->topo;
    int info = aux->info;
    p->topo = aux->prox;
    free(aux);
    return info;
}

void liberarPilha(Pilha *p){
    while(p-> topo != NULL){
        pop(p);
    }
    free(p);
}

Fila* criarFila(){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void inserirFila(Fila *f, int info){
    No *novo = (No*)malloc(sizeof(No));
    novo->info = info;
    novo->prox = NULL;
    if(f->fim != NULL){
        f->fim->prox = novo;
    }else{
        f->ini = novo;
    }
    f->fim = novo;
}

int removerFila(Fila *f){
    No *aux = f->ini;
    int info = aux->info;
    f->ini = aux->prox;
    if(f->ini == NULL){
        f->fim = NULL;
    }
    free(aux);
    return info;
}

void imprimirFila(Fila *f){
    No *aux = f->ini;
    while(aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

void liberarFila(Fila *f){
    No *aux = f->ini;
    while(aux != NULL){
        No *aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(f);
}

int qntdPar(Fila *f){
    int cont = 0;
    No *aux = f->ini;
    while(aux != NULL){
        if(aux->info % 2 == 0){
            cont++;
        }
        aux = aux->prox;
    }
    return cont;
}

Fila* removerInfo(Fila *f, int info){
    Fila *f2 = criarFila();
    No *aux = f->ini;
    while(aux != NULL){
        if(aux->info != info){
            inserirFila(f2, aux->info);
        }
        aux = aux->prox;
    }
    // exclui a fila original e o no que ficou nela que queriamos remover
    liberarFila(f);
    return f2;
}

Fila* splitPares_Impares(Fila* f){
    //f2 - pares, f3 - impares
    Fila *f2 = criarFila();
    Fila *f3 = criarFila();
    while(f->ini != NULL){
        int info = removerFila(f);
        if(info % 2 == 0){
            inserirFila(f2, info);
        }else{
            inserirFila(f3, info);
        }
    }
    // retornando os impares para a fila original
    while(f3->ini != NULL){
        inserirFila(f, removerFila(f3));
    }
    free(f3);
    return f2;
}
Fila* inverteFila(Fila* f){
    Pilha *p = criarPilha();
    while(f->ini != NULL){
        Push(p, removerFila(f));
    }
    while(p->topo != NULL){
        inserirFila(f, pop(p));
    }
    liberarPilha(p);
    return f;
}




int main(){
    Fila *f = criarFila();
    inserirFila(f, 1);
    inserirFila(f, 2);
    inserirFila(f, 3);
    inserirFila(f, 4);
    inserirFila(f, 5);
    inserirFila(f, 6);
    inverteFila(f);
    imprimirFila(f);
    liberarFila(f);
    return 0;
}