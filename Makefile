# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2023/01/21 14:09:20 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
OBJDIR		:=	./obj
SRC_DIR		:=	./srcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
#CFLAGS  +=  -fsanitize=address -fno-omit-frame-pointer -g

HEADERS			:=  ./includes
LIBFT_DIR		:=	./libft
LIBFT			:=	$(LIBFT_DIR)/libft.a
HEADERS			+=	$(LIBFT_DIR)/includes

UTIL_DIR		:=	$(SRC_DIR)/util
UTIL			:=	$(UTIL_DIR)/util.a
HEADERS			+=	$(UTIL_DIR)

BUILTIN_DIR		:=	$(SRC_DIR)/builtin_cmds
BUILTIN			:=	$(BUILTIN_DIR)/builtin_cmds.a
HEADERS			+=	$(BUILTIN_DIR)

LEXER_DIR		:=	$(SRC_DIR)/lexer
LEXER			:=	$(LEXER_DIR)/lexer.a
HEADERS			+=	$(LEXER_DIR)

PARSER_DIR		:=	$(SRC_DIR)/parser
PARSER			:=	$(PARSER_DIR)/parser.a
HEADERS			+=	$(PARSER_DIR)

EXPANSION_DIR	:=	$(SRC_DIR)/expansion
EXPANSION		:=	$(EXPANSION_DIR)/expansion.a
HEADERS			+=	$(EXPANSION_DIR)

EXEC_DIR		:=	$(SRC_DIR)/exection
EXEC			:=	$(EXEC_DIR)/exection.a
HEADERS			+=	$(EXEC_DIR)

READLINE_DIR	:=	$(shell brew --prefix readline)
READLINE		:=	$(READLINE_DIR)/lib/libreadline.a
HEADERS			+=	$(READLINE_DIR)/include

INCLUDES		:=	$(addprefix -I , $(HEADERS))

SRC_FILE :=	main.c
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SRC_FILE:.c=.o)))
RM := rm -f

#Message
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m
NAME_MSG	:=	"$(GREEN) Compile $(NAME)$(DEFAULT)"
CLEAN_MSG	:=	"$(YELLOW) Delete $(OBJDIR)$(DEFAULT)"
FCLEAN_MSG	:=	"$(RED) Delete $(NAME)$(DEFAULT)"

.PHONY: all fclean clean re

$(NAME): $(LIBFT) \
		  $(UTIL) \
		  $(BUILTIN) \
		  $(LEXER) \
		  $(PARSER) \
		  $(EXPANSION) \
		  $(EXEC) \
		  $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(UTIL) $(BUILTIN) $(LEXER) $(PARSER) $(EXPANSION) $(EXEC) $(OBJECTS) -l readline -L$(READLINE_DIR)/lib
	@echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(UTIL):
	@make -C $(UTIL_DIR)

$(BUILTIN):
	@make -C $(BUILTIN_DIR)

$(LEXER):
	@make -C $(LEXER_DIR)

$(PARSER):
	@make -C $(PARSER_DIR)

$(EXPANSION):
	@make -C $(EXPANSION_DIR)

$(EXEC):
	@make -C $(EXEC_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(BUILTIN_DIR)
	@make clean -C $(LEXER_DIR)
	@make clean -C $(PARSER_DIR)
	@make clean -C $(EXEC_DIR)
	@make clean -C $(EXPANSION_DIR)
	@echo $(CLEAN_MSG)

fclean:
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(BUILTIN_DIR)
	@make fclean -C $(LEXER_DIR)
	@make fclean -C $(PARSER_DIR)
	@make fclean -C $(EXEC_DIR)
	@make fclean -C $(EXPANSION_DIR)
	@make fclean -C $(UTIL_DIR)
	@rm -rf $(OBJDIR)
	@echo $(CLEAN_MSG)
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

re: fclean all

norm:
	norminette -v
	norminette $(SRC_DIR)
	norminette $(LIBFT_DIR)
	norminette $(includes)
