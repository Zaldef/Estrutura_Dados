#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no *prox;
}No;

typedef struct pilha{
    No* Topo;
}Pilha;

// Cria uma pilha vazia
Pilha* CriarPilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->Topo = NULL;
    return p;
}

// retorna se a fila esta vazia, 1 se sim, 0 se nao
int VaziaPilha(Pilha* p){
    return p->Topo == NULL;
}

// insere um elemento no topo da pilha
void Push(Pilha* p, int i){
    No* n = (No*)malloc(sizeof(No));
    n->info = i;
    n->prox = p->Topo;
    p->Topo = n;
}

// remove um elemento do topo da pilha
int Pop(Pilha* p){
    if(VaziaPilha(p)){
        printf("Pilha vazia\n");
        return -1;
    }
    int i = p->Topo->info;
    No* n = p->Topo;
    p->Topo = p->Topo->prox;
    free(n);
    return i;
}

// retorna a informação do elemento do topo da pilha
int Top(Pilha* p){
    if(VaziaPilha(p)){
        printf("Pilha vazia\n");
        return -1;
    }
    return p->Topo->info;
}

// libera a pilha
void LiberarPilha(Pilha* p){
    No* n = p->Topo;
    while(n != NULL){
        No* t = n->prox;
        free(n);
        n = t;
    }
    free(p);
}

// imprime a pilha
void ImprimirPilha(Pilha* p){
    No* n = p->Topo;
    while(n != NULL){
        printf("%d\n", n->info);
        n = n->prox;
    }
}

// desempilhara uma pilha na outra e retorna a pilha invertida
Pilha* InvertePilha(Pilha* p){
    Pilha* aux = CriarPilha();
    while(!VaziaPilha(p)){
        Push(aux, Pop(p));        
    }
    free(p);
    return aux;
}

int Soma_Par_Pilha(Pilha* p){
    int soma = 0;
    No* n = p->Topo;
    while(n != NULL){
        if(n->info % 2 == 0){
            soma += n->info;
        }
        n = n->prox;
    }
    return soma;
}

// apaga todas as ocorrencias de um elemento na pilha
Pilha* Apagar_Info_Pilha(Pilha* p, int info){
    Pilha* aux = CriarPilha();
    while(!VaziaPilha(p)){
        if(Top(p) != info){
            Push(aux, Pop(p));
        }else{
            Pop(p);
        }
    }
    free(p);
    return aux;
}

// Conta quantos elementos tem na pilha
int Qntd_Pilha(Pilha* p){
    Pilha* aux = CriarPilha();
    int cont = 0;
    // desempilha todos os elementos para uma pilha auxiliar e vai contando
    while(!VaziaPilha(p)){
        Push(aux, Pop(p));
        cont++;
    }
    // devolve os elementos para a pilha original
    while(!VaziaPilha(aux)){
        Push(p, Pop(aux));
    }
    free(aux);
    return cont;
}

// retorna 0 se as pilhas possuem o mesmo tamanho, 1 se p1 > p2 e 2 se p1 < p2
int CompararPilhasTamanho(Pilha* p1, Pilha* p2){
    if(Qntd_Pilha(p1) == Qntd_Pilha(p2)){
        return 0;
    }else if(Qntd_Pilha(p1) > Qntd_Pilha(p2)){
        return 1;
    }else{
        return 2;
    }
}

Pilha* Digitos(Pilha* p, int n){
    Pilha* aux = CriarPilha();
    while(n > 0){
        Push(aux, n % 10);
        n /= 10;
    }
    while(!VaziaPilha(aux)){
        Push(p, Pop(aux));
    }
    free(aux);
    return p;
}

int DigitosInverso(Pilha* p){
    Pilha* aux = CriarPilha();
    int n = 0;
    while(!VaziaPilha(p)){
        Push(aux, Pop(p));
    }
    while(!VaziaPilha(aux)){
        n = n * 10 + Pop(aux);
    }
    free(aux);
    return n;
}


int main(){
    Pilha* p1 = CriarPilha();
    Pilha* p2 = CriarPilha();
    p1 = Digitos(p1, 173);
    ImprimirPilha(p1);
    printf("Digito inverso: %d\n", DigitosInverso(p1));
    ImprimirPilha(p1);



    // ImprimirPilha(p);
    // p = InvertePilha(p);
    // printf("Pilha invertida:\n");
    // ImprimirPilha(p);
    // system("pause");
    // printf("Soma dos pares: %d\n", Soma_Par_Pilha(p));
    // p = Apagar_Info_Pilha(p, 6);
    // ImprimirPilha(p);
    // printf("Soma dos pares: %d\n", Soma_Par_Pilha(p));
    LiberarPilha(p1);
    LiberarPilha(p2);
    return 0;
}
