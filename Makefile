# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 17:11:14 by wmardin           #+#    #+#              #
#    Updated: 2022/09/16 18:26:18 by wmardin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME =	pipex
SRC =	main.c\
		errors.c

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
	@$(CC) $(SRC) $(MLXFLAGS) $(DEFINEFLAGS) $(LIBFT) -o $(NAME)
	@echo "$(BLUE)$(NAME) created w/o error flags."

test:
	@echo $(OS)

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(BLUE)git auto add & push performed."