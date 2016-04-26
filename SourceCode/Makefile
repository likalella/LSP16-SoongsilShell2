shell:main.o ssu_find.o ssu_search.o ssu_shell.o
	gcc -o shell main.o ssu_find.o ssu_search.o ssu_shell.o

main.o:ssu_function.h main.c
	gcc -c main.c
ssu_shell.o: ssu_function.h ssu_shell.h ssu_shell.c
	gcc -c ssu_shell.c
ssu_find.o:ssu_function.h ssu_find.h ssu_search.h ssu_find.c
	gcc -c ssu_find.c
ssu_search.o: ssu_find.h ssu_search.h ssu_search.c
	gcc -c ssu_search.c
