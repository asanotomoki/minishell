NAME	:=	exection.a
CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
#CFLAGS	+=	 -fsanitize=address -fno-omit-frame-pointer -g
SRCDIR	:=	./
AR		:=	ar
ARFLAFS	:=	-rcs
RM		:=	rm -rf
SOURCES	:=	exection.c get_cmdfile.c set_redirect.c set_heredoc.c exec_builtin.c check_cmdfile.c \
			fd_utils.c heredoc_utils.c pipe_utils.c wait_utils.c

OBJDIR	:=	./obj
OBJECTS	:=	$(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS	:=	$(OBJECTS:.o:=.d)
INCLUDE	:=	-I ../../libft/includes
INCLUDE	+=	-I ../../includes
#test
UTIL_DIR		:= ../util
UTIL			:= $(UTIL_DIR)/util.a
INCLUDE			+= -I $(UTIL_DIR)
LEXER_DIR		:= ../lexer
LEXER			:= $(LEXER_DIR)/lexer.a
INCLUDE			+= -I $(LEXER_DIR)
PARSER_DIR		:= ../parser
PARSER			:= $(PARSER_DIR)/parser.a
INCLUDE			+= -I $(PARSER_DIR)
EXPANSION_DIR	:= ../expansion
EXPANSION		:= $(EXPANSION_DIR)/expansion.a
INCLUDE			+= -I $(EXPANSION_DIR)
BUILTIN_DIR		:= ../builtin_cmds
BUILTIN			:= $(BUILTIN_DIR)/builtin_cmds.a
INCLUDE			+= -I $(BUILTIN_DIR)

#Message
RED		:=	\033[1;31m
GREEN	:=	\033[1;32m
YELLOW	:=	\033[1;33m
DEFAULT	:=	\033[0m

NAME_MSG := " $(GREEN)Compile $(NAME)$(DEFAULT)"
CLEAN_MSG := " $(YELLOW)Delete ./srcs/exection/obj$(DEFAULT)"
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
	$(CC) $(CFLAGS) $(INCLUDE) -o test $(NAME) $(UTIL) $(LEXER) $(PARSER) $(EXPANSION) $(BUILTIN) ../../libft/libft.a test.c
	./test

$(LEXER):
	@make -C $(LEXER_DIR)

$(UTIL):
	@make -C $(UTIL_DIR)

$(PARSER):
	@make -C $(PARSER_DIR)

$(EXPANSION):
	@make -C $(EXPANSION_DIR)

$(BUILTIN):
	@make -C $(BUILTIN_DIR)
