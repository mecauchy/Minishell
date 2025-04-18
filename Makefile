NAME = minishell

SRC_DIR = src/
OBJ_DIR = obj/
INC = includes/
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
READLINEFLAGS = -lreadline

SRC = $(SRC_DIR)split_cmds.c $(SRC_DIR)get_correct_cmd.c \
	$(SRC_DIR)vars_struct.c $(SRC_DIR)get_env_var.c $(SRC_DIR)unquote.c $(SRC_DIR)expand.c \
	$(SRC_DIR)signal_handle.c \
	$(SRC_DIR)convert_to_dec.c $(SRC_DIR)builtins.c $(SRC_DIR)builtins2.c \
	$(SRC_DIR)ft_echo.c $(SRC_DIR)ft_cd.c \
	$(SRC_DIR)redirection.c \
	$(SRC_DIR)mini_struct.c $(SRC_DIR)utils.c $(SRC_DIR)utils2.c $(SRC_DIR)minishell.c \

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

LIBFT = libft/libft.a

all : $(LIBFT) $(NAME)

$(LIBFT) :
	$(MAKE) -C libft

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(READLINEFLAGS) -I $(INC) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

clean :
	$(MAKE) clean -C libft
	rm -rf $(OBJ_DIR)

fclean : clean
	$(MAKE) fclean -C libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re