# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 17:11:14 by wmardin           #+#    #+#              #
#    Updated: 2022/09/19 22:11:33 by wmardin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME =	pipex
SRC =	00_main.c\
		01_children.c\
		07_setup_1.c 07_setup_2.c\
		08_errors_1.c 08_errors_2.c\
		09_helperfunctions.c

BLUE = \033[94m
COLOR_END = \033[0m

%.o: %.c

LIBFT = libft/libft.a

$(NAME): $(LIBFT)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)
	@echo "$(BLUE)$(NAME) created."

$(LIBFT):
	@make --no-print-directory -C ./libft

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "$(BLUE)clean performed."

fclean: clean
	@$(RM) $(NAME) $(LIBFT) a.out
	@echo "$(BLUE)fclean performed."

re: fclean all

noflag:
	@$(CC) $(SRC) $(LIBFT) -o $(NAME)
	@echo "$(BLUE)$(NAME) created w/o error flags."

test:
	@$(CC) test.c $(LIBFT) -o test

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(BLUE)git auto add & push performed."