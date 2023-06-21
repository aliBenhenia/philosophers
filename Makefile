NAME = philo
CC = cc
RM = rm -f
HEADER = philo.h
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
SRC =   ft_atoi.c addfront.c  addnew.c state_controller.c get_time.c  parse_args.c main.c
OBJ = $(SRC:%.c=%.o)
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS)  -c $< -o $@
clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all
.phony : all clean fclean $(NAME)