/*kell1426
*03/08/18
*Daniel Kelly
*4718021
Leaf_Counter.c*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "makeargv.h"

#define MaxCandidates 10

int main(int argc, char **argv){

	if (argc != 2){
		printf("Program requires 2 arguments. Command and path.\n");
		return -1;
	}

	char **Candidates = (char**)malloc(MaxCandidates * sizeof(char*)); //Allocate memory to store Candidate Names
	int i;
	for(i = 0; i < MaxCandidates; i++)
	{
		Candidates[i] = (char*)malloc(10 * sizeof(char));
	}
  int CandidatesVotes[MaxCandidates];	//Setup array to store votes for each candidate.
	for(i = 0; i < MaxCandidates; i++)
	{
		CandidatesVotes[i] = 0;
	}
  char *buf = (char *)malloc(50);	//Allocate memory to store a vote

	char *inputfile = malloc(256);	//Compine path name with votes.txt
	strcpy(inputfile, argv[1]);
	strcat(inputfile, "/votes.txt");	//Makes "<path>/votes.txt"

	FILE *fp = fopen(inputfile, "r");	//Open file in read only
	if(fp == NULL)
	{
		printf("Not a leaf node.\n");	//Folder does not contain "votes.txt". So it is not a leaf node.
		return(1);
	}
    while(fgets(buf, sizeof(buf), fp) != NULL)	//Read vote from file until EOF
		{
			char* p = strchr(buf, '\n');//Delete trailing \n character.
		  if(p)
		  {
			  *p = 0;
		  }
	    int match = 0;
	    for(i = 0; i < MaxCandidates; i++)
	    {
	      if(Candidates[i][0] == 0) //Candidate not found in array, must be added to array
	      {
	        break;
	      }
	      else if(strcmp(Candidates[i], buf) == 0) //Match found
	      {
	        match = 1;
	        break;
	      }
	    }
	    if(match == 1)
	    {
	      CandidatesVotes[i]++;	//Increment this candidates total votes.
	    }
	    else
	    {
				int j = 0;
				while(buf[j] != 0)
				{
					Candidates[i][j] = buf[j];	//Store this Candidate into array
					j++;
				}
	      CandidatesVotes[i]++;	//Increment this candidates total votes
	    }
		}

		char *outputfile = malloc(256);	//Combine path name with output file name
		char **strings;
		int numtokens = makeargv(argv[1], "/", &strings);
		strcpy(outputfile, argv[1]);
		strcat(outputfile, "/");
		strcat(outputfile, *(strings + numtokens - 1));
		strcat(outputfile, ".txt");	//Creates "<path>/<node_name>.txt"

		FILE *outfp = fopen(outputfile, "w");	//Open file in write mode. Overwrite if existing
		for(i = 0; i < MaxCandidates; i++)
		{
			if(Candidates[i + 1][0] == 0)	//If the next candidate is null
			{
				fprintf(outfp, "%s:%d\n",Candidates[i], CandidatesVotes[i]);	//write with newline at the end
				break;
			}
			fprintf(outfp, "%s:%d,",Candidates[i], CandidatesVotes[i]);	//Write Candidate info to file
		}

		printf("%s\n", outputfile); //Print out the path of the output file

		//Free memory
		free(outputfile);
		free(inputfile);
		free(buf);
		for(i = 0; i < MaxCandidates; i++)
		{
			free(Candidates[i]);
		}
		free(Candidates);
		return 0;
}
