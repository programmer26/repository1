#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

void check_options(int argc, char **argv, int *options){
	struct stat stats;

	for(int i = 1; i < argc; i++){
		if(argv[i][0] == '-'){
			if(stat(argv[i], &stats) == -1){
				for(int j = 0; j < strlen(argv[i]); j++){
					switch(argv[i][j]){
						case 'A':
							options[0] = 1;	
							break;

						case 'l':
							options[1] = 1;
							break;

						case 'R':
							options[2] = 1;
							break;
					}
				}
			}
		}
	}
}

void find_filestats(char *fullpath, char *filepath, int option, char *filestats){
	struct stat stats;
	char current_stat[300] = {0};
	sprintf(filestats, "%s", "");
	
	stat(fullpath, &stats);

	if(stat(fullpath, &stats) == -1){
		if(errno == ENOENT){
			printf("ls: cannot access %s: %s\n", fullpath, strerror(errno));
			exit(-1);
		}
	}
	
	switch(stats.st_mode & S_IFMT){
		case S_IFREG:
			strcat(filestats, "-");
			break;

		case S_IFDIR:
			strcat(filestats, "d");
			break;

		case S_IFBLK:
			strcat(filestats, "b");
			break;

		case S_IFCHR:
			strcat(filestats, "c");
			break;

		case S_IFIFO:
			strcat(filestats, "p");
			break;

		case S_IFLNK:
			strcat(filestats, "l");
			break;

		case S_IFSOCK:
			strcat(filestats, "s");
			break;
	}

	if(option == 1){
		sprintf(current_stat, "%s", "---------");
		if(stats.st_mode & S_IRUSR) current_stat[0] = 'r';
		if(stats.st_mode & S_IWUSR) current_stat[1] = 'w';
		if(stats.st_mode & S_IXUSR) current_stat[2] = 'x';
		if(stats.st_mode & S_IRGRP) current_stat[3] = 'r';
		if(stats.st_mode & S_IWGRP) current_stat[4] = 'w';
		if(stats.st_mode & S_IXGRP) current_stat[5] = 'x';
		if(stats.st_mode & S_IROTH) current_stat[6] = 'r';
		if(stats.st_mode & S_IWOTH) current_stat[7] = 'w';
		if(stats.st_mode & S_IXOTH) current_stat[8] = 'x';
		strcat(filestats, current_stat);

		sprintf(current_stat, "%ld", stats.st_nlink);
		strcat(filestats, " ");
		strcat(filestats, current_stat);
			
		strcat(filestats, " ");
		strcat(filestats, getpwuid(stats.st_uid)->pw_name);

		strcat(filestats, " ");
		strcat(filestats, getgrgid(stats.st_gid)->gr_name);

		sprintf(current_stat, "%ld", stats.st_size);
		strcat(filestats, " ");
		strcat(filestats, current_stat);

		sprintf(current_stat, "%.12s", ctime(&stats.st_mtime) + 4);
		strcat(filestats, " ");
		strcat(filestats, current_stat);
	}

	strcat(filestats, " ");
	strcat(filestats, filepath);
}

int find_total_blocksize(char *filepath, int option){
	struct stat stats;
	DIR *dir = opendir(filepath);
	
	if(dir == NULL){
		if(errno == EACCES){
			printf("ls: cannot open directory %s: %s\n", filepath, strerror(errno));
			exit(-1);
		}
	}

	struct dirent *entry;
	char fullpath[300];
	int total_blocksize = 0;

	while((entry = readdir(dir)) != NULL){
		if(((strcmp(entry->d_name, ".") != 0) &&
		(strcmp(entry->d_name, "..") != 0)) &&
		((entry->d_name[0] != '.') ||
		(option == 1))){
			sprintf(fullpath, "%s", "");
			strcat(fullpath, filepath);
			if(fullpath[strlen(fullpath) - 1] != '/'){
				strcat(fullpath, "/");
			}
			strcat(fullpath, entry->d_name);

			if(stat(fullpath, &stats) == -1){
				if(errno == ENOENT){
					printf("ls: cannot access %s: %s\n", fullpath, strerror(errno));
					exit(-1);
				}
			}

			total_blocksize += stats.st_blocks;
		}
	}
	
	closedir(dir);

	return total_blocksize;
}

void print_file(char *filepath, int *options){
	if(filepath[0] != '-'){
		struct stat stats;
		char filestats[300];
		char fullpath[300];
		char subdirs[30][300];
		int amount_subdirs = 0;
		if(stat(filepath, &stats) == -1){
			if(errno == ENOENT){
				printf("ls: cannot access %s: %s\n", filepath, strerror(errno));
				exit(-1);
			}
		}

		if(!S_ISDIR(stats.st_mode)){
			if(options[4] == 1){
				if(options[3] == 1){
					return;
				}

				options[5] = 1;
			}

			find_filestats(filepath, filepath, options[1], filestats);
			printf("%s\n", filestats);
		}else{
			if(options[4] == 1){
				if(options[3] == 0){
					return;
				}
			}

			if(options[5] != 0 && (options[4] == 1 || options[2] == 1)){
				printf("\n");
			}else{
				options[5] = 1;
			}

			if(options[4] == 1 || options[2] == 1){
				printf("%s:\n", filepath);
			}
			
			if(options[1] == 1){
				int total_blocksize = find_total_blocksize(filepath, options[0]) / 2;
				printf("total %d\n", total_blocksize);
			}
		
			DIR *dir = opendir(filepath);
			
			if(dir == NULL){
				if(errno == EACCES){
					printf("ls: cannot open directory %s: %s\n", filepath, 
					strerror(errno));
					exit(-1);
				}
			}

			struct dirent *entry;

			while((entry = readdir(dir)) != NULL){
				if(((strcmp(entry->d_name, ".") != 0) && 
				(strcmp(entry->d_name, "..") != 0)) &&
				((entry->d_name[0] != '.') || 
				(options[0] == 1))){
					sprintf(fullpath, "%s", "");
					strcat(fullpath, filepath);
					if(fullpath[strlen(fullpath) - 1] != '/'){
						strcat(fullpath, "/");	
					}
					strcat(fullpath, entry->d_name);

					find_filestats(fullpath, entry->d_name, options[1], filestats);
					
					if(filestats[0] == 'd' && options[2] == 1){
						sprintf(subdirs[amount_subdirs], "%s", "");
						strcat(subdirs[amount_subdirs], fullpath);
						amount_subdirs++;
					}
					
					printf("%s\n", filestats);
				}
			}

			closedir(dir);
			
			if(options[2] == 1){
				for(int i = 0; i < amount_subdirs; i++){
					print_file(subdirs[i], options);	
				}
			}
		}
	}
}

int main(int argc, char **argv){
	int options[7] = {0}, amount_nonoptions = 0, last_nonoption = -1;
	check_options(argc, argv, options);
	
	for(int i = 1; i < argc; i++){
		if(argv[i][0] != '-'){
			amount_nonoptions++;
			last_nonoption = i;
		}
	}
	
	if((argc == 1) || (amount_nonoptions == 0)){
		print_file(".", options);
	}else if(amount_nonoptions == 1){
		print_file(argv[last_nonoption], options);
	}else{
		options[4] = 1;
		for(int i = 1; i < argc; i++){
			print_file(argv[i], options);
		}
		
		options[3] = 1;
		for(int i = 1; i < argc; i++){
			print_file(argv[i], options);
		}
	}

	return 0;
}
