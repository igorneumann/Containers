# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 18:37:43 by ineumann          #+#    #+#              #
#    Updated: 2022/06/06 16:56:22 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	vectors
SRCS			=	vector.cpp stack.cpp map.cpp
MAIN			=	main.cpp
STACK			=	main_utils_stack.cpp main_tests_stack.cpp main_stack.cpp 
VECTOR			=	main_vector.cpp main_tests_vector.cpp main_utils_vector.cpp 
OBJS			=	$(SRCS:.cpp=.o)
CXX 			= 	clang++
CXXFLAGS		=	-g -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

all: $(NAME)

stack: fclean $(STACK)

vector: fclean $(VECTOR)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(MAIN) # -o $(NAME)

$(STACK): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(STACK) # -o $(NAME)

$(VECTOR): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(VECTOR) # -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(NAME) *.dSYM

re: fclean all

.PHONY: all vector stack clean fclean re