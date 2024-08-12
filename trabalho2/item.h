#ifndef ITEM_H
#define ITEM_H

typedef struct {
  int id, id2;      // identificador do nó
  double value;     // valor associado ao nó
} Item;


#define id(A)          (A.id)
#define id2(A)          (A.id2)                         // retorna identificador do nó
#define value(A)        (A.value)                       // retorna valor do nó
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor
#define exch(A, B)      { Item t = A; A = B; B = t; }   // troca dois nós

#endif
