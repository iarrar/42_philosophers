

NAME = philo

FLAGS = -Wall -Werror -Wextra 

SRCS = philo.c desinit.c routines.c utils.c init.c lunch.c monitor_routine.c

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(FLAGS) -pthread $(SRCS) -o $(NAME) 
	
check:
	$(CC) -g -fsanitize=thread $(FLAGS) -pthread   $(SRCS) 
	

clean:
	rm -f *.o
	

fclean: clean
	rm $(NAME)

re: fclean all
