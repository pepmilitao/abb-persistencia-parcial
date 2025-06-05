typedef struct Versao Versao;

typedef struct No No;

typedef struct Memoria Memoria;

No* criaNo (Memoria* mem, int key, No* esq, No* dir);

No timeMachine (No* no, int ver);

No* ligaNo (Memoria* mem, No* raiz, No* add, char campo[3], int* ver);

No* incluirNo (Memoria* mem, No* raiz, int key, int* ver);

void remocaoNo (No* raiz, int key);

void sucessorNo(No* raiz, int key, int ver);

void imprimeNo (No* raiz, int* ver, int prof);
