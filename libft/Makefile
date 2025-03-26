NAME = libft.a

SRC_DIR = src/
OBJ_DIR = obj/
INC = includes/
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = $(SRC_DIR)ft_atoi.c $(SRC_DIR)ft_bzero.c $(SRC_DIR)ft_calloc.c \
	$(SRC_DIR)ft_isalnum.c $(SRC_DIR)ft_isalpha.c $(SRC_DIR)ft_isascii.c \
	$(SRC_DIR)ft_isdigit.c $(SRC_DIR)ft_isprint.c $(SRC_DIR)ft_itoa.c $(SRC_DIR)ft_memchr.c \
	$(SRC_DIR)ft_memcmp.c $(SRC_DIR)ft_memcpy.c $(SRC_DIR)ft_memmove.c $(SRC_DIR)ft_memset.c \
	$(SRC_DIR)ft_putchar_fd.c $(SRC_DIR)ft_putendl_fd.c $(SRC_DIR)ft_putnbr_fd.c \
	$(SRC_DIR)ft_putstr_fd.c $(SRC_DIR)ft_split.c $(SRC_DIR)ft_strchr.c $(SRC_DIR)ft_strdup.c \
	$(SRC_DIR)ft_striteri.c $(SRC_DIR)ft_strjoin.c $(SRC_DIR)ft_strlcat.c $(SRC_DIR)ft_strlcpy.c \
	$(SRC_DIR)ft_strlen.c $(SRC_DIR)ft_strmapi.c $(SRC_DIR)ft_strncmp.c $(SRC_DIR)ft_strnstr.c \
	$(SRC_DIR)ft_strrchr.c $(SRC_DIR)ft_strtrim.c $(SRC_DIR)ft_substr.c $(SRC_DIR)ft_tolower.c \
	$(SRC_DIR)ft_toupper.c $(SRC_DIR)ft_lstadd_back.c $(SRC_DIR)ft_lstclear.c $(SRC_DIR)ft_lstiter.c \
	$(SRC_DIR)ft_lstmap.c $(SRC_DIR)ft_lstsize.c $(SRC_DIR)ft_lstadd_front.c $(SRC_DIR)ft_lstdelone.c \
	$(SRC_DIR)ft_lstlast.c $(SRC_DIR)ft_lstnew.c $(SRC_DIR)flag.c $(SRC_DIR)flag_combo_plus.c \
	$(SRC_DIR)flag_dash_length.c $(SRC_DIR)flag_plus.c $(SRC_DIR)flag_space.c $(SRC_DIR)ft_printf.c \
	$(SRC_DIR)hex_to_itoa.c $(SRC_DIR)pr_conversion.c $(SRC_DIR)flag_combo.c $(SRC_DIR)flag_combo_space.c \
	$(SRC_DIR)flag_hashtag.c $(SRC_DIR)flag_point.c $(SRC_DIR)flag_zero.c $(SRC_DIR)flag_point_length.c \
	$(SRC_DIR)itoa.c $(SRC_DIR)putcharstr.c $(SRC_DIR)flag_combo_ht.c $(SRC_DIR)flag_dash.c $(SRC_DIR)flag_nb.c \
	$(SRC_DIR)flag_zero_length.c $(SRC_DIR)fts.c $(SRC_DIR)struct.c \
	$(SRC_DIR)get_next_line_bonus.c $(SRC_DIR)get_next_line_utils_bonus.c \

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re	: fclean all

.PHONY : all clean fclean re