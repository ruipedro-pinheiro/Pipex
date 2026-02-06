NAME = pipex

SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFT_DIR)

SRC = pipex.c utils.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRCDIR_B = src_bonus
OBJDIR_B = obj_bonus
SRC_B = pipex.c utils.c
OBJ_B = $(addprefix $(OBJDIR_B)/, $(SRC_B:.c=.o))

################################################################################
#                                PROGRESS BAR                                  #
################################################################################

CNT = /tmp/.pipex_cnt
RESET := $(shell echo 0 > $(CNT))
C = \033[1;36m
Y = \033[1;33m
R = \033[1;31m
B = \033[1m
X = \033[0m

define progress
n=$$(($$(cat $(CNT)) + 1)); echo $$n > $(CNT); \
t=$(1); pct=$$((n * 100 / t)); f=$$((n * 20 / t)); \
bar=""; i=0; \
while [ $$i -lt $$f ]; do bar="$${bar}█"; i=$$((i+1)); done; \
while [ $$i -lt 20 ]; do bar="$${bar}░"; i=$$((i+1)); done; \
printf "\r\033[K $(C)🔧 [$(NAME)] $(Y)$$bar $(B)$$pct%%$(X)"
endef

################################################################################
#                                   RULES                                      #
################################################################################

all: $(LIBFT) $(NAME)
	@if [ $$(cat $(CNT)) -gt 0 ]; then printf "\n"; fi
	@printf " $(C)✅ [$(NAME)] $(B)Build complete$(X)\n"

bonus: $(LIBFT) .bonus
	@if [ $$(cat $(CNT)) -gt 0 ]; then printf "\n"; fi
	@printf " $(C)✅ [$(NAME)] $(B)Bonus complete$(X)\n"

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJ) $(LIBFT) -o $(NAME)

.bonus: $(OBJ_B) $(LIBFT)
	@$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJ_B) $(LIBFT) -o $(NAME)
	@touch .bonus

$(LIBFT):
	@$(MAKE) --silent -C $(LIBFT_DIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR_B):
	@mkdir -p $(OBJDIR_B)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call progress,$(words $(SRC)))

$(OBJDIR_B)/%.o: $(SRCDIR_B)/%.c | $(OBJDIR_B)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call progress,$(words $(SRC_B)))

clean:
	@printf "$(R)🗑️  [$(NAME)] Cleaned$(X)\n"
	@rm -rf $(OBJDIR) $(OBJDIR_B)
	@$(MAKE) --silent -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) .bonus
	@$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
