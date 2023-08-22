NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	   ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c\
	   ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strncmp.c \
	   ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	   ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c  \
	   ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c get_next_line_utils.c \
	   ft_printf_recur.c ft_printf_utils.c ft_printf.c \
	   ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_abs.c \
	   ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_swap.c ft_double_free.c ft_split_white.c \
	   ft_strequal.c ft_atod.c

OBJS = $(SRCS:.c=.o)

all: make_mandatory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

make_mandatory: $(OBJS)
	ar rcs $(NAME) $(OBJS)
	touch $@

clean:
	rm -f make_mandatory
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.phony : all clean fclean re
