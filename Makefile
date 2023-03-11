# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 23:57:31 by mhanda            #+#    #+#              #
#    Updated: 2023/03/11 09:26:07 by atabiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRC = main.cpp ./srcs/irc.cpp
SRC = main.cpp ./parsing/args_checker.cpp ./parsing/input_parsing.cpp

OBJF = $(SRC:.cpp=.o)

NAME = ircserv

CLANG = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

# $(NAME) : $(OBJF) ./headers/irc.hpp 
$(NAME) : $(OBJF) ./parsing/parser.hpp
		$(CLANG) $(FLAGS)  $(OBJF) -o $(NAME)

%.o: %.cpp
		$(CLANG) $(FLAGS) -o $@ -c $<

all : $(NAME)

clean :
		rm -f $(OBJF)
fclean : clean
		rm -f $(NAME)
re : fclean all
