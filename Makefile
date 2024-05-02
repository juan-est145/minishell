LIBFT_PATH = libft

SRC_PATH = src
INCLUDE_PATH = include
BUILTINGS_PATH = $(SRC_PATH)/builtings
PARSE_PATH = $(SRC_PATH)/parse
TOKEN_PATH = $(SRC_PATH)/token
PROCESS_AST_PATH = $(SRC_PATH)/process_ast
ERRORS_PATH = $(SRC_PATH)/errors

NAME = minishell

SCRS = $(SRC_PATH)/main.c\
$(TOKEN_PATH)/tokenizer.c\
$(TOKEN_PATH)/tokenizer_utils.c\
$(TOKEN_PATH)/tokenizer_utils2.c\
$(PARSE_PATH)/parse.c\
$(PARSE_PATH)/parse_utils.c\
$(PARSE_PATH)/parse_utils2.c\
$(BUILTINGS_PATH)/archive_env.c\
$(BUILTINGS_PATH)/archive_utils.c\
$(BUILTINGS_PATH)/archive_utils1.c\
$(BUILTINGS_PATH)/archive_utils2.c\
$(BUILTINGS_PATH)/builtings.c\
$(BUILTINGS_PATH)/builtings1.c\
$(BUILTINGS_PATH)/builtings2.c\
$(PROCESS_AST_PATH)/read_cmd.c\
$(ERRORS_PATH)/print_error_msg.c\

OBJS = $(SCRS:.c=.o)

HEADER = $(INCLUDE_PATH)/minishell.h\
$(INCLUDE_PATH)/builtings.h\
$(INCLUDE_PATH)/parse.h\
$(INCLUDE_PATH)/token.h\
$(INCLUDE_PATH)/process_ast.h\
$(INCLUDE_PATH)/errors.h\

COMPILER = $(CC)

CFLAGS = -Wall -Werror -Wextra
LIB_FLAGS = -Llibft -lft
EXEC-NAME-FLAG = -lreadline -lhistory -o

RM = rm -rf

GIT_SUBMODULES = git submodule init && git submodule update

all: make-library $(NAME)

make-library:
	$(GIT_SUBMODULES)
	$(MAKE) -C $(LIBFT_PATH)

make-library-debug:
	$(MAKE) -C $(LIBFT_PATH) debug

$(NAME): $(OBJS) $(HEADER)
	$(COMPILER) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(EXEC-NAME-FLAG) $(NAME)

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

val: 
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)