GREEN		=		\033[0;32m
RED			=		\033[0;31m
BLACK		=		\033[0;30m
YELLOW		=		\033[1;33m
BLUE		=		\033[0;34m
PURPLE		=		\033[1;95m
END			=		\033[0m


CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror
RM			=		rm -rf
LIBS		=		-L ./libft -l:libft.a -L mlx -lmlx -lXext -lX11
LIBFT		=		./libft/libft.a


NAME		=		so_long
SRC_SRC		=	\
 
GAME_SRC		=	\
					physics.c \
					player.c \
					utils.c \
					wrappers.c \
					map_draw.c \
					hooks.c \
					end.c \
 
MAIN_SRC		=	\
					init.c \
					main.c \
					error.c \
 
MAP_SRC		=	\
					map.c \
					map_error.c \
 
SRC_FILES		=	\
					$(addprefix $(SRC_DIR)/, $(SRC_SRC)) \
					$(addprefix $(GAME_DIR)/, $(GAME_SRC)) \
					$(addprefix $(MAIN_DIR)/, $(MAIN_SRC)) \
					$(addprefix $(MAP_DIR)/, $(MAP_SRC)) \
 
OBJ				=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


SRC_DIR		=	src
GAME_DIR		=	src/game
MAIN_DIR		=	src/main
MAP_DIR		=	src/map
INC_DIR		=		include
OBJ_DIR		=		obj


all: $(NAME)

$(LIBFT):
	@make -s -C ./libft

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) -fsanitize=address
	@printf "                                   \r"
	@printf "$(GREEN)> BUILDING SO_LONG			[✓]$(END)\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(YELLOW)> BUILDING $<               \r$(END)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I mlx -I ./libft/include -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p obj/src
	@mkdir -p obj/src/game
	@mkdir -p obj/src/main
	@mkdir -p obj/src/map

clean:
	@make clean -s -C ./libft
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make fclean -s -C ./libft
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re