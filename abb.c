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
    no->mod_ver = -1;
    no->mod_campo = 'n';
    no->mod_valor = NULL;
    return no;
}

void timeMachine (No* raiz, No** esq, No** dir, int ver) {

    if (raiz == NULL) return;

    *esq = raiz->esq;
    *dir = raiz->dir;

    if (raiz->mod_valor != NULL && raiz->mod_ver != -1 && raiz->mod_ver <= ver) {
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
    if (raiz->mod_valor == NULL) {
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

    if (raiz == NULL) return criaNo(key, NULL, NULL);
    
    No* esq;
    No* dir;
    timeMachine(raiz, &esq, &dir, ver);

    // Caso em que a árvore está vazia
    if (key <= raiz->key)
        return ligaNo (raiz, incluirNo(esq, key, ver), 'e', ver);
    return ligaNo (raiz, incluirNo(dir, key, ver), 'd', ver);
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
        printf("Chave %d Esq %p Dir %p ", raiz->key, raiz->esq, raiz->dir);
        printf("Mod ver %d Mod campo %c Mod valor %p\n", raiz->mod_ver, raiz->mod_campo, raiz->mod_valor);
        imprimeArvore (dir, ver, prof + 1);
    }
}
