NAME	:=	libft.a
COMPILER  := cc
CFLAGS    := -Wall -Wextra -Werror
INCLUDE   := -I ./includes
SRCDIR    := ./
AR := ar
ARFLAFS := -rcs
RM := rm -rf
SOURCES	:= ft_atoi.c ft_strtol.c ft_itoa.c\
ft_bzero.c ft_calloc.c \
ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_strlen.c ft_get_digit.c ft_strcmp.c ft_strncmp.c \
ft_split.c ft_strtrim.c \
ft_strchr.c ft_strrchr.c ft_strnstr.c \
ft_strdup.c ft_substr.c \
ft_striteri.c ft_strmapi.c \
ft_strlcat.c ft_strlcpy.c ft_strjoin.c \
ft_tolower.c ft_toupper.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJDIR    := ./obj
OBJECTS   := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS   := $(OBJECTS:.o:=.d)
#Message
RED 	:= \033[1;31m
GREEN	:= \033[1;32m
YELLOW	:= \033[1;33m
DEFAULT	:= \033[0m

NAME_MSG	:=	"$(GREEN) Compile $(NAME)$(DEFAULT)"
CLEAN_MSG	:=	"$(YELLOW) Delete ./libft/obj$(DEFAULT)"
FCLEAN_MSG	:=	"$(RED) Delete $(NAME)$(DEFAULT)"

$(NAME): $(OBJECTS)
	@$(AR) $(ARFLAFS) $(NAME) $(OBJECTS)
	@echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR)
	@$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

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
