#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "ssu_function.h"

struct ssu_function cmdList[] = {
     {"ssu_find", ssu_find},
     {NULL}
};

int main(void)
{
     while(1){
          ssu_shell();
     }
     return 0;
}

