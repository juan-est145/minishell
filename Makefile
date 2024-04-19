LIBFT_PATH = libft
SRC_PATH = src

NAME = fdf

SCRS = $(SRC_PATH)/main.c\

OBJS = $(SCRS:.c=.o)

HEADER = $(SRC_PATH)/minishell.h

COMPILER = $(CC)

CFLAGS = -Wall -Werror -Wextra
EXEC-NAME-FLAG = -o

RM = rm -rf

GIT_SUBMODULES = git submodule init && git submodule update

all: make-library $(NAME)

make-library:
	$(GIT_SUBMODULES)
	$(MAKE) -C $(LIBFT_PATH)

make-library-debug:
	$(MAKE) -C $(LIBFT_PATH) debug

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
debug: make-library-debug $(NAME)