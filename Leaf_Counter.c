/*kell1426
*02/21/18
*Daniel Kelly
*4718021*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define MaxCandidates 10

int main(int argc, char **argv){

	if (argc != 2){
		printf("Usage: %s Program\n", argv[0]);
		return -1;
	}

	char **Candidates = (char**)malloc(MaxCandidates * sizeof(char*));
	int i;
  int CandidatesVotes[MaxCandidates];
  size_t bufsize = 50;
  char *buf = (char *)malloc(bufsize);

	char *inputfile = malloc(256);	//Compine path name with votes.txt
	strcpy(inputfile, argv[1]);
	strcat(inputfile, "/votes.txt");	//Makes "<path>/votes.txt"

	FILE *fp = fopen(inputfile, "r");	//Open file in read only
    while(fgets(buf, sizeof(buf), fp) != NULL)
		{
			char* p = strchr(buf, '\n');//Delete trailing \n character.
		  if(p)
		  {
			  *p = 0;
		  }
	    int match = 0;
	    for(i = 0; i < MaxCandidates; i++)
	    {
	      if(Candidates[i] == NULL) //Candidate not found in array, must be added to array
	      {
	        break;
	      }
	      else if(buf == Candidates[i]) //Match found
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
	      strcpy(Candidates[i], buf);	//Does not copy correctly
	      CandidatesVotes[i]++;	//Increment this candidates total votes
	    }
		}
		for(i = 0; i < MaxCandidates; i++)
		{
			printf("Candidate %s has this many votes: %d", Candidates[i], CandidatesVotes[i]);
		}

		char *outputfile = malloc(256);	//Combine path name with output file name
		strcpy(outputfile, argv[1]);
		strcat(outputfile, "/<node_name>.txt");	//Creates "<path>/<node_name>.txt"

		FILE *outfp = fopen(outputfile, "w");	//Open file in write mode. Overwrite if existing
		for(i = 0; i < MaxCandidates; i++)
		{
			if(Candidates[i] == NULL)
			{//char *Candidates[MaxCandidates];
				break;
			}
			fprintf(outfp, "%s:%d,",Candidates[i], CandidatesVotes[i]);	//Write Candidate info to file
		}

		//Print out "argv[1]/last part of directory"

		//Free memory
		free(outputfile);
		free(inputfile);
		free(Candidates);
		free(buf);
		return 0;
}
