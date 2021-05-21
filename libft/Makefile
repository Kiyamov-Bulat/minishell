NAME	   = libft.a

INC_DIR	   = .

SRCS	   = ft_atoi.c ft_bzero.c ft_calloc.c ft_desc_shellsort.c ft_free_matrix.c ft_getchar.c \
				ft_hasc.c ft_indexof.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_isspace.c ft_isstrempty.c ft_isstrnum.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
				ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
				ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putc.c ft_putchar_fd.c \
				ft_putendl.c ft_putendl_fd.c ft_putnbr_fd.c ft_puts.c ft_putstr_fd.c ft_qsort.c ft_shellsort.c ft_split.c \
				ft_ssplit.c ft_strchr.c ft_strcpy.c ft_strdup.c ft_strequal.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strstr.c ft_strtrim.c ft_substr.c ft_swap.c ft_tolower.c \
				ft_toupper.c get_next_line.c get_next_line_utils.c 

OBJS	   = ${SRCS:.c=.o}

DEPS	   = libft.h

CFLAGS	   = -Wall -Wextra -Werror -I${INC_DIR}

AR	   = ar rc

.c.o :		${DEPS}
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
		${AR} ${NAME} $?

clean:		
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:		fclean all

.PHONY:		all clean fclean re