NAME      := codexion
CC        := cc
CFLAGS    := -Wall -Wextra -Werror -g3
PTHFLAG   := -pthread

EXTRA_FLAGS := 

SRCDIR    := . source source/utils
DEPDIR    := .deps
INCDIR    := includes
BUILDDIR  := build

SRCFILES  := main.c parsing.c mutex_utils.c \
             work_functions.c free_all.c monitor_function.c get_time.c \
             swap.c priority_queue.c compile_dongles.c init_file.c \
             ft_calloc.c is_alive.c priority_queue2.c ending_all_threads.c

OBJS      := $(addprefix $(BUILDDIR)/,$(SRCFILES:.c=.o))
HEADERS   := $(INCDIR)/codexion.h

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(PTHFLAG) $(EXTRA_FLAGS) $(OBJS) -o $(NAME)
	@echo "\033[32m[OK] $(NAME) créé\033[0m"

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(DEPDIR)/$(dir $*)
	@$(CC) $(CFLAGS) $(PTHFLAG) $(EXTRA_FLAGS) -MMD -MP -I$(INCDIR) -c $< -o $@

vpath %.c $(SRCDIR)
-include $(OBJS:.o=.d)

clean:
	@rm -rf $(BUILDDIR)
	@rm -rf $(DEPDIR)
	@echo "\033[33m[CLEAN] Objets supprimés\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m[FCLEAN] $(NAME) supprimé\033[0m"

re: fclean all

.PHONY: all clean fclean re