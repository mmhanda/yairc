# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 23:57:31 by mhanda            #+#    #+#              #
#    Updated: 2023/03/22 07:49:40 by mhanda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = srcs/main.cpp srcs/server.cpp srcs/command.cpp srcs/client.cpp #./parsing/args_checker.cpp ./parsing/input_parsing.cpp ./parsing/cmds.cpp

OBJF = $(SRC:.cpp=.o)

NAME = ircserv

CXX = c++

CXXFLAGS = -Wall -Wextra  -std=c++98 -Iheaders

# $(NAME) : $(OBJF) ./headers/irc.hpp
$(NAME) : $(OBJF) headers/server.hpp headers/client.hpp
		$(CXX) $(CXXFLAGS) $(OBJF) -o $(NAME)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -o $@ -c $<

all : $(NAME)

run: all
	./ircserv 1 1

clean :
		rm -f $(OBJF)
fclean : clean
		rm -f $(NAME)
re : fclean all
