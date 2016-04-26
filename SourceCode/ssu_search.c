#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fnmatch.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include "ssu_find.h"
#include "ssu_search.h"

void searchFile(char *path, struct findSignal *fs)
{
     struct stat statbuf;
     char *tmp = fs->np;
     char *tmp2 = NULL;
     int print = 1;

     if(lstat(path, &statbuf) < 0){
          fprintf(stderr, "can't read %s\n", path);
          return;
     }
     
     // pattern matching
     if(fs->np != NULL){
          if(fnmatch(fs->np, path, 0)) // unmatched
               print = 0;
     }

     // type option
     if(fs->cntType == 1){
          if(S_ISDIR(statbuf.st_mode) != 0){
               if(fs->is_d == 1 && print)
                    printf("%s\n", path);
               if(fs->cntStart == 0 && fs->cntName == 1 && print){
                    fs->np = NULL;
                    searchDir(path, fs);
                    fs->np = tmp;
               }
               if(fs->np != NULL && print == 1){
                    tmp2 = (char *)malloc(strlen(path)+strlen(fs->firstNp));
                    strncpy(tmp2, path, strlen(path));
                    strncpy(&tmp2[strlen(path)], &fs->firstNp[1], strlen(fs->firstNp)-1);
                    tmp2[strlen(path)+strlen(fs->firstNp)-1] = '\0';
                    fs->np = tmp2;
               }
               searchDir(path, fs);
               if(tmp2!=NULL){
                    free(tmp2);
                    fs->np = tmp;
               }
               return;
          }
          
          if(print)
          switch(statbuf.st_mode & S_IFMT){
               case S_IFREG:
                    if(fs->is_f == 1)
                         printf("%s\n", path);
                    break;
               case S_IFBLK:
                    if(fs->is_b == 1)
                         printf("%s\n", path);
                    break;
               case S_IFCHR:
                    if(fs->is_c == 1)
                         printf("%s\n", path);
                    break;
               case S_IFIFO:
                    if(fs->is_p == 1)
                         printf("%s\n", path);
                    break;
               case S_IFSOCK:
                    if(fs->is_s == 1)
                         printf("%s\n", path);
                    break;
               case S_IFLNK:
                    if(fs->is_l == 1)
                         printf("%s\n", path);
                    break;
               default:
                    pr_findUsg();
                    break;
          }
          return;
     }

     if(S_ISDIR(statbuf.st_mode) == 0){
          if(print){
               printf("%s\n", path);
		  }
          return;
     }
     else{
          // directory
          if(print)
               printf("%s\n", path);
          if(fs->cntStart == 0 && fs->cntName == 1 && print){
                    fs->np = NULL;
                    searchDir(path, fs);
                    fs->np = tmp;
          }
          if(fs->np != NULL && print == 1){
			   	tmp2 = (char *)malloc(strlen(path)+strlen(fs->firstNp));
               	strncpy(tmp2, path, strlen(path));
               	strncpy(&tmp2[strlen(path)], &fs->firstNp[1], strlen(fs->firstNp)-1);
               	tmp2[strlen(path)+strlen(fs->firstNp)-1] = '\0';
               	fs->np = tmp2;
          		searchDir(path, fs);
				free(tmp2);
                fs->np = tmp;
          }else{
			  searchDir(path, fs);
		  }
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
		  memset(nPath, '\0', p+d+2);
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
