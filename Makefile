# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 10:53:25 by mcauchy-          #+#    #+#              #
#    Updated: 2025/05/06 13:31:49 by mcauchy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRC_DIR			=	src/

OBJ_DIR			=	obj/

INC				=	includes/

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra -g3

READLINEFLAGS	=	-lreadline

RED				=	\e[31m

BLUE			=	\e[34m

RESET			=	\e[0m

SRC				=	$(SRC_DIR)split_cmds.c $(SRC_DIR)get_correct_cmd.c	\
					$(SRC_DIR)vars_struct.c $(SRC_DIR)get_env_var.c		\
					$(SRC_DIR)unquote.c $(SRC_DIR)expand.c				\
					$(SRC_DIR)signal_handle.c $(SRC_DIR)exec.c			\
					$(SRC_DIR)convert_to_dec.c $(SRC_DIR)builtins.c		\
					$(SRC_DIR)builtins2.c $(SRC_DIR)mini_struct.c		\
					$(SRC_DIR)ft_echo.c $(SRC_DIR)ft_cd.c				\
					$(SRC_DIR)here_doc_utils.c $(SRC_DIR)here_doc.c		\
					$(SRC_DIR)get_cmds.c $(SRC_DIR)redir.c				\
					$(SRC_DIR)utils.c $(SRC_DIR)utils2.c 				\
					$(SRC_DIR)utils3.c $(SRC_DIR)minishell.c			\
					$(SRC_DIR)redirection.c								\

OBJ				=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

LIBFT			=	libft/libft.a

all				:	$(NAME)

$(LIBFT)		:
					$(MAKE) -C libft --no-print-directory

$(NAME)			:	$(LIBFT) $(OBJ_DIR) $(OBJ)
					@$(CC) $(CFLAGS) $(READLINEFLAGS) -I $(INC) $(OBJ) $(LIBFT) -o $(NAME)
					@clear
					@echo "Compilation Done"
					@echo ""
					@echo "........                                                                         ........"
					@echo ""
					@echo ""
					@echo " /##      /## /###### /##   /## /######  /######  /##   /## /######## /##       /##      "
					@echo "| ###    /###|_  ##_/| ### | ##|_  ##_/ /##__  ##| ##  | ##| ##_____/| ##      | ##      "
					@echo "| ####  /####  | ##  | ####| ##  | ##  | ##  \__/| ##  | ##| ##      | ##      | ##      "
					@echo "| ## ##/## ##  | ##  | ## ## ##  | ##  |  ###### | ########| #####   | ##      | ##      "
					@echo "| ##  ###| ##  | ##  | ##  ####  | ##   \____  ##| ##__  ##| #3__/   | ##      | ##      "
					@echo "| ##\  # | ##  | ##  | ##\  ###  | ##   /##  \ ##| ##  | ##| ##      | ##      | ##      "
					@echo "| ## \/  | ## /######| ## \  ## /######|  ######/| ##  | ##| ########| ########| ########"
					@echo "|__/     |__/|______/|__/  \__/|______/ \______/ |__/  |__/|________/|________/|________/"
					@echo ""
					@echo ""
					@echo "........                                  mcauchy-                               ........"
					@echo "........                                   vluo                                  ........"
					@echo ""

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
					@echo "$(BLUE)minishell $(RESET): \e[92mCompiling\e[m $(notdir $<)..."

clean			:
					@$(MAKE) clean -C libft --no-print-directory
					@rm -rf $(OBJ_DIR)
					@echo "$(RED)- Objects deleted !$(RESET)"

fclean			:	clean
					@$(MAKE) fclean -C libft --no-print-directory
					@rm -rf $(NAME)
					@echo "$(RED)- Executable deleted !$(RESET)"

re				:	fclean
					@make all --no-print-directory

.PHONY			:	all clean fclean re