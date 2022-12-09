NAME	:= parser.a
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
SRCDIR	:= ./
AR		:= ar
ARFLAFS	:= -rcs
RM		:= rm -rf
SOURCES	:= parser.c
OBJDIR	:= ./obj
OBJECTS	:= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS	:= $(OBJECTS:.o:=.d)
MSG := Compile $(NAME) 
CLEAN_MSG := Delete parser obj file
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
