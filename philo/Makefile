NAME=philo
CC=cc
FLAGS=-Wall -Wextra -Werror -g3

# FILES
SRC=	main.c \
		aux_args.c \
		init.c \
		utils.c \
		actions.c \
		routine.c \
		threads.c \
		destroy_free.c \
		print_msg.c \
		eat.c
		
OBJ=$(SRC:.c=.o)

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

# MAKEFILE RULES
$(NAME): $(OBJ)
	@echo "$(PINK)Compiling $(NAME).$(CLEAR)"
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(GREEN) [OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)"

%.o: %.c
	$(CC) $(FLAGS) -c $<

all: $(NAME)

clean:
	@echo "$(PINK)Removing .o files.$(CLEAR)"
	@rm -rf $(OBJ)
	@echo "$(GREEN).o files removed correctly\n$(CLEAR)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!\n$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
