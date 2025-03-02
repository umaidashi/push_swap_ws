NAME = test_push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -DTESTING

SRCS = test_push_swap.c \
       ../stack_operations.c \
       ../error_handling.c \
       ../push_swap.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f ../stack_operations.o
	rm -f ../error_handling.o
	rm -f ../push_swap.o

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test
