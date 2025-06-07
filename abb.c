#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

No* criaNo (int key, No* esq, No* dir) {
    // Tenta alocar espaço na memória
    No* no = malloc(sizeof(struct No));
    if (no == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    // Se tudo der certo, atribuímos valores padrão para os nós
    no->key = key;
    no->esq = esq;
    no->dir = dir;
    // 101 é um valor padrão para a versão melhor que o -1 devido à implementação feita
    no->mod_ver = 101;
    no->mod_campo = 'n';
    no->mod_valor = NULL;
    return no;
}

void timeMachine (No* raiz, No** esq, No** dir, int ver) {
    // Raiz nula, então nada é feito
    if (raiz == NULL) return;
    // Se não houver mudanças no nó, os filhos esquerdo e direito serão os originais
    *esq = raiz->esq;
    *dir = raiz->dir;
    // Passa pelo buffer de modificações e se houver alguma, será atualizado
        if (raiz->mod_ver <= ver) {
            if (raiz->mod_campo == 'e') *esq = raiz->mod_valor;
            if (raiz->mod_campo == 'd') *dir = raiz->mod_valor;
    }
}

No* ligaNo (No* raiz, No* add, char campo, int ver) {
    // Checa se a raiz é nula ou se add já está ligado na raiz
    if (raiz == NULL) return add;
    // Realiza as possíveis modificações do nó
    No* esq;
    No* dir;
    timeMachine (raiz, &esq, &dir, ver);
    // Se o nó a ser adicionado já for filho da raiz, então nada deve ser feito
    if (esq == add || dir == add) return raiz;
    // Nesse caso, deve ser feita uma modificação e há espaço
    // no buffer de modificações para anotar a modificação
    if (raiz->mod_ver == 101) {
        raiz->mod_ver = ver;
        raiz->mod_campo = campo;
        raiz->mod_valor = add;
        return raiz;
    }
    // Nesse caso não há, então é criado um nó com o
    // nó "add" já ligado e com modificações feitas
    if (campo == 'e') return criaNo (raiz->key, add, dir);
    return criaNo (raiz->key, esq, add);
}

No* incluirNo (No* raiz, int key, int ver) {
    // Caso em que a árvore está vazia
    if (raiz == NULL) return criaNo(key, NULL, NULL);
    // Realiza as possíveis modificações do nó
    No* esq;
    No* dir;
    timeMachine(raiz, &esq, &dir, ver);
    // É buscada a posição para o nó com a chave designada
    if (key <= raiz->key)
        return ligaNo (raiz, incluirNo(esq, key, ver), 'e', ver);
    return ligaNo (raiz, incluirNo(dir, key, ver), 'd', ver);
}

No* achaMinimo(No* raiz, int ver) {
    // Raiz nula indica que não há nó mínimo
    if (raiz == NULL) return NULL;
    No* esq;
    No* dir;
    while (raiz != NULL) {
        // Realiza as possíveis modificações do nó
        timeMachine(raiz, &esq, &dir, ver);
        // Não há sub-árvore esquerda, então o elemento
        // encontrado até agora é o mínimo
        if (esq == NULL) break;
        // Se houver sub-árvore esquerda, então
        // deve-se buscar o mínimo dessa sub-árvore
        raiz = esq;
    }
    return raiz;
}

No* sucessorNo(No* raiz, int key, int ver) {
    // Raiz nula indica que não há sucessor
    if (raiz == NULL) return NULL;
    
    No* atual = raiz;
    No* candidato = NULL;
    No* esq;
    No* dir;

    while (atual != NULL) {
        // Realizamos as mudanças feitas no nó
        timeMachine (atual, &esq, &dir, ver);
        // Se o valor de entrada é menor que a chave do nó
        // analizado, então ele pode ser o nó sucessor, mas
        // um nó de chave menor que ele também pode
        if (key < atual->key) {
            candidato = atual;
            atual = esq;

        }
        // Senão, se o valor de entrada for maior que a chave do nó
        // analiado, então esse nó não pode ser o sucessor da chave
        // e deve-se analizar a sub-árvore direita
        else if (key > atual->key) {
            atual = dir;

        }
        // Caso contrário, o nó em análise possui chave igual à
        // entrada, logo o sucessor dessa entrada é a chave do nó
        // mínimo da sub-árvore direita
        else {
            if (dir != NULL) return achaMinimo (dir, ver);
            break;

        }
    }
    return candidato;
}

No* remocaoNo (No* raiz, int key, int ver) {
    // Caso em que a raiz é nula
    if (raiz == NULL) return NULL;
    // Realizando as modificações indicadas no buffer
    No* esq;
    No* dir;
    timeMachine(raiz, &esq, &dir, ver);
    // É feita a busca do nó, sempre ligando a raiz ao retorno da recursão
    if (key < raiz->key)      return ligaNo (raiz, remocaoNo (esq, key, ver), 'e', ver);
    else if (key > raiz->key) return ligaNo (raiz, remocaoNo (dir, key, ver), 'd', ver);
    // Aqui foi encontrado o nó com a chave desejada
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
        // Realiza-se as modificações indicadas
        No* esq;
        No* dir;
        timeMachine (raiz, &esq, &dir, ver);
        // Como queremos os valores em ordem crescente,
        // acessamos primeiro a sub-árvore esquerda,
        // depois imprimimos a chave e a profundidade
        // do nó raiz e por fim acessamos a sub-árvore direita
        imprimeArvore (esq, ver, prof + 1);
        printf("%i,%i ", raiz->key, prof);
        imprimeArvore (dir, ver, prof + 1);

    }
}
