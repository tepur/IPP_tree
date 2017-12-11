#ifndef TREE_H
#define TREE_H

#define MAX_NODE 530000

struct _ListElem;
struct _List;
struct _Node;
struct _Tree;

typedef struct _ListElem ListElem;
typedef struct _List List;
typedef struct _Node Node;
typedef struct _Tree Tree;

List *makeEmptyList();
ListElem *makeListElem();
Node *makeNode(int index);
Tree *makeTree();

Node *addNewNodeToTree(Tree *t);

void connectNodeWithListElem(Node *n, ListElem *el);

void pushBack(List *l, ListElem *n);

int getLastIndex(List *l);

void fixTreeToDeleteSubtree(ListElem *el);
void fixTreeBeforeDeleteNode(Tree *t, int x);

void deleteSubtreeListElem(Tree *t, ListElem *el);
void deleteSubtreeList(Tree *t, List *l);
void deleteSubtreeNode(Tree *t, Node *n);

void deleteSingleListElemWithoutFixing(Tree *t, ListElem *el);
void deleteSingleNodeWithoutFixing(Tree *t, Node *n);
void deleteSingleListWithoutFixing(List *l);

void deleteTree(Tree *t);

int getSize(Tree *t);

void addNode(Tree *t, int k);
void rightmostChild(Tree *t, int k);
void deleteNode(Tree *t, int x);
void deleteSubtree(Tree *t, int k);
void splitNode(Tree *t, int k, int w);


#endif //TREE_H
