/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_NICK.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:09:01 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 13:09:39 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"
int check_NICK(std::vector<std::string> const &splited_line, user *user)
{
	if (splited_line.size() != 2)
		return (0);
	if (user->NICK_authenticated == true)
		return (1);
	if (std::find(server_nick_names.begin(), server_nick_names.end(), splited_line[1]) != server_nick_names.end())
	{
		std::string sen = ":localhost 433 nickname username already exist\r\n";
		send(user->client_fd(), sen.c_str(), sen.size(), 0);
		user->PRINTER = false;
	}
	else
	{
		user->nickname(splited_line[1]);
		server_nick_names.push_back(user->nickname());
		user->PRINTER = true;
		user->NICK_authenticated = true;
	}
	return (1);
}