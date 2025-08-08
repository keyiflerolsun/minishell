CFILES = ft_printf.c \
		 ft_char.c \
		 ft_num.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME   = libftprintf.a
CC     = cc
CFLAGS = -Wall -Wextra -Werror -I../libft

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OFILES)
	@printf "$(GREEN)» 📦 Creating  $(RESET)» $(MAGENTA)$(notdir $(CURDIR))/$(NAME)$(RESET)\n"
	@ar -rcs $(NAME) $(OFILES)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%12s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)$(notdir $(CURDIR))/$(OBJDIR) $(RESET)\n"
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)$(notdir $(CURDIR))/$(NAME)$(RESET)\n"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
