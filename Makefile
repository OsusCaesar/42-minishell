# VARIABLES

NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
DBGFLAGS    := -g
READ_LINE_FLAGS := -L/usr/local/lib -I/usr/local/include -lreadline

SRC_DIR     := sources/
OBJ_DIR     := object

LIBFT_DIR   := sources_libft/libft_GIT
LIBFT_A     := $(LIBFT_DIR)/libft.a
LIBFT_H     := $(LIBFT_DIR)/libft.h

INCLUDES    := -I$(LIBFT_DIR) -I$(SRC_DIR)

SRC         := general_add_back.c \
general_add_back2.c \
general_is_ascii.c \
general_is_ascii_2.c \
general_utils.c \
general_free.c \
minishell.c \
pipeline_init.c \
pipeline_free.c \
pipeline.c \
pipeline2.c \
pipeline3.c \
token_struct.c \
built_in.c \
built_in_2.c \
built_in_3.c \
environment.c \
environment_2.c \
expand.c \
expand_2.c \
expand_3.c \
expand_wildcard.c \
executing.c \
executing_2.c \
executing_3.c \
executing_4.c \
executing_5.c \
signal.c \
token_new_word.c \
environment_free.c \
token.c 
# pipeline_print_debug.c \
token_print_debug.c \



OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# RULES 

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(READ_LINE_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT_H)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

bonus:

debug: CFLAGS += $(DBGFLAGS)
debug: fclean all

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug libft libftprintf get_next_line