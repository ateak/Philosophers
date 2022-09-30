NAME	=	philo

SRC		=	init.c\
			philo.c\
			philo_life.c\
			philo_utils.c\

HEADER 	= 	philo.h	

OBJ		=	$(SRC:%.c=%.o)

FLAGS	=	-Wall -Wextra -Werror -fsanitize=thread

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
	$(CC)  ${FLAGS} ${OBJ} -o ${NAME}

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ)

fclean	: 	clean
	@rm -f $(NAME)

re		:	fclean all