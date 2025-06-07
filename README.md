# Árvore Binária de Busca com persistência parcial

Implementação na linguagem C de uma árvore binária de busca com persistência parcial para a disciplina de Estruturas de Dados Avançadas.

# Como executar o projeto?

Basta fazer o comando `make build` para compilar o projeto e `make run` para executá-lo.

Para verificar a entrada e a saída, execute `make entrada` e `make saida` respectivamente.

Para excluir o arquivo binário, execute `make clean`.

# Como foi planejada a persistência parcial para a estrutura?

**Persistência parcial** é a característica de uma estrutura de dados que cria novas versões a partir da última versão e que pode visualizar o estado da estrutura em qualquer versão anterior, mas não modificar versões anteriores.

Para adicionar essa característica na árvore binária de busca, tomei como base principal o artigo [Making Data Structures Persistent](https://www.cs.cmu.edu/~sleator/papers/making-data-structures-persistent.pdf) que menciona o Método da Cópia de Nós.

Esse método consiste em adicionar campos nos nós da estrutura para marcar as modificações feitas naquele nó.

Para árvores binárias de busca o artigo propõe até uma versão mais simplificada que diminui a quantidade de campos por nó e mantêm a estrutura mais simples possível. Foi me baseando nessa proposta que esta implementação foi feita.

# Como foi implementado?

No projeto há **6 arquivos**, todos no mesmo diretório, são eles:

| Nome do arquivo | Função |
| - | - |
| `abb.h` | Definição das assinaturas e da declaração dos structs |
| `abb.c` | Implementação de `abb.h` |
| `main.c` | Arquivo que importa as funções de `abb.h` |
| `entrada.txt` e `saida.txt` | Entrada e saída do projeto |
| `Makefile` | Arquivo para compilar e executar o projeto |

Entrado em detalhe sobre cada arquivo:

## `abb.h`

Aqui são definidos dois structs, `No` e `Raiz`, além de criadas as assinaturas de 8 funções.

### `No`

`No` possui 3 campos que são originais da árvore binária de busca: `key`, `esq` e `dir`.

Além disso ele também implementa mais 3 campos para a persistência parcial: `mod_ver`, `mod_campo` e `mod_valor`.

- `mod_ver` guarda o valor da versão da qual a modificação se deu,

- `mod_campo` guarda o campo da qual a modificação se deu e

- `mod_valor` guarda o nó apontado após a modificação.

### `Raiz`

A função desse struct é marcar um nó como raiz e guardar a maior versão da qual ele é capaz de manter informação.

Ele possui 2 campos, `raiz` e `versao_max`, sendo auto-explicativos.

### Funções 

Como dito anteriormente, são 8 funções assinadas nesse arquivo header, sendo elas:

| Assinatura | Parâmetros | Saída | Descrição |
| - | - | - | - |
| `criaNo` | `int key`, `No* esq` e `No* dir` | `No*` | Cria um novo nó na memória |
| `timeMachine` | `No* raiz`, `No** esq`, `No** dir` e `int ver` | `void` | Retorna estado dos filhos esquerdo e direito de um nó após suas modificações na versão especificada |
| `ligaNo` | `No* raiz`, `No* add`, `char campo` e `int ver` | `No*` | Liga dois nós verificando se o buffer do nó raiz está cheio, caso esteja, é criado um novo nó com todas as modificações já feitas, incluindo essa nova ligação |
| `incluirNo` | `No* raiz`, `int key` e `int ver` | `No*` | Realiza a inclusão de um nó na árvore binária de busca |
| `achaMinimo` | `No* raiz`, e `int ver` | `No*` | Acha menor elemento da sub-árvore enraizada pelo elemento raiz na versão especificada |
| `remocaoNo` | `No* raiz`, `int key` e `int ver` | `No*` | Realiza a remoção de um nó na árvore binária de busca, se possível |
| `sucessorNo` | `No* raiz`, `int key` e `int ver` | `No*` | Encontra o nó com chave imediatamente maior que a chave dada como entrada na versão especificada |
| `imprimeArvore` | `No* raiz`, `int key` e `int ver` | `void` | Imprime toda a árvore em ordem crescente por chaves e com a profundidade de cada nó na versão especificada |

## `abb.c`

Todas as funções descritas acima são implementadas nesse arquivo, dentro dele há diversos comentários que auxiliam no entendimento da implementação.

Explicando as funcionalidades implementadas mais importantes:

### Inclusão

A função de inclusão `incluirNo` utiliza as funções `criaNo`, `timeMachine` e `ligaNo` para implementar sua funcionalidade.

`criaNo` aloca um espaço de memória para um novo nó e atribui valores para esse nó.

Os campos padrão de um nó de uma árvore binária de busca são dados como parâmetro na função, os campos adicionais são definidos de forma padrão.

``` c
no->mod_ver = 101;
no->mod_campo = 'n';
no->mod_valor = NULL;
```

`timeMachine` é muito importante para todo o código.

Ele possui como parâmetros dois ponteiros de ponteiros de nós, `esq` e `dir`, eles vão guardar as posições que o nó dado como entrada estão apontando na versão fornecida.

Por padrão, os valores de `*esq` e `*dir` são os campos `esq` e `dir` do nó de entrada, mas se houver alguma modificação na versão desejada, esses valores devem ser alterados.

``` c
if (raiz->mod_ver <= ver) {
    if (raiz->mod_campo == 'e') *esq = raiz->mod_valor;
    if (raiz->mod_campo == 'd') *dir = raiz->mod_valor;
}
```

`ligaNo` liga um nó a outro levando em consideração o buffer de alterações.

Se o buffer estiver vazio e o nó que quer ser ligado já não estiver ligado ao nó "raiz", então a ligação somente é anotada.

Mas se ele estiver preenchido, deve ser criado um novo nó com todas as modificações anteriores feitas juntamente com a que será feita na execução dessa função.

``` c
if (campo == 'e') return criaNo (raiz->key, add, dir);
return criaNo (raiz->key, esq, add);
```

Voltando para `incluirNo`, se o nó analizado for nulo, então essa subárvore é vazia e um nó pode ser criado.

Caso contrário, deve-se saber para onde `raiz` está apontando como filho esquerdo e direito usando ao função `timeMachine`.

Daí se a chave for menor ou igual à chave de `raiz`, então deve-se chamar a recursão para o filho esquerdo e ligar o resultado dessa recursão ao campo `esq` do nó `raiz`, e isso é feito com a função `ligaNo`.

Caso contrário é a mesma coisa para o filho direito.

### Remoção

A função de remoção `remocaoNo` utiliza as 3 funções auxiliares da inclusão, além da função `achaMinimo`.

A função `achaMinimo` é bem simples, ela desce na sub-árvore esquerda de um nó até que esta seja nula, quando isso ocorrer, retorna-se a `raiz`.

Remover um nó começa com a busca pelo nó, e isso é feito recursivamente até que `raiz` seja o nó com chave desejada.

Se `raiz` não tiver filhos, então basta retirá-lo da estrutura.
Se `raiz` tiver 1 filho, então basta o pai de `raiz` apontar para seu filho.
Se `raiz` tiver 2 filhos, busca-se o nó mínimo da sub-árvore direita da `raiz`, que será a nova raiz da sub-árvore antes enraizada em `raiz`.

``` c
// Nó sem filhos
if (esq == NULL && dir == NULL) return NULL;
// Nó com 1 filho
if (esq == NULL) return dir;
if (dir == NULL) return esq;
// Nó com 2 filhos
No* prox = achaMinimo (dir, ver);
No* novoDir = remocaoNo (dir, prox->key, ver);
return criaNo (prox->key, esq, novoDir);
```

### Sucessor

A função que acha o sucessor em uma determinada versão é `sucessorNo`, ela itera pela árvore achando candidatos para serem sucessores da chave dada como entrada.

Quando o valor do sucessor é definido, o nó sucessor é dado como saída.

Quando uma chave não tem sucessor, a saída é nula.

### Imprimir

A função de impressão `imprimeArvore` é bastante simples e usa a ideia do **passeio em ordem**:

1. Visita sub-árvore esquerda
2. Imprime informação do nó `raiz`
3. Visita sub-árvore direita

E é isso que essa função faz basicamente.

``` c
imprimeArvore (esq, ver, prof + 1);
printf("%i,%i ", raiz->key, prof);
imprimeArvore (dir, ver, prof + 1);
```

## `main.c`

O arquivo que executa a lógica de `abb.h` implementa mais uma função, `getRaiz`, que faz uma busca binária no array `raizes[50]` para encontrar a raiz adequada para a versão desejada.

O array `raizes[50]` possui as raízes guardadas na memória, juntamente com a versão máxima que essas raízes representam. Isso possibilita que encontremos de forma eficiente qualquer versão de raiz desejada.

Além disso, a implementação desse arquivo permite que uma nova raiz seja criada somente quando necessário, reduzindo o uso de memória. Isso será detalhado em breve.

A função `main` usa um loop que itera no máximo 100 vezes para representar o máximo de 100 versões possíveis para esse projeto.

Cada iteração espera uma palavra reservada, podendo ser `INC` para inclusão, `REM` para remoção, `SUC` para sucessor e `IMP` para impressão. Além disso também há a palavra reservada `EOF` para designar o fim do arquivo de entrada.

`INC` e `REM` devem fornecer também um número inteiro que designa a chave do nó que deve ser adicionada/removida. Ex.: `INC 13`.

`IMP` pode fornecer um número inteiro que designa a versão da estrutura que se deseja imprimir, mas não é obrigatório, e quando essa informação não é inserida, imprime-se a versão mais recente da estrutura. Ex.: `IMP 5`.

`SUC` deve fornecer um número inteiro que designa a chave dada como entrada na função do sucessor, além disso também é possível determinar a versão da estrutura que se deseja encontrar o sucessor. Ex.: `SUC 13 5`.

As funções de inclusão e remoção aumentam uma versão, já as de impressão e sucessão não. Quando um nó é incluido ou retirado, isso pode fazer a raiz precisar se duplicar, por isso que é testado se a saída dessas funções é a raiz atual, caso não seja, então há uma nova raiz que deve ser armazenada.

``` c
if (ret != raiz) {
    raizes[r - 1].versao_max = act_ver - 1;
    raizes[r++] = (Raiz) {ret, act_ver};
    raiz = ret;
} else {
    raizes[r - 1].versao_max = act_ver;
}
```

## `entrada.txt` e `saida.txt`

Esses arquivos servem para guardar o valor de entrada e saída do projeto.

Eles podem ser alterados à vontade, mas `entrada.txt` deve obedecer às regras de entrada descritas acima.
