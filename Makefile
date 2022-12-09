# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2022/12/09 18:04:50 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
OBJDIR	:=	./obj
SRC_DIR	:=	./srcs
CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -g -fsanitize=address 
HEADERS		:=  ./includes
INCLUDES	:=	$(addprefix -I, $(HEADERS))

SRC_FILE :=	main.c 
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SRC_FILE:.c=.o)))

LIBFT_DIR	:=	./libft
LIBFT		:=	$(LIBFT_DIR)/libft.a
BUILTIN_DIR	:=	$(SRC_DIR)/builtin_cmds
BUILTIN		:=	$(BUILTIN_DIR)/builtin_cmds.a
LEXER_DIR	:=	$(SRC_DIR)/lexer
LEXER		:=	$(LEXER_DIR)/lexer.a
PARSER_DIR	:=	$(SRC_DIR)/parser
PARSER		:=	$(PARSER_DIR)/parser.a

RM := rm -f
NAME_MSG := Compile $(NAME) 
CLEAN_MSG := Delete obj file
FCLEAN_MSG := Delete $(NAME) 

.PHONY: all fclean clean re src_clean

$(NAME): $(LIBFT) $(BUILTIN) $(LEXER) $(PARSER) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(BUILTIN) $(LEXER)	$(PARSER) $(OBJECTS) -lreadline
	@echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(BUILTIN): 
	@make -C $(BUILTIN_DIR)

$(LEXER): 
	@make -C $(LEXER_DIR)

$(PARSER): 
	@make -C $(PARSER_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(BUILTIN_DIR)
	@make clean -C $(LEXER_DIR)
	@make clean -C $(PARSER_DIR)
	@echo $(CLEAN_MSG)

fclean: src_clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(BUILTIN_DIR)
	@make fclean -C $(LEXER_DIR)
	@make fclean -C $(PARSER_DIR)
	@rm -rf $(OBJDIR)
	@echo $(CLEAN_MSG)
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

re: fclean all
