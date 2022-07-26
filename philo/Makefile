# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 20:16:35 by sguilher          #+#    #+#              #
#    Updated: 2022/07/26 18:40:15 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -pthread

SRC		=	main.c handle_input.c forks.c philosophers.c routine.c actions.c \
			$(UTILS)
UTILS	=	time.c utils.c
HEADER	=	philosophers.h

OBJ_DIR	=	obj
OBJ		=	$(SRC:%.c=$(OBJ_DIR)/%.o)

VPATH	=	src
INCLUDE	=	-I ./ -I ./includes

# Bonus
BONUS = philo_bonus
SRC_BONUS = $(MAIN)
OBJ_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
# rules

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "\033[1;32m"
	@echo "************************************"
	@echo "           philo created"
	@echo "************************************"
	@echo "\033[0m"

$(BONUS): $(OBJ_DIR) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $@
	@echo "\033[1;32m"
	@echo "************************************"
	@echo "         philo_bonus created"
	@echo "************************************"
	@echo "\033[0m"

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

run: $(NAME)
	./$(NAME) 5 400 100 100 5

leak:	all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

test:	all
	cd ../tests && ./test.sh

clean:
	@rm -rf $(OBJ_DIR)
	@echo "removed obj folder"

fclean:	clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "removed executable"

re:		fclean all

.PHONY:	all clean fclean re run
