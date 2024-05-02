#version 05 Avril 2024
NAME = so_long

SRC_PATH = src/
OBJ_PATH = obj/

SRC	= main_.c
SRCS    = $(addprefix $(SRC_PATH), $(SRC))
OBJ	= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
CC	= gcc
CFLAGS  = -Wall -Werror -Wextra

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_FLAGS = -I/usr/include -lXext -lX11 -Imlx_linux -O3
#-lmlx 
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

MLX_DIR = ./minilibx_linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

#ifeq ($(shell uname), Linux)
#	MLX_FLAGS = -I/usr/include -lmlx -lXext -lX11 -Imlx_linux -O3
#else
#	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
#endif

all: $(OBJ_PATH) $(NAME)

#Question pour ne pas relink ? 
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(MLX_FLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)
#Q? Ici pour les liens des Dossiers Exts ? 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
