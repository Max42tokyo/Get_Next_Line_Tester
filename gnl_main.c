#include<stdio.h> 
#include<fcntl.h> 
#include<unistd.h>
#include<stdbool.h>
#include "gnl/get_next_line.h"
#include<string.h>
#include<time.h>
int  fd;
int  fd_seg;
char *tmp;
char *str_out;
int retu = 1;
pid_t pid;
bool has_segfault_ft;
bool ok;
# define TEST_SEGFAULT(func) do { \
	if ((pid = fork()) < 0) \
		exit(EXIT_FAILURE); \
	if (pid == 0) { \
		do { func } while(0); \
		exit(EXIT_SUCCESS); \
	} else { \
		wait(&pid); \
		has_segfault_ft = WIFSIGNALED(pid); \
	} \
} while(0)

#define TESTER_gnl(fileName,expected,exp_return,msg) do{\
        if (fd == -1)\
            printf("\033[1;31mError in Opening file!!\033[0m\n");\
        else{\
        TEST_SEGFAULT(get_next_line(fd_seg, &str_out););\
        if (has_segfault_ft)\
        {\
            printf("\033[0;31m%-15s\033[0;33mFILE_NAME :\033[0;34m %-50s \033[0;33mBUFFER_SIZE : \033[1;0m%d\n","SEGFAULT",msg,BUFFER_SIZE);\
            return 0377;\
        }\
        else{\
            if (fd == -1)\
                printf("\033[1;31mError in Opening file!!\033[0m\n");\
            else{\
                retu = get_next_line(fd, &str_out);\
                if (retu != exp_return)\
                {\
                   /* TODO:::::::::::::: RETURN EXPECTED */\
                }\
                else if(strcmp(str_out,expected))\
                {\
                    printf("\033[0;31m%-15s\033[0;33mFILE_NAME :\033[0;34m %-50s \033[0;33mBUFFER_SIZE : \033[1;0m%d\n","LINE KO",msg,BUFFER_SIZE);\
                    return 0377;\
                }\
            }\
        }\
        }}while(0)

int main(int ac, char **av) 
{   
    setbuf(stdout, NULL);
    int n_time = atoi(av[2]);
    int k;
    // OPEN THE FILE
    FILE *fp = fopen(av[1], "r"); 
    fd = open(av[1],O_RDONLY);
    fd_seg = open(av[1],O_RDONLY);
    if (fp == NULL || fd < 0 || fd_seg < 0) { 
        printf("\033[1;31mCould not open file %s\n", av[1]); 
        return 0; 
    } 

    char *buffer_expected = NULL;
    size_t buffer_size = 0;
    int return_expected = 0;
    clock_t start = clock();
    for (int i = 0; n_time > 0 ? i <  n_time : (retu && return_expected >= 0); i++)
    {
        return_expected = getline(&buffer_expected, &buffer_size, fp);
        if(buffer_expected[return_expected - 1] == '\n')
            buffer_expected[return_expected - 1] = 0;
        return_expected = return_expected > 0 ? 1 : 0;
        TESTER_gnl(av[1], buffer_expected, return_expected,av[3]);
        if (((double)clock() - start) / (double)CLOCKS_PER_SEC > 3.0)
        {
            printf("\033[0;31m%-15s\033[0;33mFILE_NAME :\033[0;34m %-50s \033[0;33mBUFFER_SIZE : \033[1;0m%d\n","TIME OUT",av[3],BUFFER_SIZE);
            return 0377;
        }
    }
    printf("\033[0;32m%-15s\033[0;33mFILE_NAME :\033[0;34m %-50s \033[0;33mBUFFER_SIZE : \033[1;0m%d\n","OK",av[3],BUFFER_SIZE);
    return 0;
  
    
}
