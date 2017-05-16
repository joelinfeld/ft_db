NAME = libftprintf.a

SRCS = ft_helpers.c ft_parse_spec.c ft_get_arg_str.c ft_to_multibyte.c ft_print_spec.c ft_printf.c ft_isdigit.c ft_isupper.c ft_itoa.c ft_itoa_base.c ft_memset.c ft_strdup.c ft_strequ.c ft_strlen.c ft_strndup.c ft_strnew.c ft_tolower.c ft_crash.c ft_memalloc.c ft_putstr.c ft_putendl.c ft_atoi.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(OBJS): $(SRCS)
	gcc -Wall -Wextra -Werror -c $(SRCS)

$(NAME): $(OBJS) 
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
