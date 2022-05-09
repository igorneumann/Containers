# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 18:37:43 by ineumann          #+#    #+#              #
#    Updated: 2022/05/09 16:44:39 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	vectors
SRCS			=	vector.cpp stack.cpp #stack_main.cpp main_vector.cpp
OBJS			=	$(SRCS:.cpp=.o)
CC				=	@g++ -g -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) # -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(NAME) *.dSYM

re: fclean all

.PHONY: all clean fclean re