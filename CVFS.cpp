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

UFDT UFDTArr[MAXINODE];
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
        if(UFDTArr[i].ptrfiletable!=NULL)
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
    int i =1;
    PINODE newn = NULL;
    PINODE temp = head;

    while(i<=MAXINODE)
    {
         newn = (PINODE)malloc(sizeof(INODE));
         newn->LinkCount = 0;
         newn->ReferanceCount=0;
         newn->FileType=0;
         newn->FileSize=0;
         newn->Buffer = NULL;
         newn->next = NULL;
         newn->InodeNumber = 0;

            if(temp==NULL)
            {
                head =newn;
                temp  = head;
            }
            else
            {
                temp->next = newn;
                temp = temp->next;
            }
            i++;
    }
    printf("DILB created succesfully\n");
}

void InitialiseSuperBlock()
{
    int i = 0;
    while(i<MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL;
        i++;
    }
    
    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.Freenode = MAXINODE;
}
int CreateFile(char *name ,int permission)
{
    int i=0;
    PINODE temp =head;
}






int main()
{
    char *ptr =NULL;
    int ret =0,fd=0,count=0;
    char command[4][80],str[80],arr[1024];

    InitialiseSuperBlock();
    CreateDILB();

    while(1)
    {
        fflush(stdin);
        strcpy(str,"");

        printf("\nVFS : >");

        fgets(str,80,stdin); // scanf("%[^'\n']s",str);
        count = sscanf(str,"%s %s %s %s",command[0],command[1],command[2],command[3]);
        if(count==1)
        {
            if(strcmp(command[0],"ls")==0)
            {
                ls_file();
            }
            else if(strcmp(command[0],"closeall")== 0)
            {

            }
            else if(strcmp(command[0],"clear")== 0)
            {
                
            }
            else if(strcmp(command[0],"help")== 0)
            {
                
            }
            else if(strcmp(command[0],"exit")== 0)
            {
                
            }
            else
            {
                printf("\nERROR : Command not fount!!\n");
                continue;
            }                                                
        }
        else if(count==2)
        {
            if(strcmp(command[0],"stat")==0)
            {
                ret = stat_file(command[1]);
                if(ret == -1)
                {
                    printf("ERROR: Incorrect parameter\n");
                }
                if(ret == -2)
                {                 
                    printf("ERROR : There is no such file\n");
                }
                continue;    
            }
            else if(strcmp(command[0],"fstat")==0)
            {

            }
            else if(strcmp(command[0],"close")==0)
            {
                
            }
            else if(strcmp(command[0],"rm")==0)
            {
                
            }
            else if(strcmp(command[0],"man")==0)
            {
                
            }
            else if(strcmp(command[0],"write")==0)
            {
                
            }
            else if(strcmp(command[0],"truncate")==0)
            {
                
            }
            else
            {
                printf("\nERROR : Command not fount!!\n");
                continue;
            }                                                                        
        }
    else if(count == 3)
    {
        if(strcmp(command[0],"create")== 0)
        {
            ret = CreateFile(command[1],atoi(command[2]));
            if(ret>=0)
            {
                printf("file is successfully created with file descriptor : %d\n",ret);
            }
            if(ret == -1)
            {
                printf("ERROR: Incorrect parameter:");
            }
            if(ret== -2)
            {
                printf("There is no inodes\n");
            }
            if(ret == -3)
            {
                printf("ERROR : File already exist\n");
            }
            if(ret == -4)
            {
                printf("ERROR : Memory allocation failure\n");
            }
            continue;
        }
        
        else if(strcmp(command[0],"open")==0)
        {
            ret  = OpenFile(command[1],atoi(command[2]));
                if(ret>=0)
                {
                    printf("file is successfully opened with file descriptor : %d\n",ret);
                }
                if(ret == -1)
                {
                    printf("ERROR: Incorrect parameter:");
                }
                if(ret== -2)
                {
                    printf("ERROR: File not present\n");
                }
                if(ret == -3)
                {
                    printf("ERROR : Permission denied\n");
                }
                continue;            
        }
        else  if((command[0],"read")==0)
        {
            fd = GetFDFromName(command[1]);
            if(fd== -1)
            {
                printf("Error : Incorrect parameter\n");
                continue;
            }
            ptr = (char*)malloc(sizeof(atoi(command[2]))+1);
            if(ptr==NULL)
            {
                printf("Error : Memory allocation failed\n");
                continue;
            }
            ret = ReadFile(fd,ptr,atoi(command[2]));
                if(ret == -1)
                {
                    printf("ERROR: File not Exitsting\n");
                }
                if(ret== -2)
                {
                    printf("Error: Permission denied\n");
                }
                if(ret == -3)
                {
                    printf("ERROR : Reached at the end of file\n");
                }
                if(ret == -4)
                {
                    printf("ERROR : It is not regukar file\n");
                }
                else if(ret==0)
                {
                    printf("Error: File empty\n");
                }
                else if(ret > 0)
                {
                    write(2,ptr,ret);
                }            
                continue;
        }
        else
        {
            printf("\nError : Command not found!!\n");
            continue;
        }
    }
    
    else if(count == 4)
    {
        if(strcmp(command[0],"lseek")== 0)
        {
            fd = GetFDFromName(command[1]);
            if(fd == -1)
            {
                printf("Error : Incorrect parameter\n");
                continue;
            }
            ret = lseekFile(fd,atoi(command[2]),atoi(command[3]));
            if(ret == -1)
            {
                printf("Error : Unable to perform lssek\n");
            }
        }
        else{
            printf("\nError : Command not found!!\n");
            continue;
        }
    }
    else
    {
        printf("\nError : Command not found!!\n");
        continue;
    }
}
    return 0 ;    
}