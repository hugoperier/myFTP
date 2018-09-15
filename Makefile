##
## EPITECH PROJECT, 2018
## make
## File description:
## 
##

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -g3

NAME	= server

SRCS	= 	$(addprefix server_/,	\
		main.c			\
		login.c			\
		rfc9591.c		\
		gnl.c			\
		rfc9592.c		\
		rfc959.c		\
		server.c		\
		fnct_string.c		\
		wrapper.c		\
		data_transfert.c)

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
