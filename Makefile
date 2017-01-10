##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Tue Jan 10 16:37:02 2017 
##

SRC	=	env/env.c			\
		env/key.c			\
		parse/cmds.c			\
		parse/args.c			\
		prompt/prompt.c			\
		exec/exec.c			\
		exec/fork.c			\
		exec/builtins/exit.c		\
		exec/builtins/cd.c		\
		exec/builtins/setenv.c		\
		exec/builtins/unsetenv.c	\
		misc/str.c			\
		misc/misc.c			\
		main.c


OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

LIB_F	=	./lib/

LIB	=	-lmyprintf -lgnl

INCLUDE	=	-I./include/

CFLAGS	+=	 $(INCLUDE) -g	


all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -L$(LIB_F) $(LIB)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONE: all clean fclean re
