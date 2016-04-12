#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include "ssu_find.h"

void searchFile(char *path, struct findSignal *fs)
{
     struct stat statbuf;
     struct dirent *drip;
     DIR *dp;
     char aPath[PATH_MAX] = "";
     char nPath[PATH_MAX] = "";
     
     if(stat(path, &statbuf) < 0){
          fprintf(stderr, "can't read %s\n", path);
          return;
     }

     // *******  maybe pattern matching here. *******

     // get Absolute_pathname
     if(realpath(path, aPath) == NULL){
          fprintf(stderr, "can't get ablsolute pathname %s\n", path);
          return;
     }

     // type option
     if(fs->cntType == 1){
     switch(statbuf.st_mode & S_IFMT){
               case S_IFREG:
                    if(fs->is_f == 1)
                         printf("%s\n", aPath);
                    break;
               case S_IFBLK:
                    if(fs->is_b == 1)
                         printf("%s\n", aPath);
                    break;
               case S_IFCHR:
                    if(fs->is_c == 1)
                         printf("%s\n", aPath);
                    break;
               case S_IFIFO:
                    if(fs->is_p == 1)
                         printf("%s\n", aPath);
                    break;
               case S_IFSOCK:
                    if(fs->is_s == 1)
                         printf("%s\n", aPath);
                    break;
               case S_IFLNK:
                    if(fs->is_s == 1)
                         printf("%s\n", aPath);
                    break;
               case S_IFDIR:

                    break;
               default:
                    pr_findUsg();
          }
          return;
     }

     if(S_ISDIR(statbuf.st_mode) == 0){
          printf("%s\n", aPath);
          return;
     }
     else{
          printf("%s\n", aPath);
          return;
     }
}
