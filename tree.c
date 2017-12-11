#include<stdlib.h>
#include<stdio.h>


#include "tree.h"

struct _ListElem{
	Node *value;
	ListElem *next, *prev;
	List *listOwner; //guaranteed to be up-to-date only if he is the first/last element of "his" list
};

struct _List{
	ListElem *first, *last;
};

struct _Node{
	int index;
	List *children;
	ListElem *owner;
};

struct _Tree{
	Node *node[MAX_NODE	+ 3];
	Node *root;
	int maxIndex;
	int size;
};

List *makeEmptyList(){
	List *l = (List*) malloc(sizeof(List));
	l->first = NULL;
	l->last = NULL;
	return l;	
}

ListElem *makeListElem(){
	ListElem *el = (ListElem*) malloc(sizeof(ListElem));
	el->prev = NULL;
	el->next = NULL;
	el->value = NULL;
	el->listOwner = NULL;
	return el;
}

Node *makeNode(int index){
	Node *n = (Node*) malloc(sizeof(Node));
	n->index = index;
	n->children = makeEmptyList();
	n->owner = NULL;
	return n;
}

Tree *makeTree(){
	Tree *t = (Tree*) malloc(sizeof(Tree));
	t->maxIndex = 0;
	t->size = 0;
	addNewNodeToTree(t);
	t->root = t->node[0];
	return t;
}

Node *addNewNodeToTree(Tree *t){
	t->node[t->maxIndex] = makeNode(t->maxIndex);
	t->maxIndex++;
	t->size++;

	return t->node[t->maxIndex - 1];
}

void connectNodeWithListElem(Node *n, ListElem *el){
	if(n != NULL && el != NULL){
		el->value = n;
		n->owner = el;
	}
}

void deleteSubtreeNode(Tree *t, Node *n){
	if(n != NULL){
		deleteSubtreeList(t, n->children);
		free(n);
		t->size--;
	}
}

void pushBack(List *l, ListElem *n){
	if((l != NULL) && (n != NULL)){
		if(l->first == NULL){ //list is empty
			l->first = n;
			l->last = n;
		}
		else{
			l->last->next = n;
			n->prev = l->last;
			l->last = n;
		}	
		n->listOwner = l;
	}
}

int getLastIndex(List *l){
	if((l != NULL) && (l->last != NULL) && (l->last->value != NULL)){
		return l->last->value->index;
	}
	else return (-1);
}

void fixTreeToDeleteSubtree(ListElem *el){
	if(el->prev != NULL){
			el->prev->next = el->next;
	}
	else{
		el->listOwner->first = el->next;
		if(el->next != NULL){
			el->next->listOwner = el->listOwner;
		}
	}
	if(el->next != NULL){
		el->next->prev = el->prev;
	}
	else{
		el->listOwner->last = el->prev;
		if(el->prev != NULL){
			el->prev->listOwner = el->listOwner;
		}
	}
}

void deleteSubtreeListElem(Tree *t, ListElem *el){
	if(el != NULL){
		deleteSubtreeNode(t, el->value);
		fixTreeToDeleteSubtree(el);
		free(el);
	}
}

void deleteSubtreeList(Tree *t, List *l){
	if(l != NULL){
		while(l->first != NULL){
			deleteSubtreeListElem(t, l->first);
		}
		free(l);
	}
}

void deleteSingleListElemWithoutFixing(Tree *t, ListElem *el){
	if(el != NULL){
		deleteSingleNodeWithoutFixing(t, el->value);
		free(el);
	}
}

void deleteSingleNodeWithoutFixing(Tree *t, Node *n){
	if(n != NULL){
		deleteSingleListWithoutFixing(n->children);
		free(n);
		t->size--;
	}
}

void deleteSingleListWithoutFixing(List *l){
	if(l != NULL){
		free(l);
	}
}

void deleteTree(Tree *t){
	if(t != NULL){
		deleteSubtreeNode(t, t->root);
		free(t);
	}
}

