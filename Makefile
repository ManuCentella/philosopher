NAME	= philo
CC		= gcc
CFLAGS	= -Werror -Wall -Wextra -pthread -g

MODE	= none
ifeq ($(MODE), pretty)
    CFLAGS	+= -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
    CFLAGS	+= -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

SRC_PATH = src/
OBJ_PATH = obj/
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC		=	philo.c \
            philo_action.c \
            philo_init.c \
            philo_setup.c \
            philo_monitor.c \
            philo_threads.c \
            philo_utils.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/ -I $(LIBFT_PATH)includes/

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -o $@

clean:
	rm -rf $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean