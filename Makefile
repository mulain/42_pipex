# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 17:11:14 by wmardin           #+#    #+#              #
#    Updated: 2022/12/06 16:15:45 by wmardin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEFINE =

NAME =	pipex
SRC =	00_main+setup.c\
		01_children.c\
		02_utils.c\
		07_shutdown.c\
		08_errors.c\
		09_helperfunctions.c

BLUE = \033[94m
COLOR_END = \033[0m

%.o: %.c

LIBFT = libft/libft.a

$(NAME): $(LIBFT)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(DEFINE) -o $(NAME)
	@echo "$(BLUE)$(NAME) created. $(COLOR_END)"

$(LIBFT):
	@make --no-print-directory -C ./libft

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "$(BLUE)clean performed.$(COLOR_END)"

fclean: clean
	@$(RM) $(NAME) $(LIBFT) a.out
	@echo "$(BLUE)fclean performed.$(COLOR_END)"

re: fclean all

noflag:
	@$(CC) $(SRC) $(LIBFT) $(DEFINE) -o $(NAME)
	@echo "$(BLUE)$(NAME) created w/o error flags.$(COLOR_END)"

test:
	@$(CC) test.c $(LIBFT) -o test

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(BLUE)git auto add & push performed.$(COLOR_END)"