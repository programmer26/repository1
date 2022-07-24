#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int args, position = 0;
pthread_t ids[100] = {0};

int is_prime(int N)
{
	if(N == 1)
		return 0;
	
	for(int i = 2; i < N; ++i)
	{
		if(N % i == 0)
			return 0;
	}
	
	return 1;
}

void std_out(char* str, char n_l)
{
	char* p = str, new_line = '\n';
	int w_bytes, remaining = strlen(str);
	
	while((w_bytes = write(STDOUT_FILENO, p, remaining)) != remaining)
	{
		p += w_bytes;
		remaining -= w_bytes;
	}
	
	if(n_l)
		while((w_bytes = write(STDOUT_FILENO, &new_line, 1)) != 1);
}

void* primes(void* args)
{
	std_out("Prime calculation started for N=", 0);
	std_out(args, 1);
	
	char snum[15], snum2[15];
	
	int N = atoi(args), cnt = 0;
	
	for(int i = 2; i < N; ++i)
	{
		if(is_prime(i))
			cnt++;
	}
	
	sprintf(snum, "%d", cnt);
	sprintf(snum2, "%d", N);
	
	std_out("Number of primes for N=", 0);
	std_out(snum2, 0);
	std_out(" is ", 0);
	std_out(snum, 1);
	
	exit(NULL);
}

void execute_command(char* command)
{
	if(*command == 'e')
	{
		for(int i = 0; i < 100; ++i)
		{
			if(ids[i] != 0)
			{
				void* status;

				pthread_join(ids[i], &status);
			}
		}
		
		pthread_exit(0);
	}
	else if(*command == 'p' && command[1] == ' ' && command[2] >= '0' && command[2] <= '9')
	{
		args = atoi(command + 2);
		//pthread_t thread_id;
		
		int rc = pthread_create(&ids[position], NULL, primes, (void*)command+2);
		if(rc)
		{
			printf("ERROR\n");
			return;
		}
		pthread_join(ids[position], NULL);
		position++;
	}
	else
	{
		std_out("Supported commands:", 1);
		std_out("p N - Starts a new calculation for the number of primes from 1 to N", 1);
		std_out("e - Waits for all calculations to finish and exits", 1);
	}
}

int main(void)
{
	char buffer[128], *p = buffer;
	int r_bytes;
	
	while((r_bytes = read(STDIN_FILENO, p, 1)) != 0)
	{
		if(*p == '\n')
		{
			*p = '\0';
			execute_command(buffer);
			p = buffer;
			continue;
		}
		p += r_bytes;
	}

	return 0;
}
