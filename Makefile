SRC = srcs/main.cpp srcs/server.cpp srcs/command.cpp srcs/user.cpp srcs/channel.cpp \
./srcs/args_checker.cpp ./srcs/input_parsing.cpp ./srcs/cmds.cpp ./srcs/bot.cpp ./commands/check_NOTICE.cpp \
./commands/check_NICK.cpp   ./commands/check_USER.cpp ./commands/check_JOIN.cpp ./commands/check_PART.cpp\
./commands/check_PRIVMSG.cpp ./commands/check_MODE.cpp ./commands/check_TOPIC.cpp ./commands/check_KICK.cpp

OBJF = $(SRC:.cpp=.o)

NAME = ircserv

CXX = c++

CXXFLAGS =  -Iheaders

$(NAME) : $(OBJF) headers/server.hpp headers/user.hpp headers/channel.hpp headers/bot.hpp headers/parser.hpp
		$(CXX) $(CXXFLAGS) $(OBJF) -o $(NAME)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -o $@ -c $<

all : $(NAME)

clean :
		rm -f $(OBJF)
fclean : clean
		rm -f $(NAME)
re : fclean all
