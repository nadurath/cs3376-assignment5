#include <stdio.h>
#include <stlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int arg, char **argv)
{
	int status;
	char *cat_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] ={"grep", "3376", NULL};
	char *wg_args[] = {"wc", "-l", NULL};

	int pipeA[2];
	int pipeB[2];

	pidT, pidA, pidB;

	pipe(pipeA);
	pipe(pipeB);

	if(!(pidA = fork()))
	{
		close(pipeA[0]);
		dup2(pipeA[1], 1);
		close(pipeA[1]);
		execvp(*cat_args, cat_args);
		exit(0);
	}

	else if(!(pidB =fork()))
	{
		close(pipeA[1]);
		dup2(pipeA[0], 0);
		close(pipeA[0]);
		
		close(pipeB[0]);
		dup2(pipeB[1],1);
		close(pipeB[1]);

		execvp(*grep_args, grep_args);
	}

	else
	{
		close(pipeA[1]);
		close(pipeA[0]);
		close(pipeB[1]);
		dup2(pipeB[0],0);
		close(pipeB[0]);
		execvp(*wc_args, wc_args);
	}

	close(pipeB[1]);
	close(pipeB[0]);

	return(0);

}
