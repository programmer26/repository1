//------------------------------------------------------------------------
// NAME: Denislav Ivanov
// CLASS: XIv
// NUMBER: 7
// PROBLEM: #4
// FILE NAME: ls.c (unix file name)
// FILE PURPOSE:
// имплементация на командата "ls"
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define SUBDIR_LIMIT 512
#define PATH_LIMIT 512

struct stat stats;
char l, r, a; //option flags
const char** dirs, **files; //list of directory and file names
int dir_num, file_num; //number of directories and files passed as arguments
int non_ops; //number of arguments that are not options
int dir_index;

//------------------------------------------------------------------------
// FUNCTION: parse_args (име на функцията)
// проверява дали някоя от опциите(-A,-l,-R) е подадена
// PARAMETERS:
// args - указател към масив от подадени аргументи
// cnt - брой подадени аргументи
//------------------------------------------------------------------------

void parse_args(const char** args, int cnt)
{
	//check for passed options
	for(int i = 1; i < cnt; ++i)
	{
		if(args[i][0] == '-')
		{
			for(int j = 1; j < strlen(args[i]); ++j)
			{			
				if(args[i][j] == 'A')
					a = 1;
					
				if(args[i][j] == 'l')
					l = 1;
					
				if(args[i][j] == 'R')
					r = 1;
			}
		}
		else
			++non_ops;
	}
}

//------------------------------------------------------------------------
// FUNCTION: query_non_ops (име на функцията)
// намира броя на подадените директории и файлове и ги записва в съответните масиви
// PARAMETERS:
// args - указател към масив от подадени аргументи
// cnt - брой подадени аргументи
//------------------------------------------------------------------------

void query_non_ops(const char** args, int cnt)
{
	int dir_i = 0, file_i = 0;
	
	for(int i = 1; i < cnt; ++i) //find the number of dirs and files passed as args
	{
		if(args[i][0] != '-')
		{	
			if(stat(args[i], &stats) == -1)
			{
				printf("ls: cannot access %s: %s\n", args[i], strerror(errno));
				continue;
			}
			
			if(S_ISDIR(stats.st_mode))
				++dir_num;
			else
				++file_num;
		}
	}
	
	dirs = malloc(dir_num * sizeof(char*));
	files = malloc(file_num * sizeof(char*));
	 
	for(int i = 1; i < cnt; ++i)
	{
		if(args[i][0] != '-')
		{	
			if(stat(args[i], &stats) == -1)
				continue;
		
			if(S_ISDIR(stats.st_mode))
			{
				dirs[dir_i] = args[i];
				++dir_i;
			}
			else
			{
				files[file_i] = args[i];
				++file_i;
			}
		}
	}
}

//------------------------------------------------------------------------
// FUNCTION: query_file_stats (име на функцията)
// принтира информация за файловете
// PARAMETERS:
// path - път към файла
//------------------------------------------------------------------------

void query_file_stats(const char* path)
{
	if(stat(path, &stats) == -1)
	{
		printf("ls: cannot access %s: %s\n", path, strerror(errno));
		return;
	}
	
	switch(stats.st_mode & S_IFMT) //find file type
	{
		case S_IFREG: printf("-"); break;

		case S_IFDIR: printf("d"); break;

		case S_IFBLK: printf("b"); break;

		case S_IFCHR: printf("c"); break;

		case S_IFIFO: printf("p"); break;

		case S_IFLNK: printf("l"); break;

		case S_IFSOCK: printf("s"); break;
	}
	
	if(l) //if -l is passed as an argument, find the file persmissions and print additional info
	{
		char permissions[] = "---------";
		
		if(stats.st_mode & S_IRUSR) 
			permissions[0] = 'r';
		if(stats.st_mode & S_IWUSR) 
			permissions[1] = 'w';
		if(stats.st_mode & S_IXUSR) 
			permissions[2] = 'x';
		if(stats.st_mode & S_IRGRP) 
			permissions[3] = 'r';
		if(stats.st_mode & S_IWGRP) 
			permissions[4] = 'w';
		if(stats.st_mode & S_IXGRP) 
			permissions[5] = 'x';
		if(stats.st_mode & S_IROTH) 
			permissions[6] = 'r';
		if(stats.st_mode & S_IWOTH) 
			permissions[7] = 'w';
		if(stats.st_mode & S_IXOTH) 
			permissions[8] = 'x';
		
		printf("%s %ld %s %s %ld %.12s", permissions, stats.st_nlink, getpwuid(stats.st_uid)->pw_name, 
				getgrgid(stats.st_gid)->gr_name, stats.st_size, ctime(&stats.st_mtime) + 4); //permissions, num_of_links, owner name, group name, size in bytes, time of last modification 	
	}
}

