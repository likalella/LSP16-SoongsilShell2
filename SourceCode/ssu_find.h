#ifndef SSU_FIND_H
#define SSU_FIND_H

// struct findSignal has [TYPE] info.
struct findSignal{
     int cntType;
     int cntOpt;
     int cntName;
     int cntStart;
     int is_f;
     int is_d;
     int is_b;
     int is_c;
     int is_p;
     int is_l;
     int is_s;
     char *np;
};

void pr_findUsg(void);
void ssu_find(int , char *[]);

#endif
