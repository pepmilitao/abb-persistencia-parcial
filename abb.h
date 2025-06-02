typedef struct No {
    int key;
    struct No* esq;
    struct No* dir;
    struct No* pai;
    char mods [3][10];
} No;

void incluirNo (No* raiz, int key);

void remocaoNo (No* raiz, int key);

void sucessorNo(No* raiz, int key, int ver);

void imprimeNo (No* raiz, int key, int ver);
