CFILES = main.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME    = minismet
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iutils -Icore -Iexecutor
LDFLAGS = -lreadline

MAKEFLAGS += --no-print-directory --silent
CORE      = core/core.a
UTLS      = utils/utils.a
EXCT      = executor/executor.a

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OFILES) $(CORE) $(UTLS) $(EXCT)
	@printf "$(GREEN)» 📦 Linking   $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFILES) $(CORE) $(UTLS) $(EXCT) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%12s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(CORE): FORCE
	@$(MAKE) -C $(dir $@)

$(UTLS): FORCE
	@$(MAKE) -C $(dir $@)

$(EXCT): FORCE
	@$(MAKE) -C $(dir $@)

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)./$(OBJDIR) $(RESET)\n"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(CORE)) clean
	@$(MAKE) -C $(dir $(UTLS)) clean
	@$(MAKE) -C $(dir $(EXCT)) clean

fclean: clean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(dir $(CORE)) fclean
	@$(MAKE) -C $(dir $(UTLS)) fclean
	@$(MAKE) -C $(dir $(EXCT)) fclean

re: fclean all

FORCE:
.PHONY: all clean fclean re FORCE
