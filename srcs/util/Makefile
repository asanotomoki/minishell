NAME	:= util.a
LIBFT	:= ../../libft/libft.a
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCDIR	:= ./
AR		:= ar
ARFLAFS	:= -rcs
RM		:= rm -rf
SOURCES	:= error_utils.c free_utils.c status_utils.c env_utils.c env_utils2.c signal_util.c readline_utils.c args_utils.c
OBJDIR	:= ./obj
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS	:= $(OBJECTS:.o:=.d)
INCLUDE	:=	-I ../../libft/includes -I ../../includes

READLINE_DIR	:=	$(shell brew --prefix readline)
READLINE		:=	$(READLINE_DIR)/lib/libreadline.a
INCLUDE			+= -I $(READLINE_DIR)/include

#Message
RED		:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m

NAME_MSG := " $(GREEN)Compile $(NAME)$(DEFAULT)"
CLEAN_MSG := " $(YELLOW)Delete ./srcs/util/obj$(DEFAULT)"
FCLEAN_MSG := " $(RED)Delete $(NAME)$(DEFAULT)"

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
	$(CC) $(CFLAGS) -lreadline -L$(READLINE) -o test $(NAME) test.c
	./test
