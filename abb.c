#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "abb.h"

/*
  Função auxiliar de criação de um novo filho

  @parâmetros:
    -Abb* pai: ponteiro para o pai do novo nó a ser criado
    -chave: valor inteiro a ser inserido no nó criado
*/
Abb* abb_novoFilho(Abb* pai, int chave) {
  Abb* no = (Abb*)malloc(sizeof(Abb));

  no->chave = chave;
  no->pai = pai;
  no->esq = NULL;
  no->dir = NULL;

  return no;
}

/*
  Função de inserção de um nó em uma ABB com seu valor chave

  @parâmetros:
    -Abb* no: raiz da árvore que deseja fazer a inserção
    -chave: valor inteiro que deseja incluir no nó a ser inserido
*/
Abb* abb_insere(Abb* no, int chave) {
  if(no == NULL) // árvore vazia, logo precisamos criar um novo filho
    return abb_novoFilho(no, chave);

  else if(chave < no->chave) {
    if(no->esq == NULL)
      no->esq = abb_novoFilho(no, chave);
    else
      no->esq = abb_insere(no->esq, chave);
  }

  else if(chave > no->chave) {
    if(no->dir == NULL)
      no->dir = abb_novoFilho(no, chave);
    else
      no->dir = abb_insere(no->dir, chave);
  }
  return no;
}

/*
  Função de remoção de um nó de uma ABB a partir de sua chave

  @parâmetros
    -Abb* no: raiz da árvore que deseja fazer a remoção
    -chave: valor chave do nó que deseja remover
*/
Abb* abb_remove(Abb* no, int chave) {
  if(no == NULL) // árvore vazia, logo não há o que remover
    return NULL;

  else if(chave < no->chave)
    return abb_remove(no->esq, chave);

  else if(chave > no->chave)
    return abb_remove(no->dir, chave);

  else { // achou o nó a ser removido
    if(no->esq == NULL && no->dir == NULL) { // nó não possui filhos (folha)
      if(no->pai->esq == no)
        no->pai->esq = NULL;
      else
        no->pai->dir = NULL;
      free(no);
      no = NULL;
    }

    else if(no->esq == NULL || no->dir == NULL) { // nó só tem um filho
      Abb* aux = NULL;
      if(no->esq == NULL) // verifica se o filho é da esquerda ou direita
        aux = no->pai->dir;
      else if(no->dir == NULL)
        aux = no->pai->esq;
      Abb* aux_pai = no->pai; // pai de 'no', logo avô de 'aux'
      aux->pai = aux_pai; // pai de 'aux' passa a ser seu avô
      if(aux_pai->esq == no) // filho do avô passa a ser 'aux', no lado correto
        aux_pai->esq = aux;
      else
        aux_pai->dir = aux;
      free(no);
    }
    else { // nó tem dois filhos, buscamos então seu sucessor
      Abb* sucessor = no->dir;
      while(sucessor->esq != NULL)
        sucessor = sucessor->esq;
      no->chave = sucessor->chave;
      if(sucessor->pai->dir == sucessor) {
        sucessor->pai->dir = sucessor->dir;
        sucessor->dir->pai = sucessor->pai;
      }
      free(sucessor);
    }
  }
  return no;
}

/*
  Busca iterativa

  @parâmetros
    -Abb* no: raiz da árvore que deseja realizar a busca
    -chave: valor inteiro que deseja buscar na dada árvore
*/
Abb* abb_busca(Abb* no, int chave) {
  if(no == NULL) // árvore vazia, logo não há o que buscar
    return NULL;

  while(chave != no->chave) {
    if(chave < no->chave)
      no = no->esq;
    else
      no = no->dir;
  }
  return no;
}

/*
  Computa o nó sucessor do nó chamado pela função

  @complexidade: O(h), em uma árvore de altura h

  @parâmetros
    -Abb* no: nó da árvore que deseja calcular o sucessor
*/
Abb* abb_sucessor(Abb* no) {
  if(no == NULL) // árvore vazia, logo não há o que buscar
    return NULL;

  else if(no->dir != NULL)
    return abb_minimo(no->dir);

  else {
    Abb* aux = no->pai;

    while(aux != NULL && no == aux->dir) {
      no = aux;
      aux = aux->pai;
    }
    return aux;
  }
}

/*
  Computa o nó antecessor do nó chamado pela função

  @complexidade: O(h), em uma árvore de altura h

  @parâmetrods
    -Abb* no: nó da árvore que deseja calcular o antecessor
*/
Abb* abb_antecessor(Abb* no) {
  if(no == NULL) // árvore vazia, logo não há o que buscar
    return NULL;

  else if(no->esq != NULL)
    return abb_maximo(no->esq);

  else {
    Abb* aux = no->pai;

    while(aux != NULL && no == aux->esq) {
      no = aux;
      aux = aux->pai;
    }
    return aux;
  }
}

/*
  Busca a chave de menor valor em uma dada árvore

  @complexidade: O(h), em uma árvore de altura h

  @parâmetros
    -Abb* no: raiz da árvore que deseja calcular o mínimo
*/
Abb* abb_minimo(Abb* no) {
  if(no == NULL) // árvore vazia, logo não há o que buscar
    return NULL;

  while(no->esq != NULL)
    no = no->esq;

  return no;
}

