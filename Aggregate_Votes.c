/*kell1426
*02/28/18
*Daniel Kelly
*4718021
Aggregate_Votes.c*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "makeargv.h"

#define MaxCandidates 10

int main(int argc, char **argv){

	if (argc != 2){
		printf("Usage: %s Program\n", argv[0]);
		return -1;
	}
	DIR *dir = opendir(argv[1]);
	struct dirent *entry;
	int isLeafNode = 0;
	while(entry = readdir(dir))
	{
		if(entry->d_name[0] != '.')
		{
			printf("Filename: %s\n", entry->d_name);
			if(strcmp(entry->d_name, "votes.txt") == 0)
			{
				printf("This is a leaf node\n");
				isLeafNode = 1;
				pid_t pid = fork();
				if(pid > 0)
				{
					wait(NULL);
				}
				if(pid == 0)
				{
					char *arguments[3];
					arguments[0] = "./Leaf_Counter";
					arguments[1] = argv[1];
					arguments[2] = NULL;
					execv("/home/dan/Documents/CSCI4061/Project2/Leaf_Counter", arguments);
					printf("Execution error.\n");
				}
			}
			else if(entry->d_type == DT_DIR)
			{
				printf("This is a non-leaf node\n");
				pid_t pid = fork();
				if(pid > 0)
				{
					wait(NULL);
				}
				if(pid == 0)
				{
					char *arguments[3];
					arguments[0] = "./Aggregate_Votes";
					arguments[2] = NULL;
					char *append = malloc(256);
					strcpy(append, argv[1]);
					strcat(append, "/");
					strcat(append, entry->d_name);
					arguments[1] = append;
					execv("/home/dan/Documents/CSCI4061/Project2/Aggregate_Votes", arguments);
					printf("Execution error.\n");
				}
			}
		}
	}
	//At this point, all programs should be finished.
	printf("Done\n");
	closedir(dir);

	if(isLeafNode == 0)
	{
		int i;
		int j;
		int match;
		char **Candidates = (char**)malloc(MaxCandidates * sizeof(char*));
		for(i = 0; i < MaxCandidates; i++)
		{
			Candidates[i] = (char*)malloc(10 * sizeof(char));
		}
		int CandidatesVotes[MaxCandidates];
		for(i = 0; i < MaxCandidates; i++)
		{
			CandidatesVotes[i] = 0;
		}

		DIR *dir2 = opendir(argv[1]);
		while(entry = readdir(dir2))
		{
			if(entry->d_name[0] != '.' && entry->d_type == DT_DIR)
			{
				char *filename = malloc(256);
				strcpy(filename, argv[1]);
				strcat(filename, "/");
				strcat(filename, entry->d_name);
				strcat(filename, "/");
				strcat(filename, entry->d_name);
				strcat(filename, ".txt");
				FILE *fp = fopen(filename, "r");
				char *buf = malloc(256);
				fgets(buf, 256, fp);
				char* p = strchr(buf, '\n');//Delete trailing \n character.
				if(p)
				{
					*p = 0;
				}
				char **strings;
				int numOfCandidates = makeargv(buf, ",", &strings);
				match = 0;
				for(i = 0; i < numOfCandidates; i++)
				{
					char **strings2;
					int num = makeargv(strings[i], ":", &strings2);
					for(j = 0; j < MaxCandidates; j++)
					{
						if(Candidates[j][0] == 0)
						{
							break;
						}
						else if(strcmp(Candidates[j], strings2[0]))
						{
							match = 1;
							break;
						}
					}
					if(match = 1)
					{
						int val = atoi(strings2[1]);
						CandidatesVotes[i] += val;
					}
					else
					{
						int k = 0;
						while(strings2[0][k] != 0)
						{
							Candidates[i][k] = strings2[0][k];
							k++;
						}
						CandidatesVotes[i] = atoi(strings2[1]);
					}
				}
			}
		}
		char **strings;
		char *outputfilename = malloc(256);
		strcpy(outputfilename, argv[1]);
		int numtokens = makeargv(argv[1], "/", &strings);
		strcat(outputfilename, "/");
		strcat(outputfilename, *(strings + numtokens - 1));
		strcat(outputfilename, ".txt");

		FILE *outfp = fopen(outputfilename, "w");	//Open file in write mode. Overwrite if existing
		for(i = 0; i < MaxCandidates - 1; i++)
		{
			if(Candidates[i + 1][0] == 0)
			{
				fprintf(outfp, "%s:%d\n",Candidates[i], CandidatesVotes[i]);
				break;
			}
			//fprintf(outfp, "%s:%d,",Candidates[i], CandidatesVotes[i]);	//Write Candidate info to file
			fprintf(outfp, "Votes for candidate %d: %d\n", i, CandidatesVotes[i]);
		}

	}



		

	return 0;
}
