/*
Move All Files (Dir → Dir)
•Accept source dir and destination dir.
•Move all regular les:
◦Use rename() if same lesystem
◦Else copy + delete
Print count of moved files.
*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<dirent.h>


int main(int argc, char *argv[])
{
    char SrcPath[1024];
    char DestPath[1024];
    struct stat Src_sobj;
    struct stat Dest_sobj;
    int Src_Count = 0;
    int Dest_Count = 0;
    DIR *dp1 = NULL;
    DIR *dp2 = NULL;
    struct dirent *ptr = NULL;

///////////////////////////////////////////////////////////////////////////////////
    //stat(SrcPath, &Src_sobj);
    //stat(DestPath, &Dest_sobj);

///////// For Source file Count/////////////////////////////////////////////////////////////
    dp1 = opendir(argv[1]);   

    if(dp1 == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while((ptr = readdir(dp1)) != NULL)
    {   
        snprintf(SrcPath, sizeof(SrcPath), "%s/%s", argv[1], ptr->d_name);

        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        if (stat(SrcPath, &Src_sobj) == -1)
        {
            continue;
        }

        if(S_ISREG(Src_sobj.st_mode))
        {
            Src_Count++;
        }
        
    }

    printf("Source Files count : %d\n",Src_Count);

////////////////////Files transfer////////////////////////////////////////////////////////////
    
    snprintf(SrcPath, sizeof(SrcPath), "%s", argv[1]);
    snprintf(DestPath, sizeof(DestPath), "%s", argv[2]);
    

    stat(argv[1],&Src_sobj);
    stat(argv[2],&Dest_sobj);

    if(Src_sobj.st_dev == Dest_sobj.st_dev)
    {
        if (rename(SrcPath, DestPath) == -1)
        {
            printf("rename failed: %s\n", strerror(errno));
            return -1;
        }
        printf("File moved successfully\n");
    }

///////// For Destination file Count/////////////////////////////////////////////////////////////
   
    dp2 = opendir(argv[2]);

    if(dp2 == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while((ptr = readdir(dp2)) != NULL)
    {   
        snprintf(DestPath, sizeof(DestPath), "%s/%s", argv[2], ptr->d_name);

        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        if (stat(DestPath, &Dest_sobj) == -1)
        {
            continue;
        }

        if(S_ISREG(Dest_sobj.st_mode))
        {
            Dest_Count++;
        }
        
    }

    printf("Destination Files count : %d\n",Dest_Count);

///////////////////////////////////////////////////////////////////////////////////////
    
    closedir(dp1);
    closedir(dp2);
    
    return 0;
}