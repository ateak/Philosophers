NAME	=	philo_bonus

SRC		=	init_bonus.c\
			philo_bonus.c\
			philo_life_bonus.c\
			philo_utils_bonus.c\

HEADER 	= 	philo_bonus.h	

OBJ		=	$(SRC:%.c=%.o)

FLAGS	=	-Wall -Wextra -Werror

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