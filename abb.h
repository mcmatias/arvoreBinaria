typedef struct abb {
  int chave;
  struct abb* pai;
  struct abb* esq;
  struct abb* dir;
} Abb;

Abb* abb_novoFilho(Abb* pai, int chave);
Abb* abb_insere(Abb* no, int chave);
Abb* abb_remove(Abb* no, int chave);
Abb* abb_busca(Abb* no, int chave);
Abb* abb_sucessor(Abb* no);
Abb* abb_antecessor(Abb* no);
Abb* abb_minimo(Abb* no);
Abb* abb_maximo(Abb* no);

int abb_altura(Abb* no);
int abb_qtdNos(Abb* no);
int abb_largura(Abb* no);
float abb_densidade(Abb* no);
