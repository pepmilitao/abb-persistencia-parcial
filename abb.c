#include <stdio.h>
#include "abb.h"

void incluirNo (No* raiz, int key) {
    
    if (key <= raiz->key) {
        
        if (raiz->esq == NULL) {
            // TODO: criar e incluir novo nó
        } else {
            return incluirNo (raiz->esq, key);

        }
    } else {
        
        if (raiz->dir == NULL) {
            // TODO: criar e incluir novo nó
        } else {
            return incluirNo (raiz->dir, key);

        }
    }
}

void remocaoNo (No* raiz, int key) {

    if (key < raiz->key) {

        if (raiz->esq != NULL) {
            return remocaoNo (raiz->esq, key);

        } else {
            return;
        }
    } else if (key > raiz->key) {
        
        if (raiz->dir != NULL) {
            return remocaoNo (raiz->dir, key);

        } else {
            return;
        }
    } else {
        // TODO: lógica para remoção de nó
    }
}
