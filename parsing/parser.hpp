/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:20:51 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/12 18:09:07 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int	parse_command(void);
int	checker(int ac, char **av);
int check_PASS(std::vector<std::string> const & splited_line);
int check_NICK(std::vector<std::string> const & splited_line);
int check_USER(std::vector<std::string> const & splited_line);
int check_OPER(std::vector<std::string> const & splited_line);
int check_QUIT(char	*str1, std::string const & back_up_input);
int check_JOIN(std::vector<std::string>  & splited_line);
int check_PART(std::vector<std::string>  & splited_line);
int check_PRIVMSG(std::vector<std::string>  & splited_line);
int	check_NOTICE(std::vector<std::string> &splited_line, std::string &back_up_input);