CC = cc

CFLAGS = -Wall -Wextra -Wno-deprecated-declarations

NAME = mini_os

INCLUDES = ./includes

SRCS = ./srcs/

HEADER = bases.h commands.h mkdir_.h ls.h

SRC = $(SRCS)mini_os.c $(SRCS)bases.c ${SRCS}mkdir_.c ${SRCS}ls.c

OBJS = $(SRC:.c=.o)



all: $(NAME)



%.o: %.c

	$(CC) $(CFLAGS) -c $^ -I $(INCLUDES) -o $@



$(NAME): $(OBJS)

	$(CC) $(CFLAGS) -o $@ $(OBJS)



clean:

	rm -f $(OBJS)



fclean: clean

	rm -f $(NAME)



re: fclean all



.PHONY: make clean fclean re all