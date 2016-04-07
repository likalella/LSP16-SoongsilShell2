#ifndef SSU_FUNCTION_H
#define SSU_FUNCTION_H

void ssu_shell(void);
void ssu_find(int, char*[]);

// ssu command's name and function pointer
struct ssu_function{
     char* cmd;
     void (*func)(int, char* []);
};

#endif
