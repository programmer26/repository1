#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char**argv)
{
	int i = 0;
	while(i < 12)
	{
		int pid = fork(), status;
		
		if(pid == 0)
		{
			//child
			char* args[argc];
			
			for(int i = 0; i < argc - 1; ++i)
			{
				args[i] = argv[i+1];
			}
			
			printf("%s\n", args[0]);
			
			args[argc - 1] = NULL;
			
			if(execv(args[0], args) == -1)
			{
				perror(args[0]);
			}
		}
		if(pid == -1)
		{
			perror("fork");
		}
		else
		{
			wait(&status);
		}
		sleep(2);
		++i;
	}
	return 0;
}
