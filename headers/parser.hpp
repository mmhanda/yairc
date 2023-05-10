#pragma once
#include "server.hpp"

bool authenticate(std::string &msg , const int fd, user *user_);
int	parse_command(std::string &input , user *user_);
int	checker(int ac, char **av,int		&port);
int	check_PASS(std::vector<std::string> const &splited_line , user *tmp);
int	check_NICK(std::vector<std::string> const &splited_line, user *user);
int	check_USER(std::vector<std::string> const &splited_line, user *tmp);
int check_QUIT(std::string  & back_up_input, user *user);
int check_JOIN(std::vector<std::string>  & splited_line, user *user);
int check_PART(std::vector<std::string>  & splited_line, user *user);
int	check_KICK(std::vector<std::string> const &splited_line,std::string &input, user *tmp);
int	check_PRIVMSG(std::vector<std::string> &splited_line ,user *user_);
int check_NOTICE(std::vector<std::string> &splited_line, user *user);
int check_TOPIC(std::vector<std::string> &splited_line,  user *user_);
int check_MODE(std::vector<std::string> &splited_line,  user *user_);
