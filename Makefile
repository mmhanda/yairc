# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 23:57:31 by mhanda            #+#    #+#              #
#    Updated: 2023/03/29 16:41:45 by atabiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = srcs/main.cpp srcs/server.cpp srcs/command.cpp srcs/user.cpp srcs/channel.cpp \
./srcs/args_checker.cpp ./srcs/input_parsing.cpp ./srcs/cmds.cpp ./commands/check_NOTICE.cpp \
 ./commands/check_NICK.cpp   ./commands/check_USER.cpp ./commands/check_JOIN.cpp ./commands/check_PART.cpp  ./commands/check_PRIVMSG.cpp

OBJF = $(SRC:.cpp=.o)

NAME = ircserv

CXX = c++

CXXFLAGS = -g -Wall -Wextra  -Iheaders 
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
