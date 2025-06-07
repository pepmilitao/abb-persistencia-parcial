// Struct que representa o nó
typedef struct No{
    int key;
    struct No* esq;
    struct No* dir;
    int mod_ver;
    char mod_campo;
    struct No* mod_valor;
} No;
// Struct que indica quem são as raizes da árvore
typedef struct Raiz {
    No* raiz;
    int versao_max;
} Raiz;

// Função que cria novo nó na memória e retorna o nó criado
No* criaNo (int key, No* esq, No* dir);

// Função que retorna estado modificado do nó raiz
void timeMachine (No* raiz, No** esq, No** dir, int ver);

// Função que recebe dois nós e liga-os, retornando a raiz da sub-arvore
No* ligaNo (No* raiz, No* add, char campo, int ver);

// Função recursiva que inclui nó na árvore binária de busca, retornando raiz da sub-árvore
No* incluirNo (No* raiz, int key, int ver);

// Função que acha o menor elemento da sub-arvore enraizada pelo elemento raiz
No* achaMinimo(No* raiz, int ver);

// Função que remove um nó da árvore
No* remocaoNo (No* raiz, int key, int ver);

// Função que encontra o nó com chave imediatamente maior que a entrada
No* sucessorNo(No* raiz, int key, int ver);

// Função que imprime toda a árvore em ordem crescente e com as profundidades de cada nó
void imprimeArvore (No* raiz, int ver, int prof);
