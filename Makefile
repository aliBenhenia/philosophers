NAME = philo
CC = cc
RM = rm -f
CFLAGS = 
SRC =   ./utils/ft_split.c ./utils/ft_atoi.c ./utils/addfront.c  ./utils/addnew.c  ./utils/get_time.c  ./parsing/parse_args.c ./src/main.c
OBJ = $(SRC:%.c=%.o)
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME) -fsanitize=thread
%.o : %.c 
	$(CC) $(CFLAGS)  -c $< -o $@
clean : 
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all
.phony : all clean fclean $(NAME)