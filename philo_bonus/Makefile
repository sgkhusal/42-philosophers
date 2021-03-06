# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 20:16:35 by sguilher          #+#    #+#              #
#    Updated: 2022/07/06 13:21:08 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -pthread

SRC		=	philosophers.c
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
	./$(NAME)

leak:	all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

test:	all
	cd minishell_tester && ./tester

clean:
	@rm -rf $(OBJ_DIR)
	@echo "removed obj folder"

fclean:	clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "removed executable"

re:		fclean all

.PHONY:	all clean fclean re run
