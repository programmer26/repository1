//------------------------------------------------------------------------
// NAME: Denislav Ivanov
// CLASS: XIv
// NUMBER: 7
// PROBLEM: #1
// FILE NAME: tail.c (unix file name)
// FILE PURPOSE:
// имплементация на функцията "tail"
// ...
//------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>




//------------------------------------------------------------------------
// FUNCTION: print (име на функцията)
// принтира последните 10 реда на файла
// PARAMETERS:
// buffer - указател към съдържанието на файла
// file_name - име на файла; без име, ако file_name = NULL
// file_size - размер на файла
// new_line - дали да се принтира '\n' в края на буфера
//------------------------------------------------------------------------

void print(char* buffer, char* file_name, int file_size, int new_line)
{
	int write_bytes, remaining, size;
	int i, j = 0;

	//offset from the start of the buffer to the last 10 lines
	for(i = file_size - 1; i > 0; --i)
	{
		if(buffer[i] == '\n')
			++j;
		if(j == 11)
		{
			++i;	
			break;
		}
	}
	
	size = file_size - i;
	remaining = size;
	
	//if file_name is NULL, don't print header
	if(file_name != NULL)
	{
		char file[256], *p = file;
		strcpy(file, "==> ");
		strcat(file, file_name);
		strcat(file, " <==\n");
		int remaining2 = strlen(file);
		
		while((write_bytes = write(STDOUT_FILENO, p, strlen(file))) != remaining2)
		{
			if(write_bytes == -1)
			{
				perror("tail: error writing 'standard output'");
				break;
			}
			p += write_bytes;
			remaining2 -= write_bytes;
		}
	}

	//write the last 10 lines of the file
	while((write_bytes = write(STDOUT_FILENO, buffer + i, size)) != remaining)
	{
		if(write_bytes == -1)
		{
			perror("tail: error writing 'standard output'");
			break;
		}
		buffer += write_bytes;
		remaining -= write_bytes;
		size -= write_bytes;
	}
	
	//write a new line if necessary
	if(new_line)
	{
		while((write_bytes = write(STDOUT_FILENO, "\n", 1)) != 1)
		{
			if(write_bytes == -1)
			{
				perror("tail: error writing 'standard output'");
				break;
			}
		}	
	}
}

//------------------------------------------------------------------------
// FUNCTION: stdin_input (име на функцията)
// чете от stdin
// PARAMETERS:
// file_name - име на файла; без име, ако file_name = NULL
// new_line - дали да се принтира '\n' в края на буфера
//------------------------------------------------------------------------

void stdin_input(char* file_name, int new_line)
{
	char stdin_buffer[2048], *p = stdin_buffer;
	int read_bytes, total_bytes = 0;
	
	if(file_name != NULL)
	{
		int remaining2 = strlen(file_name), write_bytes;
		char* p = file_name;
		while((write_bytes = write(STDOUT_FILENO, p, strlen(file_name))) != remaining2)
		{
			if(write_bytes == -1)
			{
				perror("tail: error writing 'standard output'");
				break;
			}
			p += write_bytes;
			remaining2 -= write_bytes;
		}
	}
	
	while((read_bytes = read(STDIN_FILENO, p, 2048)) != 0)
	{
		p += read_bytes;
		total_bytes += read_bytes;
	}
	
	print(stdin_buffer, NULL, total_bytes, new_line);
}

//------------------------------------------------------------------------
// FUNCTION: main (име на функцията)
// приема аргументи от терминала, от нея започва изпълнението на програмата
// PARAMETERS:
// argc - брой на подадените от терминала аргументи
// argv - указател към аргументите
//------------------------------------------------------------------------

int main(int argc, char** argv)
{
	int i = 1;
	while(i < argc)
	{
		if(!strcmp(argv[i], "-") && argc != 2)
		{
			char buf[24] = "==> standard input <==\n";
			if(i == argc - 1)
				stdin_input(buf, 0);
			else
				stdin_input(buf, 1);
			++i;
			continue;
		}
		
		if(!strcmp(argv[i], "-") && argc == 2)
		{
			stdin_input(NULL, 0);
			++i;
			continue;
		}
		
		//open the file
		int fd = open(argv[i], O_RDONLY);
		if(fd == -1)
		{
			char error[128];
			strcpy(error, "tail: cannot open '");
			strcat(error, argv[i]);
			strcat(error, "' for reading"); 
			perror(error);
			++i;
			continue;
		}

		int read_bytes, size = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		char* buffer = malloc(size), *p = buffer;

		//read the contents of the file and store them in a buffer
		while((read_bytes = read(fd, p, size)) != 0)
		{
			if(read_bytes == -1)
			{
				char error[128];
				strcpy(error, "tail: error reading '");
				strcat(error, argv[i]);
				strcat(error, "'"); 
				perror(error);
				goto end;
			}	
			p += read_bytes;
		}
	
		if(argc > 2 && i != argc - 1)
		{
			print(buffer, argv[i], size, 1);
		}
		else if(argc == 2)
		{
			print(buffer, NULL, size, 0);
		}
		else
		{
			print(buffer, argv[i], size, 0);
		}
		
		//close the file and move on to the next one if there is such
		
		end:;
		int ret = close(fd);
		if(ret == -1)
		{
			char error[128];
			strcpy(error, "tail: error reading '");
			strcat(error, argv[i]);
			strcat(error, "'"); 
			perror(error);		
		}
		free(buffer);
		++i;
	}
	
	//if there are no arguments, prompt the user to enter from the command-line
	if(argc == 1)
	{
		stdin_input(NULL, 0);
	}
	return 0;
}
