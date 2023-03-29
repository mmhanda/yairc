# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 23:57:31 by mhanda            #+#    #+#              #
#    Updated: 2023/03/29 13:01:48 by atabiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = srcs/main.cpp srcs/server.cpp srcs/command.cpp srcs/user.cpp srcs/channel.cpp \
./srcs/args_checker.cpp ./srcs/input_parsing.cpp ./srcs/cmds.cpp ./srcs/check_NOTICE.cpp 

OBJF = $(SRC:.cpp=.o)

NAME = ircserv

CXX = c++

CXXFLAGS = -Wall -Wextra  -Iheaders
# -std=c++98 
$(NAME) : $(OBJF) headers/server.hpp headers/user.hpp headers/channel.hpp headers/parser.hpp 
		$(CXX) $(CXXFLAGS) $(OBJF) -o $(NAME)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -o $@ -c $<

all : $(NAME)

clean :
		rm -f $(OBJF)
fclean : clean
		rm -f $(NAME)
re : fclean all
