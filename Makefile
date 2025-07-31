# ================= Colors =================
RESET     = \033[0m
RED       = \033[31m
GREEN     = \033[32m
YELLOW    = \033[33m
CYAN      = \033[36m

# ================= Project Info =================
NAME      = cub3d
CC        = cc
CFLAGS    = -Wall -Wextra -Werror

# ================= Directories =================
SRC_DIR   = src
OBJ_DIR   = obj
LIBFT_DIR = includes/libft
GNL_DIR   = includes/get_nextline
INCLUDES  = -Iincludes -I$(LIBFT_DIR) -I$(GNL_DIR)

# ================= Source Files =================
SRC       = $(wildcard $(SRC_DIR)/*.c)
GNL_SRC   = $(wildcard $(GNL_DIR)/*.c)
OBJ       = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ      += $(GNL_SRC:%.c=$(OBJ_DIR)/%.o)

# ================= Libft =================
LIBFT_A   = $(LIBFT_DIR)/libft.a

# ================= Rules =================
all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	@echo "$(CYAN)🔨  Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -lmlx -framework OpenGL -framework AppKit -o $@
	@echo "$(GREEN)✅  Build complete!$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)📂  Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_A):
	@echo "$(CYAN)📦  Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(RED)🧹  Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
