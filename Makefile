##
## Makefile for minishell2 in /home/boulay_b/Rendu/SE2/PSU/PSU_2014_minishell2
##
## Made by Boulay Arnaud
## Login   <boulay_b@epitech.net>
##
## Started on  Wed Mar 11 19:12:25 2015 Boulay Arnaud
## Last update Wed Mar 11 19:12:26 2015 Boulay Arnaud
##

NAME	= mysh

SRCSFO	= sources/

SRCS	= $(SRCSFO)main.c \
	  $(SRCSFO)get_next_line.c \
	  $(SRCSFO)exec.c \
	  $(SRCSFO)pwd.c \
	  $(SRCSFO)cd.c \
	  $(SRCSFO)env.c \
	  $(SRCSFO)env_builtin.c \
	  $(SRCSFO)list.c \
	  $(SRCSFO)signal.c \
	  $(SRCSFO)strtowordtab.c \
	  $(SRCSFO)listtotab.c \
	  $(SRCSFO)string.c \
	  $(SRCSFO)builtins.c \
	  $(SRCSFO)tools.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Iinclude/ -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
