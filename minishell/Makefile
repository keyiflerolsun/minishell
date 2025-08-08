CFILES = main.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME      = minismet
CC        = cc
CFLAGS    = -Wall -Wextra -Werror -Ilibs/libft -Ilibs/ft_printf -Ilibs/get_next_line -Ilibs/pipex
LDFLAGS   = -lreadline

MAKEFLAGS += --no-print-directory --silent
LIBFT      = libs/libft/libft.a
PRINTF     = libs/ft_printf/libftprintf.a
GNL        = libs/get_next_line/get_next_line.a
PPX        = libs/pipex/pipex.a

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OFILES) $(PPX) $(GNL) $(PRINTF) $(LIBFT)
	@printf "$(GREEN)» 📦 Linking   $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFILES) $(PPX) $(GNL) $(PRINTF) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%14s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(PPX): FORCE
	@$(MAKE) -C $(dir $@)

$(GNL): FORCE
	@$(MAKE) -C $(dir $@)

$(PRINTF): FORCE
	@$(MAKE) -C $(dir $@)

$(LIBFT): FORCE
	@$(MAKE) -C $(dir $@)

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)./$(OBJDIR) $(RESET)\n"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(PPX)) clean
	@$(MAKE) -C $(dir $(GNL)) clean
	@$(MAKE) -C $(dir $(PRINTF)) clean
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(dir $(PPX)) fclean
	@$(MAKE) -C $(dir $(GNL)) fclean
	@$(MAKE) -C $(dir $(PRINTF)) fclean
	@$(MAKE) -C $(dir $(LIBFT)) fclean

re: fclean all

FORCE:
.PHONY: all clean fclean re FORCE
