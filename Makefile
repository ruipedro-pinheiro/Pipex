NAME = pipex

SRCDIR = src
OBJDIR = obj
INCDIR = include

BNSDIR = src_bonus
BNSOBJDIR = obj_bonus


# Source Files
SRC = pipex.c utils.c
SRC := $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(SRC:.c=.o)
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

BNS = pipex.c utils.c 
BNS := $(addprefix $(BNSDIR)/, $(BNS))

BNSOBJ = $(BNS:.c=.o)
BNSOBJ := $(patsubst $(BNSDIR)/%, $(BNSOBJDIR)/%, $(BNSOBJ))


LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)#/include
LDFLAGS =  -L$(LIBFT_DIR)
LIBS =  $(LIBFT)

# Archiver
AR = ar
ARFLAGS = rcs

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g -I$(LIBFT_INCLUDE)
# Compilation mode (silent by default, set VERBOSE=1 to show commands)
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif
# Default Rule
all: $(OBJDIR) $(LIBFT) $(NAME)

# Object Directory Rule
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Linking Rule
$(NAME): $(OBJ) $(LIBFT)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) $(MLXFLAGS) -o $(NAME)
	$(V)echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)

# Libft
$(LIBFT):
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	$(V)echo '[$(NAME)] Libft build successfully'

# Clean Rules
clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

bonus: fclean $(BNSOBJDIR) $(BNSOBJ) $(LIBFT)
		$(V)$(CC) $(CCFLAGS) $(LDFLAGS) $(BNSOBJ) $(LIBS) -o $(NAME)
	$(V)echo '[$(NAME)] Bonus Executable build successfully'


.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
