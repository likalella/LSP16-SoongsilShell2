#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fnmatch.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "ssu_find.h"
#include "ssu_search.h"

void searchFile(char *path, struct findSignal *fs)
{
     struct stat statbuf;
     char aPath[PATH_MAX] = "";
     
     // *******  maybe pattern matching here. *******

     // get Absolute_pathname
     if(realpath(path, aPath) == NULL){
          fprintf(stderr, "can't get ablsolute pathname %s\n", path);
          return;
     }

     if(lstat(path, &statbuf) < 0){
          fprintf(stderr, "can't read %s\n", path);
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
                    if(fs->is_d == 1){
                         printf("%s\n", aPath);
                    }
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
          // directory
          printf("directory\n");
          printf("dir : %s\n", aPath);
          searchDir(aPath, fs);
          return;
     }
}

void searchDir(char *path, struct findSignal *fs)
{
     struct dirent *dirp;
     DIR *dp;
     char *nPath;
     int p, d;

     if((dp = opendir(path)) == NULL){
          fprintf(stderr, "can't open %s\n", path);
          return;
     }

     while((dirp = readdir(dp)) != NULL){
          if(strcmp(dirp->d_name, ".") == 0 ||
              strcmp(dirp->d_name, "..") == 0)
               continue;
          p = strlen(path);
          d = strlen(dirp->d_name);
          nPath = (char *)malloc(p+d+2);
          strcpy(nPath, path);
          if(path[p-1] != '/'){
               nPath[p] = '/';
               strcpy(&nPath[p+1], dirp->d_name);
               nPath[p+d+1] = '\0';
          }
          else{
               strcpy(&nPath[p], dirp->d_name);
               nPath[p+d] = '\0';
          }

          searchFile(nPath, fs);
          free(nPath);
     }
     closedir(dp);
}
