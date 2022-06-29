#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>


#define MAXINODE 5

#define READ 1
#define WRITE 2

#define MAXFILESIZE 2048

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1
#define END 2

typedef struct superblock
{
    int TotalInodes;
    int FreeInodes;
}SUPERBLOCK,*PSUPERBLOCK;

typedef struct inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;
    char *Buffer;
    int LinkCount;
    int ReferanceCount;
    int permission; //1 23
    struct inode *next;
}INODE,*PINODE,**PPINODE;

typedef struct filetable
{
    int readoffset;
    int writeoffset;
    int count;
    int mode; // 1 2 3
    PINODE ptrinode;
}FILETABLE ,*PFILETABLE;

typedef struct ufdt
{
    PFILETABLE ptrfiletable;
}UFDT;

UFDT UFDTArr[50];
SUPERBLOCK SUPERBLOCKOBJ;
PINODE head = NULL;

void man(char *name)
{
    if(name==NULL)return;

    if(strcmp(name,"create")==0)
    {
        printf("Description: Used to create new regular file.\n");
        printf("Usage : create File_name Permission\n");
    }
    else if(strcmp(name,"read")==0)
    {
        printf("Description : Used to read data from regular\n");
        printf("Usage : read File_name No_Of_Bytes_To_Read\n");
    }
    else if(strcmp(name,"write")==0)
    {
        printf("Description : Used to write into regular file\n");
        printf("Usage : write File_name\nAfter this enter the data that we want to write\n");
    }
    else if(strcmp(name,"ls")==0)
    {
        printf("Description : Used to list all information of files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp(name,"stat")==0)
    {
        printf("Description : Usage to display information of file.\n");
        printf("Usage: stat File_name\n");
    }
    else if(strcmp(name,"fstat")==0)
    {
        printf("Description :Used to display information of file\n");
        printf("Usage :stat File_Descriptior\n");
    }
    else if(strcmp(name,"truncate")==0)
    {
        printf("Description: Used to remove data from file\n");
        printf("Usage: truncate File_name\n");
    }
    else if (strcmp(name,"open")==0)
    {
        printf("Description : Used to open existing file\n");\
        printf("Usage :open File_name mode\n");
    }
    else if(strcmp(name,"close")==0)
    {
        printf("Description : Used to close opened file\n");
        printf("Usage:open File_name mode\n");
    }
    else if(strcmp(name,"closeall")==0)
    {
        printf("Description: Used to close all opened file\n");
        printf("Usage: closeall\n");
    }
    else if(strcmp(name,"lseek")==0)
    {
        printf("Description:Used to change the file offset\n");
        printf("Usage : lseek File_Name\n");
    }
    else if(strcmp(name,"rm")==0)
    {
        printf("Descrption : Used to delete the file\n");
        printf("Usage : rm File_Name\n");
    }
    else
    {
        printf("ERROR : No manual entry available.\n");
    }
}

void DisplayHelp()
{
    printf("ls : To List out all files\n");
    printf("clear : To clear console\n");
    printf("open : To open the file\n");
    printf("close : To close the opened file\n");
    printf("closeall: To close all opened files\n");
    printf("read : To Read the contents into file\n");
    printf("write:To Write contents into file\n");
    printf("exit: To terminate file sysem\n");
    printf("stat : To Dispaly information of file usinf name\n");
    printf("fstat : To Dispaly information of file using file descriptor\n");
    printf("truncate: To Remove all the data from file \n");
    printf("rm : To delete the file\n");
}

int GetFDFromName(char *name)
{
    int i=0;

    while(i<MAXINODE)
    {
        if(UFDT[i].ptrfiletable!=NULL)
        {
            if(strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName),name)==0)
            {
                break;
            }
            i++;
        }
    }    
    if(i==MAXINODE)
    {
        return -1;
    } 
    else
    {
        return i;
    }
}

PINODE Get_Inode(char *name)
{
    PINODE temp = head;
    int i=0;

    if(name==NULL)
    {
        return NULL;
    }
    while(temp!=NULL)
    {
        if(strcmp(name,temp->FileName)==0)
        {
            break;
        }
        temp = temp->next;
    }
    return temp;
}

void CreateDILB()
{
    
}