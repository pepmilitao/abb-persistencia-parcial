typedef struct No{
    int key;
    struct No* esq;
    struct No* dir;
    int mod_ver;
    char mod_campo;
    struct No* mod_valor;
} No;

typedef struct Raiz {
    No* raiz;
    int versao_max;
} Raiz;

No* criaNo (int key, No* esq, No* dir);

void timeMachine (No* raiz, No** esq, No** dir, int ver);

No* ligaNo (No* raiz, No* add, char campo, int ver);

No* incluirNo (No* raiz, int key, int ver);

// TODO: void remocaoNo (No* raiz, int key);

// TODO: void sucessorNo(No* raiz, int key, int ver);

void imprimeArvore (No* raiz, int ver, int prof);
