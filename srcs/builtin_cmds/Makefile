# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 20:41:09 by tasano            #+#    #+#              #
#    Updated: 2023/01/16 21:55:20 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	builtin_cmds.a
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS  +=  -fsanitize=address -fno-omit-frame-pointer -g
SRCDIR	:=	./
AR		:=	ar
ARFLAFS	:=	-rcs
RM		:=	rm -rf
SOURCES	:=	builtin_cd.c \
			builtin_echo.c \
			builtin_pwd.c \
			builtin_unset.c \
			builtin_export.c \
			builtin_export_utils.c \
			builtin_env.c \
			builtin_exit.c 
OBJDIR	:=	./obj
LIBFT_DIR		:=	../../libft
LIBFT			:=	$(LIBFT_DIR)/libft.a
INCLUDE			:=	-I $(LIBFT_DIR)/includes
INCLUDE			+=	-I ../../includes
INCLUDE			+=	-I ../util

OBJECTS	:=	$(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS	:=	$(OBJECTS:.o:=.d)
#Message
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m

NAME_MSG	:= "$(GREEN) Compile $(NAME)$(DEFAULT)"
CLEAN_MSG	:= "$(YELLOW) Delete ./srcs/builtin_cmds/obj$(DEFAULT)"
FCLEAN_MSG	:= "$(RED) Delete $(NAME)$(DEFAULT)"

$(NAME): $(OBJECTS)
	@$(AR) $(ARFLAFS) $(NAME) $(OBJECTS)
	@echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(OBJDIR)
	@echo $(CLEAN_MSG)

.PHONY: fclean
fclean:	clean
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

.PHONY: re
re: fclean all

.PHONY: test
test: all
	$(CC) $(CFLAGS) $(INCLUDE) -o test $(NAME)  $(LIBFT) ../../libft/libft.a test.c
	./test
$(LIBFT):
	@make -C $(LIBFT_DIR)