#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *find_free_lines(char *filename);
void find_free_values(char *filename,char final[64][64]);
int *find_malloc_lines(char *filename);
void find_malloc_values(char *filename,char final[64][64]);
void find_return_values(char *filename,char final[64][64]);
void free_comment_add(char *filename, int line);
void free_comment_del(char *filename,int line);
void print_array(char **array);


void print_int_array(int *array)
{
    for (size_t i=0;array[i]!=-1;i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
    printf("Terminé\n");
    return;
}

void print_str_array(char array[64][64])
{
    for (size_t i=0;strcmp(array[i]," ")!=0;i++)
    {
        printf("%s ",array[i]);
    }
    printf("\n");
    printf("Terminé\n");
    return;
}




void free_comment_add(char *filename, int line)
{

    //sed -i ' 2s/$/ \/\/must be freed/' text
    char command[512];
    char l[16];
    sprintf(l,"%d",line);
    strcpy(command,"sed -i '");
    strcat(command,l);
    strcat(command,"s/$/\\/\\/must be freed/' ");
    strcat(command,filename);
    system(command);
}

void free_comment_del(char *filename,int line)
{
    //sed -i '2s/\/\/must be freed//g' text
    char command[512];
    char l[16];
    sprintf(l,"%d",line);
    strcpy(command,"sed -i ' ");
    strcat(command,l);
    strcat(command,"s/\\/\\/must be freed//g' ");
    strcat(command,filename);
    system(command);
}


void find_return_values(char *filename,char final[64][64])
{
    //cat text | grep -E -o 'return[ ]+[(]?[ ]*[a-zA-Z0-9_]+[ ]*[)]?[ ]*;' |grep -E -o '[a-zA-Z0-9_]+[ )]*;'|grep -E -o '[a-zA-Z0-9_]+'
    FILE *fp;
    char path[512];
    char command[512];
    for (int i = 0; i < 64; i++)
    {
        strcpy(final[i]," ");
    }
    strcpy(command,"cat ");
    strcat(command,filename);
    strcat(command," | grep -E -o '^[^//]**return[ ]+[(]?[ ]*[a-zA-Z0-9_]+[ ]*[)]?[ ]*;' |grep -E -o '[a-zA-Z0-9_]+[ )]*;'|grep -E -o '[a-zA-Z0-9_]+'");
    //printf("command : %s\n",command);

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL)
    {
        //printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    size_t i=0;
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        path[strcspn(path,"\r\n")]=0;
        strcpy(final[i],path);
        i++;
    }

    if(NULL != fp)
    {
        pclose(fp);
        fp = NULL;
    }

}




void find_malloc_values(char *filename,char final[64][64])
{
    //cat text | grep -E -o 'free[ ]?\([ ]?[a-zA-Z0-9_]+[ ]?\)'  | grep -E -o '\([ ]?[a-zA-Z0-9_]+[ ]?\)' |grep -E -o '[a-ZA-Z0-9_]+'
    FILE *fp;
    char path[512];
    char command[512];
    for (int i = 0; i < 64; i++)
    {
        strcpy(final[i]," ");
    }
    strcpy(command,"cat ");
    strcat(command,filename);
    strcat(command," | grep -E -o '^[^//]**[a-zA-Z0-9_]+[ ]?=[ ]?malloc' | grep -E -o '[a-zA-Z0-9_]+[ ]?=' | grep -E -o '[a-ZA-Z0-9_]+'");
    //printf("command : %s\n",command);

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL)
    {
        //printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    size_t i=0;
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        path[strcspn(path,"\r\n")]=0;
        strcpy(final[i],path);
        i++;
    }

    if(NULL != fp)
    {
        pclose(fp);
        fp = NULL;
    }

}

int* find_malloc_lines(char *filename)
{
    FILE *fp;
    char path[512];
    int *final=malloc(sizeof(int)*512);
    for (int i = 0; i < 512; i++)
    {
        final[i] = -1;
    }
    char command[512];
    strcpy(command,"cat ");
    strcat(command,filename);
    strcat(command," | grep -E -n -o '^[^//]**[a-zA-Z0-9_]+[ ]?=[ ]?malloc' | cut -d : -f 1");
    //printf("command : %s\n",command);

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL)
    {
        //printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    size_t i=0;
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        // printf("%s", path);
        final[i]=atoi(path);
        i++;
    }

    //printf("final result =\n");
    //printf("%s", final);
    /* close */
    if(NULL != fp)
    {
        pclose(fp);
        fp = NULL;
    }

    return final;
}





