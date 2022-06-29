# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 18:37:43 by ineumann          #+#    #+#              #
#    Updated: 2022/06/29 17:50:22 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	vectors
MAINDIR			=	./srcs/main/
SRCSDIR			=	./srcs/cpp/
SRCS			=	$(SRCSDIR)vector.cpp $(SRCSDIR)stack.cpp $(SRCSDIR)map.cpp
MAIN			=	$(MAINDIR)main.cpp
STACK			=	$(MAINDIR)main_utils_stack.cpp $(MAINDIR)main_tests_stack.cpp $(MAINDIR)main_stack.cpp 
VECTOR			=	$(MAINDIR)main_vector.cpp $(MAINDIR)main_tests_vector.cpp $(MAINDIR)main_utils_vector.cpp 
MAP				=   $(MAINDIR)main_map.cpp
OBJS			=	$(SRCS:.cpp=.o)
CXX 			= 	clang++
CXXFLAGS		=	-g -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

all: $(NAME)

stack: fclean $(STACK) clean

vector: fclean $(VECTOR) clean

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(MAIN) # -o $(NAME)

$(STACK): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(STACK) # -o $(NAME)

$(VECTOR): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(VECTOR) # -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) *.dSYM

re: fclean all

.PHONY: all vector stack clean fclean re