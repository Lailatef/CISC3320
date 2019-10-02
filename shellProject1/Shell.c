//"Welcome to this cshell script, enter one of the following: "
 
// "list:         list files and directory of a given directory" 
// "history:      list commands entered in the past" 
// "printwd:      print current working directory" 
// "chdir:        change to a given directory" 
// "ls:          run an external program with command line arguments" 
 //"exit:         exit the script" 





#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>


int main()
{
    static int count = 0;
    DIR *d;
    struct dirent *dir;
    char *buffer;
    size_t bufsize = 32;
    size_t nread;
    char history[100][30];
    while (1)
    {
        printf("MYSHELL>");
        buffer = (char *)malloc(bufsize * sizeof(char));
        if( buffer == NULL)
        {
            perror("Unable to allocate buffer");
            exit(1);
        }
        nread = getline(&buffer,&bufsize,stdin);
        buffer[strlen(buffer) - 1] = '\0';
        strcpy(history[count], buffer);
        count++;
        if ( strcmp(buffer, "list") == 0 )
        {
            d = opendir(".");
            if (d)
            {
                while ((dir = readdir(d)) != NULL)
                {
                    printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }
        else if ( strcmp(buffer, "exit") == 0 )
        {
            printf("Exiting the shell\n");
            free(buffer);
            exit(0);
        }
        else if ( strcmp(buffer, "history") == 0 )
        {
            int i = 0;
            for ( i = 0; i < count; i++ )
            {
                printf ("%d) %s\n", (i + 1), history[i]);
            }
        }
        else if ( strcmp(buffer, "printwd") == 0 )
        {
            char pwd_buf[PATH_MAX] = {0};
            getcwd(pwd_buf, sizeof(pwd_buf));
            printf("%s\n", pwd_buf);
        }
        else if ( strstr(buffer, "chdir ") != NULL )
        {
            int y=0,z;
            char dirChange[128] = {0};
            for(z=6;z<strlen(buffer);z++)
            {
                dirChange[y] = buffer[z];
                y++;
            }
            if (chdir(dirChange) != 0)
            {
                printf("Error while changing directory\n");
            }

        }
        else
        {
            if ( system(buffer) != 0 )
            {
                printf("Cannot execute command \n");
            }
        }
        free(buffer);
    }
}
