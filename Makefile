# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 23:57:31 by mhanda            #+#    #+#              #
#    Updated: 2023/03/20 17:31:50 by mhanda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC_DIR = srcs
SRCS = $(SRC_DIR)/server.cpp $(SRC_DIR)/main.cpp
BIN_DIR = bin
OBJF = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))
INC_DIR = headers
HEADERS = $(shell find $(INC_DIR) -name '*.hpp')

CXX = c++
CXXFLAGS = -Wall -Wextra  -std=c++98
CXXFLAGS += -I$(INC_DIR)

$(NAME) : $(OBJF) $(HEADERS)
	$(CXX) $(CXXFLAGS)  $(OBJF) -o $(NAME)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D) # create directory
	$(CXX) $(CXXFLAGS) -o $@ -c $<

all : $(NAME)

clean :
	rm -f $(OBJF)
fclean : clean
	rm -f $(NAME)
re : fclean all
