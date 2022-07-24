//------------------------------------------------------------------------
// NAME: Denislav Ivanov
// CLASS: XIv
// NUMBER: 7
// PROBLEM: #2
// FILE NAME: shell.c (unix file name)
// FILE PURPOSE:
// имплементация на shell
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ADD 1024


//------------------------------------------------------------------------
// FUNCTION: parse_cmdline (име на функцията)
// обработва подадените й команди във формат, подходящ за execv*()
// PARAMETERS:
// const char* cmdline - указател към подадената команда
//------------------------------------------------------------------------

char** parse_cmdline(const char* cmdline)
{
	int cnt = 1;
	
	//find the number of arguments in the command
	for(int i = 0; cmdline[i] != '\0'; ++i)
	{
		if(cmdline[i] == ' ' && cmdline[i+1] != '\0')
		{
			cnt++;
		}
	}

	cnt++; //increment so the buffer has space for the NULL 

	char** args = malloc(cnt * sizeof(char*));
	
	*args = (char*)cmdline; //first argument --> beginning of the command
	
	for(int i = 0, j = 1; cmdline[i] != '\0'; ++i)
	{
		if(cmdline[i] == ' ')
		{
			if(cmdline[i+1] == '\n')
			{
				args[j] = NULL;
				continue;
			}
			if(cmdline[i+1] == '\0')
			{
				args[j] = NULL;
				continue;
			}
			if(cmdline[i+1] == ' ') //arbitrary number of spaces before an argument
			{
				continue;
			}
			args[j] = (char*)&cmdline[i+1];
			++j;
		}
	}
	
	args[cnt - 1] = NULL;
	
	return args;
}

//------------------------------------------------------------------------
// FUNCTION: execute (име на функцията)
// изпълнява самата команда
// PARAMETERS:
// char** args - масив с аргументи за execv*()
// char* buf - главен масив(с цел освобождаване на памет при грешка на execv*())
//------------------------------------------------------------------------

void execute(char** args, char* buf)
{
	if(args[0][0] == '\0')
		return;

	pid_t pid = fork();
	int status;
	
	if(pid == -1)
	{
		perror("fork");
		return;
	}
	else if(pid == 0)
	{
		execvp(args[0], args);
		perror(args[0]);
		free(args);
		free(buf);
		exit(1);
	}
	else
	{
		wait(&status);
	}
}

//------------------------------------------------------------------------
// FUNCTION: print_dollar (име на функцията)
// принтира '$ ' на STDOUT
// PARAMETERS:
// НЯМА
//------------------------------------------------------------------------

void print_dollar(void)
{
	char* str = "$ ", *q = str;
	int bytes, size = strlen(str);
	
	while((bytes = write(STDOUT_FILENO, q, size)) != 0)
	{
		if(bytes == -1)
		{
			perror("error writing 'standard output'");
			break;
		}
		q += bytes;
		size -= bytes;
	}		
}

//------------------------------------------------------------------------
// FUNCTION: spaces_to_zero (име на функцията)
// замества space-овете с '\0' в даден стринг
// PARAMETERS:
// char* str - указател към стринга
//------------------------------------------------------------------------

void spaces_to_zero(char* str)
{
	for(int i = 0; str[i] != '\0'; ++i)
	{
		if(str[i] == ' ')
			str[i] = '\0';
	}
}

//------------------------------------------------------------------------
// FUNCTION: main (име на функцията)
// от нея започва изпълнението на програмата
// PARAMETERS:
// НЯМА
//------------------------------------------------------------------------

int main(void)
{
	int bytes, size, position = 0;
	char* buffer = malloc(ADD), *line_beginning = buffer;
	
	print_dollar();

	size = ADD; //starting size of the buffer

	while((bytes = read(STDIN_FILENO, &buffer[position], 1)) != 0)
	{
		//check for errors during reading
		if(bytes == -1)
		{
			perror("error reading");
			break;
		}
		
		//resize the buffer if needed
		if(position >= size - 1)
		{
			size += ADD;
			buffer = realloc(buffer, size);
		}

		//check for end of a line
		if(buffer[position] == '\n')
		{
			const char delimiter[3] = "&&";
			char* token = strtok(line_beginning, delimiter);
			
			while(token != NULL)
			{
				if(*token == ' ') //if the character after the delimeter is space, move 'token' by 1
					token += 1;
				
				char** args = parse_cmdline(token); //get the arguments for execv*()
		
				spaces_to_zero(token); //null terminate them
				
				buffer[position] = '\0'; //get rid of the '\n' at the end of the line
				
				execute(args, buffer); //execute the command
				
				free(args);	//free the memory allocated for the arguments of execv*()

				token = strtok(NULL, delimiter); //get next command
			}
			
			line_beginning = &buffer[position + 1]; //next line begins after the '\n'
					
			print_dollar();
		}
		
		position += bytes;
	}
	
	free(buffer); //free the whole buffer memory
	return 0;
}
