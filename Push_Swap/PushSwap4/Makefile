#Antonin_fe
CC	= cc
CFLAGS	= -Wall -Wextra -Werror -g3
#valgrind --leak-check=full --show-leak-kinds=all
NAME	= push_swap

SRC_PATH = src/
OBJ_PATH = obj/

SRC		= main.c \
		input_check.c input_check_utils.c \
		initialisation.c \
		stack.c \
		swap.c push.c rotate.c reverse_rotate.c \
		sort.c \
		position.c cost.c do_move.c \
		utils.c \
		usfull.c \
		ft_parsing.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= includes/

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INCS)
	@echo -n "Here We Are !"

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
