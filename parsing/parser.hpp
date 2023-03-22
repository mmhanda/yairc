/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:20:51 by atabiti           #+#    #+#             */
//   Updated: 2023/03/14 02:18:42 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../headers/client.hpp"

#define CLIENT_MAX_NICKNAME 9

int	parse_command(std::string &input , const int fd);
int	checker(int ac, char **av,int		&port);
int	check_PASS(std::vector<std::string> const &splited_line , client *tmp);
// int check_NICK(std::vector<std::string> const & splited_line);
int	check_NICK(std::vector<std::string> const &splited_line, client *tmp);
// int check_USER(std::vector<std::string> const & splited_line);
int	check_USER(std::vector<std::string> const &splited_line, client *tmp);
int check_OPER(std::vector<std::string> const & splited_line);
int check_QUIT(char	*str1, std::string const & back_up_input);
int check_JOIN(std::vector<std::string>  & splited_line);
int check_PART(std::vector<std::string>  & splited_line);
// int check_PRIVMSG(std::vector<std::string>  & splited_line);
int	check_PRIVMSG(std::vector<std::string> &splited_line , std::string &back_up);
int	check_NOTICE(std::vector<std::string> &splited_line, std::string &back_up_input);
