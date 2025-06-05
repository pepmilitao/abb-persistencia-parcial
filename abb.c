#include <stdio.h>
#include <string.h>
#include "abb.h"

struct Versao {
    int ver;
    char campo[3];
    No* valor;
};

// TODO: modificar variável mod por lista com 2 espaços (não é difícil, somente chato)
struct No {
    int key;
    No* esq;
    No* dir;
    Versao mod;
};

struct Memoria {
    int ver;
    No arvore[100];
    No raizes[50];
    int tamanho_arvore;
    int tamanho_raizes;
};

// Função que cria novo nó na memória e retorna o nó criado
No* criaNo (Memoria* mem, int key, No* esq, No* dir) {

    mem->arvore[mem->tamanho_arvore++] = (No) {
        .key = key,
        .esq = esq,
        .dir = dir,
        .mod = {.valor = NULL}
    };
    return &mem->arvore[mem->tamanho_arvore];
}

No timeMachine (No* no, int ver) {

    // Versão da última modificação é anterior à versão desejada, senão o nó retornado é o original
    if (no->mod.ver < ver) {
        // Campo de modificação possui campo "esq", senão o campo de modifição é "dir"
        if (strcmp(no->mod.campo, "esq") == 0) {

            // Retorna nó com mesma chave e filho direito, mas com filho esquerdo modificado
            return (No) {
                .key = no->key,
                .esq = no->mod.valor,
                .dir = no->dir
            };
        } else {
            return (No) {
                .key = no->key,
                .esq = no->esq,
                .dir = no->mod.valor
            };
        }
    }
    return *no;
}

// Função que recebe dois nós e liga-os, retornando a raiz da sub-arvore
No* ligaNo (Memoria* mem, No* raiz, No* add, char campo[3], int* ver) {

    // Nesse caso, há espaço no buffer de modificações para anotar a modificação
    if (raiz->mod.valor == NULL) {
        raiz->mod.ver = *ver;
        strcpy(raiz->mod.campo, campo);
        raiz->mod.valor = add;
        return raiz;
    }
    // Nesse caso não há, então é criado um nó com o nó "add" já ligado e com modificações feitas
    
    // Devemos analisar o nó raiz com as alteraçõesda versão feitas
    No raiz_tm = timeMachine (raiz, *ver);

    // No "add" será apontado pelo campo "esq" da nova raiz, senão será apontado pelo campo "dir"
    if (strcmp("esq", campo) == 0) {
        return criaNo (mem, raiz->key, add, raiz_tm.dir);
    }
    return criaNo (mem, raiz->key, raiz_tm.esq, add);
}

// Função recursiva que inclui nó na árvore binária de busca, retornando raiz da sub-árvore
No* incluirNo (Memoria* mem, No* raiz, int key, int* ver) {
    No* add;
    No* ret;
    
    // Nó deve estar na sub-árvore esquerda
    if (key <= raiz->key) {

        // Encontrada posição do nó na árvore
        if (raiz->esq == NULL) {

            // Cria nó na memória...
            add = criaNo(mem, key, NULL, NULL);
            // ...e o liga na estrutura
            return ligaNo (mem, raiz, add, "esq", ver);

        }
        
        // Se não for encontrada a posição chamamos a recursão
        // Nesse caso, guardamos a raiz da sub-árvore esquerda
        ret = incluirNo (mem, raiz->esq, key, ver);

        // A raiz dessa sub-árvore mudou, então a modificação deve ser anotada
        if (ret != raiz->esq) {
            return ligaNo(mem, raiz, ret, "esq", ver);
        }

    } else {

        // Análogo
        if (raiz->dir == NULL) {
            add = criaNo(mem, key, NULL, NULL);
            return ligaNo (mem, raiz, add, "dir", ver);
        }
        ret = incluirNo (mem, raiz->dir, key, ver);
        if (ret != raiz->dir) {
            return ligaNo(mem, raiz, ret, "dir", ver);
        }

    }

    // Retornamos a raiz para analisar as sub-árvores esquerda e direita de cada nó
    return raiz;
}

void remocaoNo (No* raiz, int key) {

    if (key < raiz->key) {

        if (raiz->esq != NULL) {
            remocaoNo (raiz->esq, key);

        } else {
            return;
        }
    } else if (key > raiz->key) {
        
        if (raiz->dir != NULL) {
            remocaoNo (raiz->dir, key);

        } else {
            return;
        }
    } else {
        // TODO: lógica para remoção de nó
    }
}

// Função que imprime valor e profundidade dos nós da árvore toda em ordem crescente na versão indicada
void imprimeNo (No* raiz, int* ver, int prof) {

    // Visito primeiro o filho esquerdo na versão especificada
    No esq_tm = timeMachine (raiz->esq, *ver);
    imprimeNo (&esq_tm, ver, prof + 1);

    // Depois imprimo o valor do nó atual e a profundidade na versão especificada
    // Por fim visito o filho direito na versão especificada
}
