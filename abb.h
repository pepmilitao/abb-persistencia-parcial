typedef struct Versao Versao;

typedef struct No No;

typedef struct Memoria Memoria;

void corrigeNo (No* no);

void incluirNo (Memoria* mem, No* raiz, int key, int* ver);

void remocaoNo (No* raiz, int key);

void sucessorNo(No* raiz, int key, int ver);

void imprimeNo (No* raiz, int key, int ver);
