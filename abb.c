#include <stdio.h>
#include "abb.h"

struct Versao {
    int ver;
    char campo[3];
    No* valor;
};

struct No {
    int key;
    No* esq;
    No* dir;
    Versao mods[2];
    int i;
};

struct Memoria {
    int ver;
    No arvore[100];
    No raizes[50];
    int tamanho_arvore;
    int tamanho_raizes;
};

void incluirNo (Memoria* mem, No* raiz, int key, int* ver) {
    
    if (key <= raiz->key) {
        
        if (raiz->esq == NULL) {

            // Criar nó na memória
            mem->arvore[mem->tamanho_arvore++] = (No) {
                .key = key,
                .i = 0
            };
            
            // Se possível, registra modificação do campo, se não, cria cópia de nó
            if (raiz->i <= 1) {
                raiz->mods[raiz->i++] = (Versao) {*ver, "esq", raiz->esq};
            } else {

            }
        } else {
            incluirNo (mem, raiz->esq, key, ver);

        }
    } else {
        
        if (raiz->dir == NULL) {
            // TODO: criar e incluir novo nó
        } else {
            incluirNo (mem, raiz->dir, key, ver);

        }
    }
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