void fixTreeBeforeDeleteNode(Tree *t, int x){
	if(t->node[x]->owner->prev != NULL){
		if(t->node[x]->children->first != NULL){
			t->node[x]->owner->prev->next = t->node[x]->children->first;
			t->node[x]->children->first->prev = t->node[x]->owner->prev;
		}
		else{
			t->node[x]->owner->prev->next = t->node[x]->owner->next;
		}
	}
	else{ //t->node[x] was the first element on t->node[x]->owner->listOwner
		if(t->node[x]->children->first != NULL){
			t->node[x]->children->first->listOwner = t->node[x]->owner->listOwner;
			t->node[x]->owner->listOwner->first = t->node[x]->children->first;
		}
		else if(t->node[x]->owner->next != NULL){
			t->node[x]->owner->next->listOwner = t->node[x]->owner->listOwner;
			t->node[x]->owner->listOwner->first = t->node[x]->owner->next;
		}
		else{
			t->node[x]->owner->listOwner->first = NULL;
		}
	}

	if(t->node[x]->owner->next != NULL){
		if(t->node[x]->children->last != NULL){
			t->node[x]->owner->next->prev = t->node[x]->children->last;
			t->node[x]->children->last->next = t->node[x]->owner->next;
		}
		else{
			t->node[x]->owner->next->prev = t->node[x]->owner->prev;
		}
	}
	else{ //t->node[x] was the last element on t->node[x]->owner->listOwner
		if(t->node[x]->children->last != NULL){
			t->node[x]->children->last->listOwner = t->node[x]->owner->listOwner;
			t->node[x]->owner->listOwner->last = t->node[x]->children->last;
		}
		else if(t->node[x]->owner->prev != NULL){
			t->node[x]->owner->prev->listOwner = t->node[x]->owner->listOwner;
			t->node[x]->owner->listOwner->last = t->node[x]->owner->prev;
		}
		else{
			t->node[x]->owner->listOwner->last = NULL;
		}
	}
}

int getSize(Tree *t){
	return t->size;
}

void addNode(Tree *t, int k){
	Node *newNode = addNewNodeToTree(t);	
	ListElem *el = makeListElem(); 
	
	connectNodeWithListElem(newNode, el);
	pushBack(t->node[k]->children, el);

	printf("OK\n");
}

void rightmostChild(Tree *t, int k){
	printf("%d\n", getLastIndex(t->node[k]->children));		
}

void deleteNode(Tree *t, int x){
	fixTreeBeforeDeleteNode(t, x);

	if(t->node[x]->owner == NULL){
		deleteSingleNodeWithoutFixing(t, t->node[x]);
	}
	else{
		deleteSingleListElemWithoutFixing(t, t->node[x]->owner);
	}

	printf("OK\n");	
}

void deleteSubtree(Tree *t, int k){	
	if(t->node[k]->owner == NULL){
		deleteSubtreeNode(t, t->node[k]);
	}
	else{
		deleteSubtreeListElem(t, t->node[k]->owner);
	}
	
	printf("OK\n");
}

void splitNode(Tree *t, int k, int w){
	Node *newNode = addNewNodeToTree(t);
	ListElem *el = makeListElem();
	
	connectNodeWithListElem(newNode, el);
	
	ListElem *oldWNext = t->node[w]->owner->next;
	
	t->node[w]->owner->next = el;
	el->prev = t->node[w]->owner;
	
	ListElem *oldKChildrenLast = t->node[k]->children->last;
	t->node[k]->children->last = el;
	el->listOwner = t->node[k]->children;
	
	if(oldWNext != NULL){
		el->value->children->first = oldWNext;
		el->value->children->last = oldKChildrenLast;
		
		oldWNext->listOwner = el->value->children;
		oldKChildrenLast->listOwner = el->value->children;
		
		el->value->children->first->prev = NULL;
		el->value->children->last->next = NULL;
	}
	else{
		el->value->children->first = NULL;
		el->value->children->last = NULL;
	}
	
	printf("OK\n");
}

