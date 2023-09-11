.PHONY: clean all install

myshell: main.c builtin.c builtin_backend.c dirctvs.c err_hndlr.c exec_backend.c exec.c parser.c parser_backend.c
	gcc -o myshell main.c builtin.c builtin_backend.c dirctvs.c err_hndlr.c exec_backend.c exec.c parser.c parser_backend.c

#depend on myshell target to make all
all: myshell
	
clean: 
	rm -f *.o myshell

install: myshell
	sudo cp myshell /usr/bin