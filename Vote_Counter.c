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

#define MaxCandidates 10

int main(int argc, char **argv){
	if (argc != 2){
		printf("Usage: %s Program\n", argv[0]);
		return -1;
	}

	pid_t pid = fork();
	if(pid > 0)
	{
		wait(NULL);
	}
	else if(pid < 0)
	{
		printf("Fork Error\n");
	}
	else
	{
		char *arguments[3];
		arguments[0] = "./Aggregate_Votes";
		arguments[1] = argv[1];
		arguments[2] = NULL;
		execv("/home/dan/Documents/CSCI4061/Project2/Aggregate_Votes", arguments);
		printf("Execution error.\n");
	}

	char **strings;
	int numtokens = makeargv(argv[1], "/", &strings);
	char *inputfile = malloc(256);
	strcpy(inputfile, argv[1]);
	strcat(inputfile, "/");
	strcat(inputfile, *(strings + numtokens - 1));
	strcat(inputfile, ".txt");

	FILE *fp = fopen(inputfile,"r");
	char *buf = malloc(256);
	fgets(buf, 256, fp);
	fclose(fp);
	fopen(inputfile, "a");
	char **CandidateStrings;
	int numOfCandidates = makeargv(buf, ",", &CandidateStrings);
	char *winner = malloc(20);
	int winnerVotes;
	int i;
	for(i = 0; i < numOfCandidates; i++)
	{
		char **CandidateStrings2;
		int num = makeargv(CandidateStrings[i], ":", &CandidateStrings2);
		if(i == 0)
		{
			strcpy(winner, CandidateStrings2[0]);
			winnerVotes = atoi(CandidateStrings2[1]);
		}
		else
		{
			if(atoi(CandidateStrings2[1]) > winnerVotes)
			{
				strcpy(winner, CandidateStrings2[0]);
				winnerVotes = atoi(CandidateStrings2[1]);
			}
		}
	}

	fprintf(fp, "Winner: %s\n", winner);
	fclose(fp);
	free(buf);
	free(winner);
	free(inputfile);

	return 0;
}
