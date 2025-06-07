#include <stdio.h>
#include <stdlib.h>
#include "abb.h"


// TODO: modificar variável mod por lista com 2 espaços (não é difícil, somente chato)

// Função que cria novo nó na memória e retorna o nó criado
No* criaNo (int key, No* esq, No* dir) {
    No* no = malloc(sizeof(struct No));
    if (no == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    no->key = key;
    no->esq = esq;
    no->dir = dir;
    no->mod_ver = 101;
    no->mod_campo = 'n';
    no->mod_valor = NULL;
    return no;
}

void timeMachine (No* raiz, No** esq, No** dir, int ver) {

    if (raiz == NULL) return;

    *esq = raiz->esq;
    *dir = raiz->dir;

    if (raiz->mod_ver <= ver) {
        if (raiz->mod_campo == 'e') *esq = raiz->mod_valor;
        if (raiz->mod_campo == 'd') *dir = raiz->mod_valor;
    }
}

// Função que recebe dois nós e liga-os, retornando a raiz da sub-arvore
No* ligaNo (No* raiz, No* add, char campo, int ver) {


    // Checa se a raiz é nula ou se add já está ligado na raiz
    if (raiz == NULL) return add;

    No* esq;
    No* dir;
    timeMachine (raiz, &esq, &dir, ver);

    if (esq == add || dir == add) return raiz;

    // Nesse caso, há espaço no buffer de modificações para anotar a modificação
    if (raiz->mod_ver == 101) {
        raiz->mod_ver = ver;
        raiz->mod_campo = campo;
        raiz->mod_valor = add;
        return raiz;
    }
    // Nesse caso não há, então é criado um nó com o nó "add" já ligado e com modificações feitas

    // No "add" será apontado pelo campo "esq" da nova raiz,
    // senão será apontado pelo campo "dir"
    if (campo == 'e') return criaNo (raiz->key, add, dir);
    if (campo == 'd') return criaNo (raiz->key, esq, add);
};

// Função recursiva que inclui nó na árvore binária de busca, retornando raiz da sub-árvore
No* incluirNo (No* raiz, int key, int ver) {

    // Caso em que a árvore está vazia
    if (raiz == NULL) return criaNo(key, NULL, NULL);
    
    No* esq;
    No* dir;
    timeMachine(raiz, &esq, &dir, ver);

    if (key <= raiz->key)
        return ligaNo (raiz, incluirNo(esq, key, ver), 'e', ver);
    return ligaNo (raiz, incluirNo(dir, key, ver), 'd', ver);
}

No* achaMinimo(No* raiz, int ver) {
    if (raiz == NULL) return NULL;

    No* esq;
    No* dir;
    while (raiz != NULL) {
        
        timeMachine(raiz, &esq, &dir, ver);
        if (esq == NULL) break;
        raiz = esq;
    }
    return raiz;
}

No* sucessorNo(No* raiz, int key, int ver) {
    
    if (raiz == NULL) return NULL;

    No* atual = raiz;
    No* candidato = NULL;
    No* esq;
    No* dir;

    while (atual != NULL) {
        
        timeMachine (atual, &esq, &dir, ver);
        if (key < atual->key) {
            candidato = atual;
            atual = esq;

        } else if (key > atual->key) {
            atual = dir;

        } else {
            if (dir != NULL) return achaMinimo (dir, ver);
            break;
        }
    }

    return candidato;
}

No* remocaoNo (No* raiz, int key, int ver) {
    
    // Caso em que a raiz é nula
    if (raiz == NULL) return NULL;
    
    // Procurando nó para retirar
    No* esq;
    No* dir;
    timeMachine(raiz, &esq, &dir, ver);

    if (key < raiz->key)      return ligaNo (raiz, remocaoNo (esq, key, ver), 'e', ver);
    else if (key > raiz->key) return ligaNo (raiz, remocaoNo (dir, key, ver), 'd', ver);
    else {
        
        // Nó sem filhos
        if (esq == NULL && dir == NULL) return NULL;

        // Nó com 1 filho
        if (esq == NULL) return dir;
        if (dir == NULL) return esq;

        // Nó com 2 filhos
        No* prox = achaMinimo (dir, ver);
        No* novoDir = remocaoNo (dir, prox->key, ver);
        return criaNo (prox->key, esq, novoDir);
    }
}

// Função que imprime valor e profundidade dos nós da árvore toda em ordem crescente na versão indicada
void imprimeArvore (No* raiz, int ver, int prof) {
    // Se a entrada for nula, então para-se a recursão
    if (raiz != NULL) {
        No* esq;
        No* dir;
        timeMachine (raiz, &esq, &dir, ver);
        imprimeArvore (esq, ver, prof + 1);
        printf("%i,%i ", raiz->key, prof);
        imprimeArvore (dir, ver, prof + 1);
    }
}
