NAME		= libft.a

HEADER 		= libft.h

SRCS		=	ft_atoi.c		\
			ft_bzero.c		\
			ft_calloc.c		\
			ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isspace.c		\
			ft_memset.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_putstr_fd.c		\
			ft_split.c		\
			ft_strchr.c		\
			ft_strcmp.c		\
			ft_strcmp_simple.c	\
			ft_strdup.c		\
			ft_strjoin.c		\
			ft_strlcpy.c		\
			ft_strlen.c		\
			ft_strmapi.c		\
			ft_strncmp.c		\
			ft_strnstr.c		\
			ft_strrchr.c		\
			ft_strtrim.c		\
			ft_substr.c		\
			ft_tolower.c		\
			ft_toupper.c		\
			get_next_line.c 


OBJS	= 		$(SRCS:.c=.o)

LIB		=		ar -rcs
CC		= 		gcc
RM		= 		rm -f
CFLAGS	= 		-Wall -Wextra -Werror

all:			$(NAME)

$(NAME): 		$(OBJS)	Makefile $(HEADER)
				@$(LIB) $(NAME) $(OBJS)

# Depend. adicionales = solo se ejecutara la regla si cambia make o header
%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