/*
  Busca a chave de maior valor em uma dada árvore

  @complexidade: O(h), em uma árvore de altura h

  @parâmetros
    -Abb* no: raiz da árvore que deseja calcular o máximo
*/
Abb* abb_maximo(Abb* no) {
  if(no == NULL) // árvore vazia, logo não há o que buscar
    return NULL;

  while(no->dir != NULL)
    no = no->dir;

  return no;
}

/*
  Computa recursivamente a altura
  de uma dada árvore.

  @parâmetros
    -Abb* no: raiz da árvore que deseja fazer o cálculo
*/
int abb_altura(Abb* no) {
  int altura_esq, altura_dir;

  if(no == NULL) // árvore vazia, logo sua altura é -1
    return -1;

  altura_esq = abb_altura(no->esq);
  altura_dir = abb_altura(no->dir);

  if(altura_esq > altura_dir)
    return altura_esq + 1;
  else
    return altura_dir + 1;
}

/*
  Computa recursivamente a quantidade
  de nós presente na dada árvore

  @parâmetros
    -Abb* no: raiz da árvore que deseja fazer o cálculo
*/
int abb_qtdNos(Abb* no) {
  if(no == NULL) // árvore vazia, logo não há nenhum nó
    return 0;

  return (1 + abb_qtdNos(no->esq) + abb_qtdNos(no->dir));
}

/*
  Computa a largura de uma dada ávore.
  Largura de uma ABB é definida como a diferença entre
  a maior e menor chave dentre seus nós.

  @parâmetrods
    -Abb* no: raiz da árvore que deseja calcular a altura
*/
int abb_largura(Abb* no) {
  Abb* min = NULL;
  Abb* max = NULL;

  if(no == NULL) // árvore vazia, logo não há nós e sua largura é (0-0 = 0)
    return 0;

  min = abb_minimo(no);
  max = abb_maximo(no);

  return (max->chave - min->chave);
}

/*
  Computa a densidade de uma dada árvore.
  Densidade de uma ABB de altura 'h' é definida pela divisão
  entre sua quantidade de nós e o número de nós
  de uma ABB cheia, de altura h

  @parâmetros
    -Abb* no: raiz da árvore que deseja calcular a densidade
*/
//float abb_densidade(Abb* no) {
  //int n, N, altura;

  //if(no == NULL) // árvore vazia, logo não há o que calcular
    //return 0;

  //n = abb_qtdNos(no);
  //altura = abb_altura(no);
  //N = pow(altura+1, 2) - 1;

  //return n/N;
//}

/* Função que verifica se uma árvore é vazia */
int treeIsEmpty(Abb* t)
{
  /* Retorna 1 se a árvore for vazia e 0 caso contrário */
  return t == NULL;

}

void showTree(Abb* t)
{
  /* Essa função imprime os elementos de forma recursiva */
  
  printf("<"); /* notação para organizar na hora de mostrar os elementos */
  if(!treeIsEmpty(t)) /* se a árvore não for vazia... */
  {
    /* Mostra os elementos em pré-ordem */
    printf("%d ", t->chave); /* mostra a raiz */
    showTree(t->esq); /* mostra a sae (subárvore à esquerda) */
    showTree(t->dir); /* mostra a sad (subárvore à direita) */
  }
  printf(">"); /* notação para organizar na hora de mostrar os elementos */
}

int main(void) {
  Abb* a;
  Abb* aux;
  Abb* raiz;
  int aux_inteiro;
  a = aux = raiz = NULL;
  a = abb_insere(a, 7);
  a = abb_insere(a, 4);
  a = abb_insere(a, 9);
  a = abb_insere(a, 2);
  a = abb_insere(a, 5);
  a = abb_insere(a, 6);
  a = abb_insere(a, 1);
  a = abb_insere(a, 8);
  a = abb_insere(a, 3);
  a = abb_insere(a, 10);
  showTree(a);
  printf("\n");
  //aux = abb_remove(a, 4);
  //showTree(a);
  //printf("\n");
  raiz = abb_busca(a, 7);
  printf("passou da busca\n");
  
  aux = abb_minimo(raiz);
  printf("Minimo: %d\n", aux->chave);
  aux = abb_maximo(raiz);
  printf("Maximo: %d\n", aux->chave);
  aux = abb_sucessor(raiz);
  printf("Sucessor: %d\n", aux->chave);
  aux = abb_antecessor(raiz);
  printf("Antecessor: %d\n", aux->chave);
  aux = abb_busca(a, 10);
  printf("Busca (10): %d\n", aux->chave);

  aux_inteiro = abb_altura(raiz);
  printf("Altura: %d\n", aux_inteiro);
  aux_inteiro = abb_qtdNos(raiz);
  printf("Qtd nos: %d\n", aux_inteiro);
  aux_inteiro = abb_largura(raiz);
  printf("Largura: %d\n", aux_inteiro);
  //aux_inteiro = abb_densidade(raiz);
  //printf("Densidade %d\n", aux_inteiro);
  

  return 0;
}
