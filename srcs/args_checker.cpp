/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:23:40 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/24 06:02:04 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include <iostream>
#include <stdlib.h> //for atoi
std::string PASSWORD;

/*
		Command: PASS
	Parameters: <password> (RFC 1459)
	ERRORS : ERR_ALREADYREGISTRED  ERR_NEEDMOREPARAMS
*/
int	check_PASS(std::vector<std::string> const &splited_line , user *tmp)
{
				std::cout << splited_line[1] <<std::endl;
				std::cout << splited_line[1].size() <<std::endl;

	if(tmp->PASS_authenticated == true)
	{
		std::cerr << "462 " << splited_line[0] << " :ERR_ALREADYREGISTRED" << std::endl;
		return 0;
	}
	else
	{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	else
	{
		if (splited_line[1] != PASSWORD)
		{
			std::cerr << "464 " << splited_line[0] << " :Password incorrect "  << std::endl;
			return (0);
		}
		tmp->PASS_authenticated = true;
		if(	tmp->PASS_authenticated && 	tmp->NICK_authenticated && 	tmp->USER_authenticated)
		{
					std::cout << "\e[1m"<< "🅆 🄴 🄻 🄲 🄾 🄼 🄴   🅃 🄾     🅈 🄰 🄸 🅁 🄲    🅂 🄴 🅁 🅅 🄴 🅁 " << std::endl;

		}
		}
	}

	return (0);
}


int	checker(int ac, char **av, int &port)
{
	size_t	i;

	if (ac != 3)
	{
		std::cerr << "ERROR: Your executable should be run as follows: \t./ircserv <port> <password>" << std::endl;
		return (0);
	}
	else
	{
		std::string port_checking(av[1]);
		std::string password_checking(av[2]);
		i = 0;
		while (i < port_checking.size())
		{
			if (!(std::isdigit(port_checking[i])))
			{
				std::cerr << "ERROR: <port> must be numeric" << std::endl;
				return (0);
			}
			i++;
		}
		port = atoi(av[1]);
		if (port < 0 || port > 65353)
		{
			std::cerr << "ERROR: <port> must be between 0  and 65353" << std::endl;
			return (0);
		}
		if (port >= 0 && port <= 1023)
		{
			std::cerr << "ERROR: Port numbers from 0 to 1023 are reserved for common TCP/IP applications" << std::endl;
			return (0);
		}
		PASSWORD = password_checking;
	}
	return (1);
}
