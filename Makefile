CC = gcc
NAME = minishell
FLAGS = -g
LIBFT = libft/libft.a

SRCS = main.c				\
		tools.c				\
		create_node.c		\
		get.c				\
		get_utlis.c			\
		get_utlis_1.c		\
		get_utlis_2.c		\
		functions.c			\
		functions_1.c		\
		update.c			\
		parsing.c			\
		check_quotes.c		\
		handler.c			\
		handler_utlis.c		\
		handler_utlis_1.c	\
		free.c				\
		env.c				\
		builtin/unset.c				\
		builtin/echo.c				\
		builtin/export.c	\
		builtin/export_utlis.c	\
		builtin/ft_cd.c		\
		builtin/ft_cd_oldpwd.c		\
		builtin/ft_cd_utlis.c		\
		builtin/ft_pwd.c	\
		builtin/ft_env.c	\
		builtin/ft_exit.c	\
		utlis.c				\
		utlis_1.c			\
		redr.c				\
		redr_utlis.c		\
		redr_utlis_1.c		\
		./start/convert_parssing.c \
		./start/exec/exec.c \
		./start/utils/utils.c \
		./start/utils/utils_1.c \
		./start/utils/cmd_utils.c \
		./start/exec/her_rd/infile_and_outfile.c \
		./start/exec/her_rd/herdoc.c \

READLINE =  -lreadline -L /Users/ael-mahm/homebrew/opt/readline/lib/ -I /Users/ael-mahm/homebrew/opt/readline/include/

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@cd libft && make

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) ${READLINE} -o $@

clean:
	@rm -rf $(OBJS)
	@cd libft && make clean

fclean: clean
	@rm -rf $(NAME)
	@cd libft && make fclean

re: fclean all