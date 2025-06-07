#include <stdio.h>
#include <string.h>
#include "abb.h"

// Array que guarda as raízes da árvore
Raiz raizes[50];
// Valor que representa a quantidade de raízes armazenadas
int r = 0;

// Função que faz uma busca binária para encontrar a raíz necessária para cada versão
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
    char op[3], linha[20];
    No* raiz = NULL;
    int args, key, ver, act_ver = 0;
    No* ret;
    No* raiz_ret;
    // Estado inicial da árvore
    raizes[r++] = (Raiz){raiz, 0};
    // Operação do programa
    while (act_ver < 100) {
        scanf("%s", op);
        // Operação de inserção de nó
        if (strcmp(op, "INC") == 0) {
            scanf(" %d", &key);
            // Inserção realizada e versão modificada
            ret = incluirNo (raiz, key, ++act_ver);
            // Se a raiz de retorno for outra, então ela deve ser
            // guardada no array de raízes, senão, então a versão
            // máxima encontrada até agora para essa raiz é a versão
            // atual
            if (ret != raiz) {
                // A versão máxima da última raiz foi a última versão
                raizes[r - 1].versao_max = act_ver - 1;
                // Nó de retorno é guardado
                raizes[r++] = (Raiz) {ret, act_ver};
                raiz = ret;
            } else {
                raizes[r - 1].versao_max = act_ver;
            }
        } else if (strcmp(op, "IMP") == 0) {
            // Lê restante da linha dada como entrada
            fgets(linha, sizeof(linha), stdin);
            // Tenta ler a versão que pode ter sido dada como entrada
            args = sscanf(linha, " %d", &ver);
            // Se não foi possível ler nenhum número, então usa-se a versão mais recente
            if (args != 1) ver = act_ver;
            raiz_ret = getRaiz(ver);
            printf("IMP %d\n", ver);
            imprimeArvore (raiz_ret, ver, 0);
            printf("\n");
        } else if (strcmp(op, "REM") == 0) {
            // Análogo à inclusão de nó
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
            // Análogo à impressão da árvore
            fgets(linha, sizeof(linha), stdin);
            args = sscanf(linha, " %d %d", &key, &ver);
            if (args < 2) ver = act_ver;
            raiz_ret = getRaiz(ver);
            ret = sucessorNo (raiz_ret, key, ver);
            // Se o retorno for nulo, quer dizer que o sucessor da chave é infinito
            if (ret != NULL) {
                printf("SUC %d %d\n%d", key, ver, ret->key);
            } else {
                printf("SUC %d %d\ninfinito", key, ver);
            }
            printf("\n");
        } else if (strcmp(op, "EOF") == 0) break;
        else continue;
    }
    return 0;
}
