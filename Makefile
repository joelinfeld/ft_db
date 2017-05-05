NAME=ft_db
CC=gcc
CFLAGS=-Wall -Wextra -Werror

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)

LIB_DIR = libft
LIB_LINK = -L $(LIB_DIR) -lft
INC = -I libft/includes

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(LIB_LINK) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^

clean:
	make -C $(LIB_DIR) clean
	-rm -f $(OBJS)

fclean: clean
	make -C $(LIB_DIR) fclean
	-rm -f $(NAME)

re: fclean all
