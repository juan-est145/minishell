LIBFT_PATH = libft

NAME = minishell

SCRS = main_miguel.c\
		archive_env.c\
		archive_utils.c\
		builtings.c\
		
OBJS = $(SCRS:.c=.o)

HEADER = prueba.h

COMPILER = $(CC)

CFLAGS = -Wall -Werror -Wextra 
EXEC-NAME-FLAG = -lreadline -lhistory -o

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(COMPILER) $(CFLAGS) $(OBJS) $(EXEC-NAME-FLAG) $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

debug: CFLAGS += -g
debug: $(NAME)
