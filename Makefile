# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2022/12/13 16:07:17 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
OBJDIR	:=	./obj
SRC_DIR	:=	./srcs
CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -g -fsanitize=address 

HEADERS			:=  ./includes
LIBFT_DIR		:=	./libft
LIBFT			:=	$(LIBFT_DIR)/libft.a
HEADERS			+=	$(LIBFT_DIR)/includes
BUILTIN_DIR		:=	$(SRC_DIR)/builtin_cmds
BUILTIN			:=	$(BUILTIN_DIR)/builtin_cmds.a
HEADERS			+=	$(BUILTIN_DIR)
LEXER_DIR		:=	$(SRC_DIR)/lexer
LEXER			:=	$(LEXER_DIR)/lexer.a
HEADERS			+=	$(LEXER_DIR)
PARSER_DIR		:=	$(SRC_DIR)/parser
PARSER			:=	$(PARSER_DIR)/parser.a
HEADERS			+=	$(PARSER_DIR)
PIPE_DIR		:=	$(SRC_DIR)/pipe
PIPE			:=	$(PIPE_DIR)/pipe.a
HEADERS			+=	$(PIPE_DIR)
REDIRECT_DIR	:=	$(SRC_DIR)/redirect
REDIRECT		:=	$(REDIRECT_DIR)/redirect.a
HEADERS			+=	$(REDIRECT_DIR)
UTIL_DIR		:=	$(SRC_DIR)/util
UTIL			:=	$(UTIL_DIR)/util.a
HEADERS			+=	$(UTIL_DIR)

INCLUDES	:=	$(addprefix -I , $(HEADERS))

SRC_FILE :=	main.c \
			basic_cmd.c get_cmdfile.c 
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SRC_FILE:.c=.o)))
RM := rm -f

#Message
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m
NAME_MSG := "$(GREEN) Compile $(NAME)$(DEFAULT)"
CLEAN_MSG := "$(YELLOW) Delete $(OBJDIR)$(DEFAULT)"
FCLEAN_MSG := "$(RED) Delete $(NAME)$(DEFAULT)"

.PHONY: all fclean clean re src_clean

$(NAME): $(LIBFT) \
		  $(BUILTIN)\
		  $(LEXER) \
		  $(PARSER) \
		  $(PIPE) \
		  $(REDIRECT) \
		  $(UTIL) \
		  $(OBJECTS)
		  
	@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(BUILTIN) $(LEXER) $(PARSER) $(PIPE) $(REDIRECT) $(UTIL) $(OBJECTS) -lreadline
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

$(PIPE): 
	@make -C $(PIPE_DIR)

$(REDIRECT): 
	@make -C $(REDIRECT_DIR)

$(UTIL): 
	@make -C $(UTIL_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(BUILTIN_DIR)
	@make clean -C $(LEXER_DIR)
	@make clean -C $(PARSER_DIR)
	@make clean -C $(PIPE_DIR)
	@make clean -C $(REDIRECT_DIR)
	@make clean -C $(UTIL_DIR)
	@echo $(CLEAN_MSG)

fclean: src_clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(BUILTIN_DIR)
	@make fclean -C $(LEXER_DIR)
	@make fclean -C $(PARSER_DIR)
	@make fclean -C $(PIPE_DIR)
	@make fclean -C $(REDIRECT_DIR)
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
