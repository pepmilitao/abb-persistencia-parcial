#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#define MAX_VERSOES 100

Raiz raizes[MAX_VERSOES];
int r = 0;

No* getRaiz(int ver) {
    int esq = 0, dir = r - 1, mid;
    while (esq < dir) {
        mid = (esq + dir) / 2;
        if (raizes[mid].versao_max < ver)
            esq = mid + 1;
        else
            dir = mid;
    }
    return raizes[esq].raiz;
}

int main () {
    char op[3];
    No* raiz = NULL;
    int key, ver, act_raiz, act_ver = 0;
    No* ret;
    No* raiz_ret;

    raizes[r++] = (Raiz){raiz, 0};
    
    // Operação do programa
    while (act_ver < 100) {
        scanf("%s", op);
        if (strcmp(op, "INC") == 0) {
            scanf(" %d", &key);
            ++act_ver;
            ret = incluirNo (raiz, key, act_ver);

            if (ret != raiz) {
                raizes[r - 1].versao_max = act_ver - 1;
                raizes[r++] = (Raiz) {ret, act_ver};
                raiz = ret;
            } else {
                raizes[r - 1].versao_max = act_ver;
            }
        } else if (strcmp(op, "IMP") == 0) {
            // TODO: imprimir versão mais recente sem mencionar versão
            scanf(" %d", &ver);
            raiz_ret = getRaiz(ver);
            imprimeArvore (raiz_ret, ver, 0);
        } else if (strcmp(op, "REM") == 0) {
            scanf(" %d", &key);
            ++act_ver;
            ret = remocaoNo (raiz, key, act_ver);

            if (ret != raiz) {
                raizes[r - 1].versao_max = act_ver - 1;
                raizes[r++] = (Raiz) {ret, act_ver};
                raiz = ret;
            } else {
                raizes[r - 1].versao_max = act_ver;
            }
        } else if (strcmp(op, "SUC") == 0) {
            scanf(" %d %d", &key, &ver);
            raiz_ret = getRaiz(ver);
            ret = sucessorNo (raiz_ret, key, ver);
            if (ret != NULL) {
                printf("SUC %d %d\n%d", key, ver, ret->key);
            } else {
                printf("SUC %d %d\ninfinito", key, ver);
            }
        }
        printf("\n");
    }
    
    free(raiz);
    return 0;
}