void find_free_values(char *filename,char final[64][64])
{
    //cat text | grep -E -o 'free[ ]?\([ ]?[a-zA-Z0-9_]+[ ]?\)'  | grep -E -o '\([ ]?[a-zA-Z0-9_]+[ ]?\)' |grep -E -o '[a-ZA-Z0-9_]+'
    FILE *fp;
    char path[512];
    char command[512];
    for (int i = 0; i < 64; i++)
    {
        strcpy(final[i]," ");
    }
    strcpy(command,"cat ");
    strcat(command,filename);
    strcat(command," | grep -E -o '^[^//]**free[ ]?\\([ ]?[a-zA-Z0-9_]+[ ]?\\)'  | grep -E -o '\\([ ]?[a-zA-Z0-9_]+[ ]?\\)' |grep -E -o '[a-ZA-Z0-9_]+'");
    //printf("command : %s\n",command);

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL)
    {
        //printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    size_t i=0;
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        path[strcspn(path,"\r\n")]=0;
        strcpy(final[i],path);
        i++;
    }

    if(NULL != fp)
    {
        pclose(fp);
        fp = NULL;
    }

}

int* find_free_lines(char *filename)
{
    FILE *fp;
    char path[512];
    int *final=malloc(sizeof(int)*512);
    for (int i = 0; i < 512; i++)
    {
        final[i] = -1;
    }
    char command[512];
    strcpy(command,"cat ");
    strcat(command,filename);
    strcat(command," | grep -E -n -o '^[^//]**[ ]*free[ ]?\\([ ]?[a-zA-Z0-9_]+[ ]?\\)' | cut -d : -f 1");
    //printf("command : %s\n",command);

    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL)
    {
        //printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    size_t i=0;
    while (fgets(path, sizeof(path), fp) != NULL)
    {
        // printf("%s", path);
        final[i]=atoi(path);
        i++;
    }

    //printf("final result =\n");
    //printf("%s", final);
    /* close */
    if(NULL != fp)
    {
        pclose(fp);
        fp = NULL;
    }

    return final;
}

int is_in(char malloc_values[64],char free_values[64][64],char return_values[64][64])
{

    for (size_t j=0;strcmp(free_values[j]," ")!=0 || strcmp(return_values[j]," ")!=0;j++)
    {
        //printf("mal=%s | free=%s | ret=%s\n",malloc_values,free_values[j],return_values[j]);
        if (strcmp(malloc_values,free_values[j])==0)
            return 1;
        if (strcmp(malloc_values,return_values[j])==0)
            return 1;
    }

    return 0;
}

void print_or_delete(char* filename,int* malloc_lines, char malloc_values[64][64], char free_values[64][64], char return_values[64][64] )
{
    for (size_t i=0;malloc_lines[i]!=-1;i++)
    {
        //printf("test\n");
        if (is_in(malloc_values[i],free_values,return_values))
        {
      //      printf("F");
            free_comment_del(filename,malloc_lines[i]);
        }
        else
        {
    //        printf("NF");
            free_comment_del(filename,malloc_lines[i]);
            free_comment_add(filename,malloc_lines[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc!=2)
        return 1;
    int *tofreeline=find_malloc_lines(argv[1]);
    char freeval[64][64];
    find_free_values(argv[1],freeval);
    char malval[64][64];
    find_malloc_values(argv[1],malval);
    char retval[64][64];
    find_return_values(argv[1],retval);
//    printf("malloc array\n");
 //   print_str_array(malval);
    //printf("free array\n");
    //print_str_array(freeval);
    //printf("ret array\n");
    //print_str_array(retval);
    print_or_delete(argv[1],tofreeline,malval,freeval,retval);
    free(tofreeline);

    return 0;
}
