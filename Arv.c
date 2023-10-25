#include <stdio.h>
#include <stdlib.h>

typedef struct NoArv{
    int info;
    struct NoArv *esq;
    struct NoArv *dir;
}NoArv;

typedef struct Arv{
    NoArv *raiz;
}Arv;

// vazia arvore
int vaziaArvore(Arv* a){
    if(a->raiz == NULL){
        return 1;
    }else{
        return 0;
    }
}

//Inserir no na arvore

void inserirArvore(Arv* a,int info){
    NoArv* n = (NoArv*)malloc(sizeof(NoArv));
    n->info = info;
    n->esq = NULL;
    n->dir = NULL;
    if(!a->raiz){
        a->raiz = n;
    }else{
        // percorrer a arvore
        NoArv* monkey = a->raiz; // Auxilaiar que percoree a arvore
        int flag = 0;
        while(flag == 0){
            // se o valor do no for menor que o valor do no atual
            if(n->info < monkey->info){
                // se o no da esquerda for nulo, insere o no
                if(monkey->esq == NULL){
                    monkey->esq = n;
                    flag = 1;
                }else{
                    // se nao, continua percorrendo a arvore
                    monkey = monkey->esq;
                }
            // se o valor do no for maior que o valor do no atual
            }else{
                // se o no da direita for nulo, insere o no
                if(monkey->dir == NULL){
                    monkey->dir = n;
                    flag = 1;
                }else{
                    // se nao, continua percorrendo a arvore
                    monkey = monkey->dir;
                }
            }
        }
    }    
}

// criar arvore
Arv* criarArvore(){
    Arv* a = (Arv*)malloc(sizeof(Arv));
    a->raiz = NULL;
    return a;
}

// buscar no na arvore
int buscarArvore(Arv* a, int info){
    // percorrer a arvore. se encontrar, retorna 1, se nao encontrar, retorna 0
    if(!a->raiz){
        return 0;
    }else{
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(!flag){
            if(info == monkey->info){
                return 1;
            }else if(info < monkey->info){
                // se o no da esquerda for nulo, retorna 0
                if(monkey->esquerda == NULL){
                    return 0;
                }else{
                    monkey = monkey->esquerda;
                }
            }else{
                // se o no da direita for nulo, retorna 0
                if(monkey->direita == NULL){
                    return 0;
                }else{
                    monkey = monkey->direita;
                }
            }
        }
    }
}

// imprimir arvore
void imprimirArvorePre(NoArv* n){
    if(n != NULL){
        printf("%d ", n->info);
        imprimirArvorePre(n->esquerda);
        imprimirArvorePre(n->direita);
    }
}

void imprimirArvoreIn(NoArv* n){
    if(n != NULL){
        imprimirArvoreIn(n->esquerda);
        printf("%d ", n->info);
        imprimirArvoreIn(n->direita);
    }
}

void imprimirArvorePos(NoArv* n){
    if(n != NULL){
        imprimirArvorePos(n->esquerda);
        imprimirArvorePos(n->direita);
        printf("%d ", n->info);
    }
}

// liberar arvore
void esvaziarArvore(NoArv* n){
    if(!n){
        esvaziarArvore(n->esquerda);
        esvaziarArvore(n->direita);
        free(n);
    }
}

void liberarArvore(Arv* a){
    esvaziarArvore(a->raiz);
    free(a);
}
// remover no da arvore
// ao remover um no de uma arvore temos que analisar tres casos, o no é uma folha (caso simples), o no tem um filho (caso simples) o filho toma 
// o lugar do pai
// no tem dois filhos (caso complexo), o maior descendente da subarvore esquerda toma o lugar do no removido ou o menor descendente da subarvore direita toma o lugar do no removido

void removerArvore(Arv* a, int info){
    // procurar o no a ser removido, retornar um int para identificar as seguintes coisas:
    // -1 - Arvore vazia
    // 0 - no nao encontrado
    // 1 - no encontrado e removido
    if(!a->raiz){
        return -1;
    }else{
        NoArv* ant = NULL;
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(!flag){
            if(info == monkey->info){
                flag 1;
            }else if(info < monkey->info){
                // se o no da esquerda for nulo, retorna 0
                if(monkey->esquerda == NULL){
                    return 0;
                }else{
                    ant = monkey;
                    monkey = monkey->esquerda;
                }
            }else{
                // se o no da direita for nulo, retorna 0
                if(monkey->direita == NULL){
                    return 0;
                }else{
                    ant = monkey;
                    monkey = monkey->direita;
                }
            }
        }
    }
    // caso 1 - no folha
    if(monkey->esq == NULL && monkey->dir == NULL){
        if(monkey == a){
            a->raiz = NULL;
        }
        free(monkey);
        return 1;
    // caso 2 - no com um filho na esquerda
    }else if(monkey->esq != NULL && monkey->dir == NULL){
        if(ant->esq == monkey){
            ant->esq = monkey->esq;
        }else{
            ant->dir = monkey->esq;
        }
        free(monkey);
        return 1;
    // caso 2 - no com um filho na direita
    }else if(monkey->esq == NULL && monkey->dir != NULL){
        if(ant->esq == monkey){
            ant->esq = monkey->dir;
        }else{
            ant->dir = monkey->dir;
        }
        free(monkey);
        return 1;
    // caso 3 - no com dois filhos
    }else{

    }
        


}



int main(){
    Arv* a = criarArvore();
    inserirArvore(a, 10);
    inserirArvore(a, 5);
    inserirArvore(a, 15);
    inserirArvore(a, 3);
    imprimirArvore(a->raiz);
    return 0;

}
