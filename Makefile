# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 19:00:14 by bchedru           #+#    #+#              #
#    Updated: 2025/01/09 18:57:02 by bchedru          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-IInclude -fsanitize=thread

FILES = main ft_init ft_solo_bolo error_management error_management_bis  \
		routine utils ft_atol

SRC_FILES = $(addprefix src/, $(FILES)) \

OBJ_DIR = obj/

SRCS = $(addsuffix .c, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

bonus: $(NAME_BONUS)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)


$(OBJ_DIR):
	mkdir $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re