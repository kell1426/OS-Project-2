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
  char *Candidates[MaxCandidates];
  int CandidatesVotes[MaxCandidates];
  size_t bufsize = 1024;
  char *buf = (char *)malloc(bufsize);
  int bytes_read = 0;
  char **strings;

	FILE *fd = open(/*argv[1] + ".txt"*/ "votes.txt", O_RDONLY);

  do {
    bytes_read = getline(&buf, &bufsize, fd);
    char* p = strchr(buf, '\n');							//Delete trailing \n character.
	  if(p)
	  {
		  *p = 0;
	  }
    makeargv(buf, " ", &strings);
    int i;
    int match = 0;
    for(i = 0; i < MaxCandidates; i++)
    {
      if(Candidates[i] == NULL) //Candidate not found in array, must be added to array
      {
        break;
      }
      if(*strings == Candidates[i]) //Match found
      {
        match = 1;
        break;
      }
    }
    if(match == 1)
    {
      CandidatesVotes[i]++;
    }
    else
    {
      Candidates[i] = *strings;
      CandidatesVotes[i]++;
    }

  } while(bytes_read != 0);
	return 0;
}
