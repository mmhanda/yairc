/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:20:51 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/26 09:41:32 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "server.hpp"
#include <sstream>
#define CLIENT_MAX_NICKNAME 9

bool    authenticate(std::string &msg , const int fd, user *user_);
int	parse_command(std::string &input , const int fd, user *user_);
int	checker(int ac, char **av,int		&port);
int	check_PASS(std::vector<std::string> const &splited_line , user *tmp);
int	check_NICK(std::vector<std::string> const &splited_line, user *user);
int	check_USER(std::vector<std::string> const &splited_line, user *tmp);
int check_OPER(std::vector<std::string> const & splited_line);
int check_QUIT(std::string  & back_up_input, user *user);
int check_JOIN(std::vector<std::string>  & splited_line, user *user);
int check_LIST(std::vector<std::string>  & splited_line, user *user);
int check_PART(std::vector<std::string>  & splited_line, user *user);
int	check_KICK(std::string &input, user *tmp);
int	check_PRIVMSG(std::vector<std::string> &splited_line , std::string &back_up ,user *user_);
// int	check_PRIVMSG(std::vector<std::string> &splited_line , std::string &back_up);
// int	check_NOTICE(std::vector<std::string> &splited_line, std::string &back_up_input);
int check_NOTICE(std::vector<std::string> &splited_line,std::string &back_up_input,  user *user_);
