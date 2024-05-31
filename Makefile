LIBFT_PATH = libft

SRC_PATH = src
INCLUDE_PATH = include
BUILTINGS_PATH = $(SRC_PATH)/builtings
PARSE_PATH = $(SRC_PATH)/parse
TOKEN_PATH = $(SRC_PATH)/token
PROCESS_AST_PATH = $(SRC_PATH)/process_ast
ERRORS_PATH = $(SRC_PATH)/errors
SET_UP = $(SRC_PATH)/set_up

NAME = minishell

SCRS = $(SRC_PATH)/main.c\
$(SRC_PATH)/read_input.c\
$(TOKEN_PATH)/tokenizer.c\
$(TOKEN_PATH)/tokenizer_utils.c\
$(TOKEN_PATH)/tokenizer_utils2.c\
$(TOKEN_PATH)/expand_variables.c\
$(PARSE_PATH)/parse.c\
$(PARSE_PATH)/parse_utils.c\
$(PARSE_PATH)/parse_utils2.c\
$(PARSE_PATH)/find_first_pipe_cmd.c\
$(BUILTINGS_PATH)/archive_env.c\
$(BUILTINGS_PATH)/archive_utils.c\
$(BUILTINGS_PATH)/archive_utils1.c\
$(BUILTINGS_PATH)/archive_utils2.c\
$(BUILTINGS_PATH)/archive_utils3.c\
$(BUILTINGS_PATH)/builtings.c\
$(BUILTINGS_PATH)/builtings1.c\
$(BUILTINGS_PATH)/builtings2.c\
$(BUILTINGS_PATH)/builtings_child_process.c\
$(BUILTINGS_PATH)/builtings_child_process2.c\
$(PROCESS_AST_PATH)/read_cmd.c\
$(PROCESS_AST_PATH)/archive_utils_cmd.c\
$(PROCESS_AST_PATH)/archive_utils_cmd1.c\
$(ERRORS_PATH)/print_error_msg.c\
$(SET_UP)/set_up.c

OBJS = $(SCRS:.c=.o)

HEADER = $(INCLUDE_PATH)/minishell.h\
$(INCLUDE_PATH)/builtings.h\
$(INCLUDE_PATH)/parse.h\
$(INCLUDE_PATH)/token.h\
$(INCLUDE_PATH)/process_ast.h\
$(INCLUDE_PATH)/errors.h\
$(INCLUDE_PATH)/set_up.h\

CC = $(shell which cc clang gcc | head -n 1)

CFLAGS = -Wall -Werror -Wextra -g
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
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(EXEC-NAME-FLAG) $(NAME)

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