#include <stdio.h>
#include "abb.h"

struct Versao {
    int ver;
    char campo[3];
    No* valor_anterior;
};

struct No {
    int key;
    No* esq;
    No* dir;
    No* pai;
    Versao mods[6];
    int i;
};

struct Memoria {
    int ver;
    No arvore[100];
    No raizes[20];
    int tamanho_arvore;
    int tamanho_raizes;
};

int achaVersao (No* no, int* ver) {
    
}

void incluirNo (Memoria* mem, No* raiz, int key, int* ver) {
    
    if (key <= raiz->key) {
        
        if (raiz->esq == NULL) {

            // Criar nó na memória
            mem->arvore[mem->tamanho_arvore++] = (No) {
                .key = key,
                .pai = raiz,
                .i = 0
            };

            // Verifica se há espaço no vetor de modificações
            // Se não houver mais espaço um novo nó raiz deve ser criado
            if (raiz->i <= 6) {

                // Registar modificação
                raiz->mods[raiz->i++] = (Versao) {*ver, "esq", raiz->esq};
                // Ligar novo nó no nó raiz
                raiz->esq = &mem->arvore[mem->tamanho_arvore];

            } else {
                
                // Corrigir nó raiz recursivamente
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
