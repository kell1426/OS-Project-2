/*kell1426
*03/08/18
*Daniel Kelly
*4718021
Vote_Counter.c*/

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
		printf("Program requires 2 arguments. Command and path.\n");
		return -1;
	}

	pid_t pid = fork();
	if(pid > 0)	//Parent will wait for child to finish
	{
		wait(NULL);
	}
	else if(pid < 0)	//Fork error
	{
		printf("Fork Error\n");
	}
	else	//Child
	{
		int devNull = open("/dev/null", 0);	//Re-direct childs stdout to NULL
		dup2(devNull, 1);
		char *arguments[3];
		arguments[0] = "./Aggregate_Votes";
		arguments[1] = argv[1];
		arguments[2] = NULL;
		execv("./Aggregate_Votes", arguments);	//Execute Aggregate_Votes on the root node
		printf("Execution error.\n");
	}
	//At this point, all Aggregate_Votes programs have exited. Time to find the winner
	char **strings;
	int numtokens = makeargv(argv[1], "/", &strings);
	char *inputfile = malloc(256);
	strcpy(inputfile, argv[1]);
	strcat(inputfile, "/");
	strcat(inputfile, *(strings + numtokens - 1));
	strcat(inputfile, ".txt");	//Get the path name of the output file created from calling Aggregate_Voteson the root node

	FILE *fp = fopen(inputfile,"r");	//Open in read mode
	char *buf = malloc(256);
	fgets(buf, 256, fp);	//Grab the vote info
	fclose(fp);
	fopen(inputfile, "a");	//Open in append mode
	char **CandidateStrings;
	int numOfCandidates = makeargv(buf, ",", &CandidateStrings);
	char *winner = malloc(20);
	int winnerVotes;
	int i;
	for(i = 0; i < numOfCandidates; i++)	//Find who the winner is by comparing total votes.
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
	//Free up memory
	fprintf(fp, "Winner: %s\n", winner);
	fclose(fp);
	free(buf);
	free(winner);
	free(inputfile);

	return 0;
}
