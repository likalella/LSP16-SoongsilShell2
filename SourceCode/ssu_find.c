#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "ssu_function.h"
#include "ssu_find.h"

// Print Usage
void pr_findUsg(void){
     printf("Usage: ssu_find [OPTION]\n");
     printf("       ssu_find FILENAME or PATTERN [TYPE]\n");
     printf("       ssu_find START_PATH -name FILENAME|PATTERN [TYPE]\n");
     printf("       ssu_find START_PATH FILENAME|PATTERN [TYPE]\n");
     printf("[OPTION]: -name FILENAME or PATTERN\n");
     printf("  [TYPE]: -type -{f|d|b|c|p|l|s}\n");
}

void ssu_find(int argc, char *argv[]){
     struct findSignal fs;
     fs.is_f = 0;
     fs.is_d = 0;
     fs.is_b = 0;
     fs.is_c = 0;
     fs.is_p = 0;
     fs.is_l = 0;
     fs.is_s = 0;
     char *name = NULL;
     char *pattern = NULL;
     char *sPath = NULL;
     int i, j;
     int cntArg = 0, cntOpt = 0, cntType = 0;
     struct stat file_info;

     // Parsing
     for(i=1; i<argc; i++){
          // argv[i] start '-'
          if(*argv[i] == '-'){
               if((strcmp(argv[i], "-name")) == 0){
                    // [OPTION]
                    if(++cntOpt != 1){
                         pr_findUsg();
                         return;
                    }
                    
                    if(++i < argc){
                         if(cntArg == 1){
                              sPath = pattern;
                              pattern = NULL;
                         }
                         name = argv[i];
                    }
                    else{
                         pr_findUsg();
                         return;
                    }
               }
               else if((strcmp(argv[i], "-type")) == 0){
                    // [TYPE]
                    if(++cntType != 1){
                         pr_findUsg();
                         return;
                    }
                    
                    if(++i < argc){
                         if(strlen(argv[i]) != 2){
                              pr_findUsg();
                              return;
                         }
                         if((strcmp(argv[i], "-f")) == 0)
                              fs.is_f = 1;
                         else if((strcmp(argv[i], "-d")) == 0)
                              fs.is_d = 1;
                         else if((strcmp(argv[i], "-b")) == 0)
                              fs.is_b = 1;
                         else if((strcmp(argv[i], "-c")) == 0)
                              fs.is_c = 1;
                         else if((strcmp(argv[i], "-p")) == 0)
                              fs.is_p = 1;
                         else if((strcmp(argv[i], "-l")) == 0)
                              fs.is_l = 1;
                         else if((strcmp(argv[i], "-s")) == 0)
                              fs.is_s = 1;
                         else{
                              pr_findUsg();
                              return;
                         }
                    }
                    else{
                         pr_findUsg();
                         return;
                    }
               }
               else{
                    // wrong input, no option.
                    pr_findUsg();
                    return;
               }
          }
          else{
               if(cntArg == 0){
                    pattern = argv[i]; 
               }
               else if(cntArg == 1){
                    sPath = pattern;
                    pattern = argv[i];
               }
               else{
                    pr_findUsg();
                    return;
               }
               cntArg++;
          }
     }

     
}
