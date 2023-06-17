NAME = philo
CC = cc
RM = rm -f
HEADER = ./includes/philo.h
CFLAGS = -Wall -Werror -Wextra
SRC =   ./utils/ft_atoi.c ./utils/addfront.c  ./utils/addnew.c ./threading/state_controller.c ./utils/get_time.c  ./parsing/parse_args.c ./src/main.c
OBJ = $(SRC:%.c=%.o)
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME) #-fsanitize=address
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS)  -c $< -o $@ 
clean : 
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all
.phony : all clean fclean $(NAME)