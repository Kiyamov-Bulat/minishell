NAME		= minishell
INC_DIR		= ./executor
SRC_DIR		= .
CC			= gcc
TEMP		= parse_line.c parse_dquote.c parse_squote.c parse_dollar.c parse_utils.c get_abs_path_command.c \
			  get_abs_path_command2.c minishell_utils.c minishell_utils2.c minishell_utils3.c set_last_red_file.c \
			  cmd.c free_cmd.c ft_realloc.c free_dpointer.c error_handler.c signal_handler.c ft_cd.c ft_pwd.c \
			  ft_env.c ft_exit.c ft_unset.c ft_export.c ft_echo.c ft_getch.c executor.c executor2.c repair_cmd.c \
			  error_handler_command.c ft_export2.c repair_cmd2.c set_last_red_file2.c main.c
			  
SRCS		= $(addprefix $(SRC_DIR)/, $(TEMP))
OBJS		= $(SRCS:.c=.o)
LIBFT_DIR	= libft
LIBS		= -L$(LIBFT_DIR) -lft
DEBUG		= -D DEBUG
DEPS		= minishell.h
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I.
SMAKE		= make -s

%.o:		%.c $(DEPS)
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

libft:
			make -C $(LIBFT_DIR)

$(NAME):	$(OBJS)
			$(SMAKE) libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

test:		CFLAGS += $(DEBUG)
test:		$(NAME)
			./$(NAME) 

clean:
			rm -rf $(OBJS)
			$(SMAKE) clean -C $(LIBFT_DIR)

fclean:		clean
			rm -rf $(NAME)
			$(SMAKE) fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re libft
