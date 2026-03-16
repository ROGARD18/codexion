NAME      := codexion
CC        := cc
CFLAGS    := -Wall -Wextra -Werror
PTHFLAG   := -pthread

SRCDIR    := source
DEPDIR    := .deps
INCDIR    := includes
BUILDDIR  := build

SRCFILES  := main.c source/parsing.c source/sleep.c source/threads_functions.c

OBJS      := $(addprefix $(BUILDDIR)/,$(SRCFILES:.c=.o))
HEADERS   := $(INCDIR)/codexion.h

DEPFLAGS  := -MD -MP -MF $(DEPDIR)/$*.d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILDDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@) $(DEPDIR)/$(dir $<)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCDIR) -c $< -o $@

vpath %.c $(SRCDIR)
-include $(addprefix $(DEPDIR)/,$(SRCFILES:.c=.d))

clean:
	rm -rf $(DEPDIR)
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
