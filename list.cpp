/*** Copyright (c) 2017 Nnmjywg ***/

#include <iostream>
#include <direct.h>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include "tinydir.h"

char Buffer[MAX_PATH];
char *home = std::getenv("USERPROFILE");

int dirExists(LPCSTR dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in);
  if (dirName_in == NULL){
    return 0; // So that stuff works
  }
  if(ftyp == INVALID_FILE_ATTRIBUTES)
    return -1;  //something is wrong with your path!

  if(ftyp &FILE_ATTRIBUTE_DIRECTORY)
    return 0;   // this is a directory!

  return 1;    // this is not a directory!
}

int list (char* d)
{
    tinydir_dir dir;
    if(d == NULL)
    {
        tinydir_open(&dir, ".");
    }
    else
    {
        tinydir_open(&dir, d);
    }
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (file.is_dir)
        {
            printf("(DIR)\t%s", file.name);
        }
        else
        {
            printf("\t%s", file.name);
        }
        printf("\n");
        tinydir_next(&dir);
    }
    tinydir_close(&dir);
    return 0;
}

int main(int argc, char* argv[])
{
    if (dirExists(argv[1]) == -1)
    {
        std::string error0 = "Directory does not exist: " + std::string(argv[1]);
        std::cerr << error0 << std::endl;
        return 1;
    }

    if (dirExists(argv[1]) == 1)
    {
        std::string error1 = "Is a file: " + std::string(argv[1]);
        std::cerr << error1 << std::endl;
        return 1;
    }
        
    if(dirExists(argv[1]) == 0)
    {
        _chdir(argv[1]);
        std::cout << std::endl;
    }
    list(argv[1]);
    return 0;
}