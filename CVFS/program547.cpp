/////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
/////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

/////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
/////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

/////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
//
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :   BootBlock
//  Description     :   Holds the information to boot the OS
//
/////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :   SuperBlock
//  Description     :   Holds the information about the file system
//
/////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :   Inode
//  Description     :   Holds the information about the file
//
/////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode* PINODE;
typedef struct Inode** PPINODE;

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :   FileTable
//  Description     :   Holds the information about the opened file
//
/////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable* PFILETABLE;

/////////////////////////////////////////////////////////////////////////
//
//  Structure Name  :   UAREA
//  Description     :   Holds the information about the process file
//
/////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

/////////////////////////////////////////////////////////////////////////
//
//  Global Variables or objects used in the Project
//
/////////////////////////////////////////////////////////////////////////

BootBlock bootObj;
SuperBlock superObj;
UAREA uareaObj;

PINODE head = NULL;

/////////////////////////////////////////////////////////////////////////
//
// FunctionName : InitialiseUAREA
// Description  : It is used to Initialise UAREA members
// Author       : Pravin Ashok Chavan
// Date         : 13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaObj.ProcessName, "Myexe");

    int i = 0;

    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareaObj.UFDT[i] = NULL;
    }
    printf("Marvellous CVFS : UAREA gets initialised succesfully \n");
}

/////////////////////////////////////////////////////////////////////////
//
// FunctionName : InitialiseSuperBlock
// Description  : It is used to Initialise Super Block members
// Author       : Pravin Ashok Chavan
// Date         : 13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superObj.TotalInodes = MAXINODE;
    superObj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super Block gets initialised succesfully \n");
}

/////////////////////////////////////////////////////////////////////////
//
// FunctionName : CreateDILB
// Description  : It is used to create LinkedList of inodes
// Author       : Pravin Ashok Chavan
// Date         : 13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for ( i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if (temp == NULL)   // LL is Empty
        {
            head = newn;
            temp = head;
        }
        else                // LL Contains atleast one node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }

    printf("Marvellous CVFS : DILB gets Created succesfully \n");
    
}

/////////////////////////////////////////////////////////////////////////
//
// FunctionName : StartAuxillaryDataInitialisation
// Description  : It is used to call all such function which are used to
//                initialise auxillary data
// Author       : Pravin Ashok Chavan
// Date         : 13/01/2026
//
/////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootObj.Information,"Booting process of Marvellous CVFS is done");

    printf("%s\n", bootObj.Information);

    InitialiseSuperBlock();

    CreateDILB();
    
    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary Data initialised succesfully\n");
}

/////////////////////////////////////////////////////////////////////////
//
// FunctionName : DisplayHelp
// Description  : It is used to display help page
// Author       : Pravin Ashok Chavan
// Date         : 14/01/2026
//
/////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("------------------------------------------------------\n");
    printf("------------- Marvellous CVFS Help Page --------------\n");
    printf("------------------------------------------------------\n");

    printf("man     : It is used to display manual page\n");
    printf("clear   : It is used to clear the terminal\n");
    printf("create  : It is used to create a new file\n");
    printf("write   : It is used to write the data into file\n");
    printf("read    : It is used to read the data from the file\n");
    printf("stat    : It is used to dispaly statistical information\n");
    printf("unlink  : It is used to delete the file\n");
    printf("exit    : It is used to terminate Marvellous CVFS\n");

    printf("------------------------------------------------------\n");

}

/////////////////////////////////////////////////////////////////////////
//
// FunctionName : ManPageDisplay
// Description  : It is used to display manual page
// Author       : Pravin Ashok Chavan
// Date         : 14/01/2026
//
/////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if((strcmp("ls", Name)) == 0)
    {
        printf("About : It is used to list the names of all file\n");
        printf("Usage : ls\n");

    }
    else if ((strcmp("man",Name)) == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");
    }
    else if ((strcmp("exit",Name)) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
    else if ((strcmp("clear",Name)) == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");
    }
    else
    {
        printf("No manual entry for %s\n", Name);
    }
    
    
}

/////////////////////////////////////////////////////////////////////////
//
//  Entry Point Function of the Project
//
/////////////////////////////////////////////////////////////////////////

int main ()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;

    StartAuxillaryDataInitialisation();

    printf("------------------------------------------------------\n");
    printf("-------- Marvellous CVFS Started Succesfully ---------\n");
    printf("------------------------------------------------------\n");

    // Infinite Listening Shell
    while (1)
    {
        fflush(stdin);

        strcpy(str, "");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str), stdin);

        iCount = sscanf(str,"%s %s %s %s  %s", Command[0], Command[1], Command[2], Command[3], Command[4]);  

        fflush(stdin);

        if (iCount == 1)
        {
            if ((strcmp("exit",Command[0])) == 0)
            {
               printf("Thank you for using Marvellous CVFS\n");
               printf("Deallocating all the allocated resources \n");

               break;
            }
            else if((strcmp("ls", Command[0])) == 0)
            {
                printf("Inside ls\n");
            }
            else if ((strcmp("help", Command[0])) == 0)
            {
                DisplayHelp();
            }
            else if((strcmp("clear", Command[0])) == 0)
            {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
            

        } // end of if 1
        else if (iCount == 2)
        {
            if ((strcmp("man", Command[0])) == 0)
            {
                ManPageDisplay(Command[1]);
            }
            
        } // end of else if 2
        else if (iCount == 3)
        {
            
        } // end of else if 3
        else if (iCount == 4)
        {
            
        } // end of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information");
        } // end of else
        
    } // end of while
    

    return 0;
} // end of main