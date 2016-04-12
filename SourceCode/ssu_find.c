#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include "ssu_function.h"
#include "ssu_find.h"
#include "ssu_search.h"

// Print Usage
void pr_findUsg(void){
     printf("Usage: ssu_find [OPTION]\n");
     printf("       ssu_find FILENAME or PATTERN [TYPE]\n");
     printf("       ssu_find START_PATH -name FILENAME|PATTERN [TYPE]\n");
     printf("       ssu_find START_PATH FILENAME|PATTERN [TYPE]\n");
     printf("[OPTION]: -name FILENAME|PATTERN\n");
     printf("          [TYPE]\n");
     printf("  [TYPE]: -type -{f|d|b|c|p|l|s}\n");
}

void ssu_find(int argc, char *argv[]){
     struct findSignal fs;
     fs.cntType = 0;
     fs.cntOpt = 0;
     fs.cntName = 0;
     fs.is_f = 0;
     fs.is_d = 0;
     fs.is_b = 0;
     fs.is_c = 0;
     fs.is_p = 0;
     fs.is_l = 0;
     fs.is_s = 0;
     fs.np = NULL;
     char *sPath = NULL;
     int i, j;
     int cntArg = 0;

     // Parsing
     for(i=1; i<argc; i++){
          // argv[i] start '-'
          if(*argv[i] == '-'){
               if((strcmp(argv[i], "-name")) == 0){
                    // [OPTION]
                    if(++fs.cntOpt != 1){
                         // wrong input, dulicated input
                         pr_findUsg();
                         return;
                    }
                    
                    if(++i < argc){
                         if(cntArg == 1){
                              sPath = fs.np;
                              fs.cntName--;
                         }
                         fs.np = argv[i];
                    }
                    else{
                         // wrong input, too few argument
                         pr_findUsg();
                         return;
                    }
               }
               else if((strcmp(argv[i], "-type")) == 0){
                    // [TYPE]
                    if(++fs.cntType != 1){
                         // wrong input, duplicated input
                         pr_findUsg();
                         return;
                    }
                    
                    if(++i < argc){
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
                              // wrong input, invalid type
                              pr_findUsg();
                              return;
                         }
                    }
                    else{
                         // wrong input, too few argument
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
                    if(fs.cntOpt == 1){
                         sPath = argv[i];
                         printf("sPath : %s\n", sPath);
                    }
                    else{
                         fs.np = argv[i];
                         fs.cntName++;
                    }
               }
               else if(cntArg == 1){
                    if(fs.cntOpt != 1){
                         sPath = fs.np;
                         fs.cntName--;
                    }
                    fs.np = argv[i];
                    fs.cntName++;
               }
               else{
                    // wrong input, too many argument
                    pr_findUsg();
                    return;
               }
               cntArg++;
          }
     }
     
     // wrong input, too many filename or pattern
     if(sPath!=NULL && fs.cntName!=0 && fs.cntOpt!=0){
          pr_findUsg();
          return;
     }
    
     //searchFile
     if(sPath == NULL){
          searchFile("/", &fs);
          return;
     }
     else{
          searchFile(sPath, &fs);
          return;
     }
}
