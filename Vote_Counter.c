/*kell1426
*02/21/18
*Daniel Kelly
*4718021*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "makeargv.h"
#include <sys/wait.h>

int main(int argc, char **argv){

	//Allocate space for MAX_NODES to node pointer
	struct node* mainnodes=(struct node*)malloc(sizeof(struct node)*MAX_NODES);

	if (argc != 2){
		printf("Usage: %s Program\n", argv[0]);
		return -1;
	}

	//call parseInput
	int num = parseInput(argv[1], mainnodes);

	//printgraph(mainnodes,num);	//Used for Debugging.
	//Call execNodes on the root node
	execNodes(mainnodes);


	return 0;
}
