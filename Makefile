# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 19:00:14 by bchedru           #+#    #+#              #
#    Updated: 2024/09/05 20:03:40 by bchedru          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIBAMOA = libamoa/libamoa.a

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-IInclude

LFLAGS =	-Llibamoa \
			-lamoa

FILES = main philo_init philo_utils philo_loop philo_error philo_eat philo_think

SRC_FILES = $(addprefix src/, $(FILES)) \

OBJ_DIR = obj/

SRCS = $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

bonus: $(NAME_BONUS)

clean :
	rm -rf $(OBJ_DIR)
	make fclean -C libamoa

fclean : clean
	rm -rf $(NAME)
	make fclean -C libamoa

re: fclean all

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBAMOA)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

$(LIBAMOA):
	make -C libamoa

$(OBJ_DIR):
	mkdir $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re