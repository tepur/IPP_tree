#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "tree.h"

#define MAX_OPER_TYPE 20

int main(int argc, char *argv[]){

	char debugMode = 'N';
	int i;

	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-v") == 0){
			debugMode = 'Y';
		}
		else{
			printf("ERROR");
			exit(1);
		}
	}

	Tree *tree = makeTree();
	
	char operationName[MAX_OPER_TYPE + 3];
	int k, w;
	
	while(scanf("%s", operationName) != EOF){
		
		if(strcmp(operationName, "SPLIT_NODE") == 0){
			scanf("%d %d", &k, &w);
			splitNode(tree, k, w);
		}
		else{
			scanf("%d", &k);
			
			if(strcmp(operationName, "ADD_NODE") == 0){
				addNode(tree, k);
			}
			else if(strcmp(operationName, "RIGHTMOST_CHILD") == 0){
				rightmostChild(tree, k);
			}
			else if(strcmp(operationName, "DELETE_NODE") == 0){
				deleteNode(tree, k);
			}
			else{
				deleteSubtree(tree, k);
			}
		}
		if(debugMode == 'Y'){
			fprintf(stderr, "NODES: %d\n", getSize(tree));
		}
	}
	deleteTree(tree);
	return 0;
}
