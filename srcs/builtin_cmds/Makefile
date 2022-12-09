# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tasano <tasano@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 20:41:09 by tasano            #+#    #+#              #
#    Updated: 2022/12/09 17:30:02 by tasano           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	builtin_cmds.a
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCDIR	:= ./
AR		:= ar
ARFLAFS	:= -rcs
RM		:= rm -rf
SOURCES	:= builtin_cd.c builtin_echo.c builtin_pwd.c builtin_export.c builtin_unset.c builtin_env.c builtin_exit.c
OBJDIR	:= ./obj
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS	:= $(OBJECTS:.o:=.d)
MSG := Compile $(NAME) 
CLEAN_MSG := Delete builtin_cmds obj file
FCLEAN_MSG := Delete $(NAME)

$(NAME): $(OBJECTS) 
	@$(AR) $(ARFLAFS) $(NAME) $(OBJECTS)
	@echo $(MSG)

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
