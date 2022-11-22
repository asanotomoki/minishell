# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2022/11/22 12:16:38 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell
OBJDIR   := ./obj
SRC_DIR := ./srcs
LIBFT_DIR := ./libft
CC  := cc
CFLAGS := -Wall -Werror -Wextra -g -fsanitize=address 

HEADERS :=  ./includes $(LIBFT_DIR)/includes
INCLUDES :=	$(addprefix -I, $(HEADERS))

LIBFT := $(LIBFT_DIR)/libft.a
SRC_FILES := main.c \
			 basic_cmd.c \
			 error.c get_cmdfile.c free.c
SOURCES	:=  $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJECTS  := $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))
RM := rm -f
NAME_MSG := Compile $(NAME) 
CLEAN_MSG := Delete obj file
FCLEAN_MSG := Delete $(NAME) 
LIBFT_MSG := Compile $(LIBFT) 

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJECTS)
	@echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT) : 
	@make -C $(LIBFT_DIR)
	@echo $(LIBFT_MSG)

all: $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR)
	@echo $(CLEAN_MSG)

fclean:	clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

re: fclean all

.PHONY: all bonus fclean clean re
