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
    return (a->raiz == NULL);
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
                if(monkey->esq == NULL){
                    return 0;
                }else{
                    monkey = monkey->esq;
                }
            }else{
                // se o no da direita for nulo, retorna 0
                if(monkey->dir == NULL){
                    return 0;
                }else{
                    monkey = monkey->dir;
                }
            }
        }
    }
}

// imprimir arvore
void imprimirArvorePre(NoArv* n){
    if(n != NULL){
        printf("%d ", n->info);
        imprimirArvorePre(n->esq);
        imprimirArvorePre(n->dir);
    }
}

void imprimirArvoreIn(NoArv* n){
    if(n != NULL){
        imprimirArvoreIn(n->esq);
        printf("%d ", n->info);
        imprimirArvoreIn(n->dir);
    }
}

void imprimirArvorePos(NoArv* n){
    if(n != NULL){
        imprimirArvorePos(n->esq);
        imprimirArvorePos(n->dir);
        printf("%d ", n->info);
    }
}

// liberar arvore
void esvaziarArvore(NoArv* n){
    if(!n){
        esvaziarArvore(n->esq);
        esvaziarArvore(n->dir);
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

int removerArvore(Arv* a, int info){
    // procurar o no a ser removido, retornar um int para identificar as seguintes coisas:
    // -1 - Arvore vazia
    // 0 - no nao encontrado
    // 1 - no encontrado e removido
    NoArv* ant = NULL;
    NoArv* monkey = a->raiz;

    if(!a->raiz){
        return -1;
    }else{
        int flag = 0;
        while(!flag){
            if(info == monkey->info){
                flag = 1;
            }else if(info < monkey->info){
                // se o no da esquerda for nulo, retorna 0
                if(monkey->esq == NULL){
                    return 0;
                }else{
                    ant = monkey;
                    monkey = monkey->esq;
                }
            }else{
                // se o no da direita for nulo, retorna 0
                if(monkey->dir == NULL){
                    return 0;
                }else{
                    ant = monkey;
                    monkey = monkey->dir;
                }
            }
        }
    }
    // caso 1 - no folha
    if(monkey->esq == NULL && monkey->dir == NULL){
        if(monkey == a->raiz){
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
        //monkey 2 vai ser o maior descendente da subarvore esquerda
        NoArv* monkey2 = monkey->esq;
        //ant2 vai ser o pai do maior descendente da subarvore esquerda
        NoArv* ant2 = monkey;
        // procurar o maior descendente da subarvore esquerda
        while(monkey2->dir != NULL){
            ant2 = monkey2;
            monkey2 = monkey2->dir;
        }
        // se o maior descendente da subarvore esquerda tiver um filho na esquerda
        if(monkey2->dir != NULL){
            ant2->dir = monkey2->esq;
        }else{
            ant2->dir = NULL;
        }
        // o maior descendente da subarvore esquerda toma o lugar do no removido
        monkey2->esq = monkey->esq;
        monkey2->dir = monkey->dir;
        if(ant != NULL){
            if(ant->esq == monkey){
            ant->esq = monkey2;
            }else{
            ant->dir = monkey2;
            }
        }
        
        free(monkey);
        return 1;
    }



}

int qntdNosArvore(NoArv* n){
    int qntd = 1;

    if(n == NULL){
        return 0;
    }

    if(n->esq != NULL){
        qntd += qntdNosArvore(n->esq);
    }
    if(n->dir != NULL){
        qntd += qntdNosArvore(n->dir);
    }
    return qntd;
}

int numeroDescendentes(Arv* a, int info){
    // retorna -2 se a arvore for vazia
    // retorna -1 se o no nao for encontrado
    // retorna o numero de descendentes se o no for encontrado
    if(!a->raiz){
        return -2;
    }else{
        NoArv* monkey = a->raiz;
        int flag = 0;
        int qntd = -1;
        while(!flag){
            if(info == monkey->info){
                return qntd_Descendentes(monkey, qntd);
            }else if(info < monkey->info){
                // se o no da esquerda for nulo
                if(monkey->esq == NULL){
                    return -1;
                }else{
                    monkey = monkey->esq;
                }
            }else{
                // se o no da direita for nulo
                if(monkey->dir == NULL){
                    return -1;
                }else{
                    monkey = monkey->dir;
                }
            }
        }
    }
}

// funcao auxiliar para contar o numero de descendentes
int qntd_Descendentes(NoArv* a, int i){
    if(a != NULL){
        i = qntd_Descendentes(a->esq,i);
        i = qntd_Descendentes(a->dir,i);
        i++;
    }
    return i;
}

// funcao para contar o numero de nos internos de uma arvore/subarvore
int qntd_Nos_Internos(NoArv* a, int i){
    if(a->esq != NULL || a->dir != NULL){
        i = qntd_Nos_Internos(a->esq,i);
        i = qntd_Nos_Internos(a->dir,i);
        i++;
    }
    return i;
}

int retorna_pai(Arv* a, int info){
    // retorna -1 se a arvore for vazia
    // retorna 0 se o no nao tiver pai
    // retorna -2 se o no nao for encontrado
    // retorna o valor do pai se o no for encontrado
    if(!a->raiz){
        return -1;
    }else{
        NoArv* dad_monkey = NULL;
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(!flag){
            if(info == monkey->info ){
                if(dad_monkey == NULL){
                    return 0;
                }else{
                    return dad_monkey->info;
                }
            }else if(info < monkey->info){
                // se o no da esquerda for nulo, retorna 0
                if(monkey->esq == NULL){
                    return -2;
                }else{
                    dad_monkey = monkey;
                    monkey = monkey->esq;
                }
            }else{
                // se o no da direita for nulo, retorna 0
                if(monkey->dir == NULL){
                    return -2;
                }else{
                    dad_monkey = monkey;
                    monkey = monkey->dir;
                }
            }
        }
    }
}

int menorValor(Arv* a){
    // retorna -1 se a arvore for vazia
    // retorna o menor valor se a arvore nao for vazia
    if(!a->raiz){
        return -1;
    }else{
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(!flag){
            if(monkey->esq == NULL){
                return monkey->info;
            }else{
                monkey = monkey->esq;
            }
        }
    }
}

int maiorValor(Arv* a){
    // retorna -1 se a arvore for vazia
    // retorna o maior valor se a arvore nao for vazia
    if(!a->raiz){
        return -1;
    }else{
        NoArv* monkey = a->raiz;
        int flag = 0;
        while(!flag){
            if(monkey->dir == NULL){
                return monkey->info;
            }else{
                monkey = monkey->dir;
            }
        }
    }
}




int main(){
    Arv* a = criarArvore();
    inserirArvore(a, 10);
    inserirArvore(a, 5);
    inserirArvore(a, 15);
    inserirArvore(a, 3);
    inserirArvore(a, 7);
    inserirArvore(a, 12);
    inserirArvore(a, 17);
    inserirArvore(a, 1);
    inserirArvore(a, 4);
    inserirArvore(a, 6);
    inserirArvore(a, 8);
    inserirArvore(a, 11);
    inserirArvore(a, 13);
    inserirArvore(a, 16);
    inserirArvore(a, 18);
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 15));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 10));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 5));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 17));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 18));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 16));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 13));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 12));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 11));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 8));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 7));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 6));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 4));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 3));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 1));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 2));
    imprimirArvoreIn(a->raiz);
    printf("\n Codigo de remocao: %d\n", removerArvore(a, 0));
    imprimirArvoreIn(a->raiz);

    return 0;
}
