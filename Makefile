NAME	= philo
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread -g

SRC_PATH = src/
OBJ_PATH = obj/

SRC		=	philo.c \
            philo_action.c \
            philo_init.c \
            philo_monitor.c \
            philo_threads.c \
            philo_utils.c \
            init_simu.c\

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean