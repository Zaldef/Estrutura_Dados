#include <stdio.h>
#include <stdlib.h>

typedef struct NoArv{
    struct  NoArv* e;
    int info;
    struct NoArv* d;
}NoArv;

typedef struct{
    NoArv* raiz;
}Arv;

Arv* criarArvore(){
    Arv* a = (Arv*) malloc(sizeof(Arv));
    a->raiz = NULL;
    return a;
}

int vaziaArvore(Arv* a){
    return (a->raiz == NULL);
}

void liberarArvore(NoArv* n){
    if(n != NULL){
        liberarArvore(n->e);
        liberarArvore(n->d);
        free(n);
    }
}

Arv* inserirArvore(Arv* a, NoArv* n){
    if(vaziaArvore(a)){
        a->raiz = n;
    }else{
        // percorrer a arvore
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(flag == 0){
            // se o valor do no for menor que o valor do no atual
            if(n->info < monkey->info){
                // se o no da esquerda for nulo, insere o no
                if(monkey->e == NULL){
                    monkey->e = n;
                    flag = 1;
                }else{
                    // se nao, continua percorrendo a arvore
                    monkey = monkey->e;
                }
            // se o valor do no for maior que o valor do no atual
            }else{
                // se o no da direita for nulo, insere o no
                if(monkey->d == NULL){
                    monkey->d = n;
                    flag = 1;
                }else{
                    // se nao, continua percorrendo a arvore
                    monkey = monkey->d;
                }
            }
        }
    }
    // retorna a arvore
    return a;
}

NoArv* criarNo(int info){
    NoArv* n = (NoArv*) malloc(sizeof(NoArv));
    n->info = info;
    n->e = NULL;
    n->d = NULL;
    return n;
}

int buscarArvore(Arv* a, int info){
    // percorrer a arvore. se encontrar, retorna 1, se nao encontrar, retorna 0
    if(vaziaArvore(a)){
        return 0;
    }else{
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(!flag){
            if(info == monkey->info){
                return 1;
            }else if(info < monkey->info){
                // se o no da esquerda for nulo, retorna 0
                if(monkey->e == NULL){
                    return 0;
                }else{
                    monkey = monkey->e;
                }
            }else{
                // se o no da direita for nulo, retorna 0
                if(monkey->d == NULL){
                    return 0;
                }else{
                    monkey = monkey->d;
                }
            }
        }
    }
}

void imprimirArvorePre(NoArv* n){
    if(n != NULL){
        printf("%d ", n->info);
        imprimirArvorePre(n->e);
        imprimirArvorePre(n->d);
    }
}

void imprimirArvoreIn(NoArv* n){
    if(n != NULL){
        imprimirArvoreIn(n->e);
        printf("%d ", n->info);
        imprimirArvoreIn(n->d);
    }
}

void imprimirArvorePos(NoArv* n){
    if(n != NULL){
        imprimirArvorePos(n->e);
        imprimirArvorePos(n->d);
        printf("%d ", n->info);
    }
}

int qntdNosInternosArvore(NoArv* n){
    int qntd = 0;
    if(n->e != NULL && n->d != NULL){
        qntd += 1;    
    }
    if(n->e != NULL){
        qntd += qntdNosInternosArvore(n->e);
    }
    if(n->d != NULL){
        qntd += qntdNosInternosArvore(n->d);
    }
    return qntd;
}




int main(){
    Arv* a = criarArvore();
    a = inserirArvore(a,criarNo(5));
    a = inserirArvore(a,criarNo(10));
    a = inserirArvore(a,criarNo(3));
    a = inserirArvore(a,criarNo(4));
    a = inserirArvore(a,criarNo(7));
    a = inserirArvore(a,criarNo(1));
    a = inserirArvore(a,criarNo(2));
    imprimirArvoreIn(a->raiz);
    printf("\n Quantidade de nos: %d", qntdNosInternosArvore(a->raiz));
    liberarArvore(a->raiz);

    return 0;
}