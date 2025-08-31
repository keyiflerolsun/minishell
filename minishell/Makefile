CFILES = main.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3 -Icore -Iparser -Iexecutor -Ibuiltins -Iutils
LDFLAGS = -lreadline

MAKEFLAGS += --no-print-directory --silent
CORE      = core/core.a
PARS      = parser/parser.a
EXCT      = executor/executor.a
BLTN      = builtins/builtins.a
UTLS      = utils/utils.a

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OFILES) $(CORE) $(PARS) $(EXCT) $(BLTN) $(UTLS)
	@printf "$(GREEN)» 📦 Linking   $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OFILES) $(CORE) $(PARS) $(EXCT) $(BLTN) $(UTLS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%12s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(CORE): FORCE
	@$(MAKE) -C $(dir $@)

$(PARS): FORCE
	@$(MAKE) -C $(dir $@)

$(EXCT): FORCE
	@$(MAKE) -C $(dir $@)

$(BLTN): FORCE
	@$(MAKE) -C $(dir $@)

$(UTLS): FORCE
	@$(MAKE) -C $(dir $@)

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)./$(OBJDIR) $(RESET)\n"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(CORE)) clean
	@$(MAKE) -C $(dir $(PARS)) clean
	@$(MAKE) -C $(dir $(EXCT)) clean
	@$(MAKE) -C $(dir $(BLTN)) clean
	@$(MAKE) -C $(dir $(UTLS)) clean

fclean: clean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(dir $(CORE)) fclean
	@$(MAKE) -C $(dir $(PARS)) fclean
	@$(MAKE) -C $(dir $(EXCT)) fclean
	@$(MAKE) -C $(dir $(BLTN)) fclean
	@$(MAKE) -C $(dir $(UTLS)) fclean

re: fclean all

run: $(NAME)
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--suppressions=readline.supp \
		./minishell

FORCE:
.PHONY: all clean fclean re FORCE run