//------------------------------------------------------------------------
// FUNCTION: get_block_size (име на функцията)
// намира размера на блоковете в дадена директория
// PARAMETERS:
// path - път към директория
//------------------------------------------------------------------------

int get_block_size(const char* path)
{
	struct dirent* d;
	DIR* dh = opendir(path);
	int size = 0;
	
	if(!dh)
	{
		printf("ls: cannot open directory %s: %s\n", path, strerror(errno));
		exit(1);
	}

	while((d = readdir(dh)) != NULL)
	{
		if((strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) && (a || d->d_name[0] != '.'))
		{
			char full_path[PATH_LIMIT];
			strcpy(full_path, path);
			strcat(full_path, "/");
			strcat(full_path, d->d_name);

			if(stat(full_path, &stats) == -1)
			{
				printf("ls: cannot access %s: No such file or directory\n", full_path);
				continue;
			}
			
			size += stats.st_blocks / 2;			
		}
	}
	closedir(dh);
	return size;
}

//------------------------------------------------------------------------
// FUNCTION: query_path (име на функцията)
// принтира файловете в дадена директория с определените флагове или самите файлове, ако не е подадена директория
// PARAMETERS:
// path - път към файл или директория
//------------------------------------------------------------------------

void query_path(const char* path)
{	
	if(stat(path, &stats) == -1)
	{
		printf("ls: cannot access %s: %s\n", path, strerror(errno));
		return;
	}
	
	if(!S_ISDIR(stats.st_mode)) //if 'path' is not a dir, query the stats and print it
	{
		query_file_stats(path);
		printf(" %s\n", path);
		return;
	}
	
	char subdirs[SUBDIR_LIMIT][PATH_LIMIT] = {0};
	int subdir_cnt = 0;
	struct dirent* d;
	DIR* dh = opendir(path);
	
	if(!dh)
	{
		printf("ls: cannot open directory %s: %s\n", path, strerror(errno));
		return;
	}
	
	if(r)
	{
		if(dir_index)
			printf("\n%s:\n", path);
		else
			printf("%s:\n", path);
	}
	else
	{
		if(file_num)
			printf("\n%s:\n", path);		
		else
		{
			if(non_ops > 1 && dir_index)
				printf("\n%s:\n", path);
			else if(non_ops > 1 && !dir_index)
				printf("%s:\n", path);
		}
	}
	
	if(l)
		printf("total %d\n", get_block_size(path)); //if -l is passed as an argument, print the total block size

	while((d = readdir(dh)) != NULL)
	{
		if((strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) && (a || d->d_name[0] != '.'))
		{
			char full_path[PATH_LIMIT];
			strcpy(full_path, path);
			
			if(path[strlen(path) - 1] != '/') //if path ends with a '/', skip, else put one
				strcat(full_path, "/");
				
			strcat(full_path, d->d_name);
			
			if(r) //if -R is passed, fill the list of subdirectories
			{
				if(stat(full_path, &stats) == -1)
				{
					printf("ls: cannot access %s: No such file or directory\n", path);
					continue;
				}
			
				if(S_ISDIR(stats.st_mode))
				{
					if(subdir_cnt >= SUBDIR_LIMIT)
					{
						printf("Maximum limit of subdirectories reached!\n");
						continue;
					}
					strcpy(subdirs[subdir_cnt], full_path);
					++subdir_cnt;
				}
			}
			
			query_file_stats(full_path);
			printf(" %s\n", d->d_name);
			++dir_index;
		}
	}
	closedir(dh);
		
	if(r) //if -R is passed, recursively check every subdirectory
	{
		for(int i = 0; i < subdir_cnt; ++i)
		{
			query_path(subdirs[i]);
		}
	}
}

int main(int argc, const char** argv)
{
	parse_args(argv, argc);
	query_non_ops(argv, argc);

	if(argc == 1 || non_ops == 0)
	{
		query_path(".");
	}
	else
	{	
		for(int i = 0; i < file_num; ++i)
		{
			query_path(files[i]);
		}
		
		for(int i = 0; i < dir_num; ++i)
		{
			query_path(dirs[i]);
		}
	}

	free(dirs);
	free(files);

	return 0;
}
