/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_USER.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:10:45 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 13:11:01 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"
#include "channel.hpp"
int check_USER(std::vector<std::string> const &splited_line, user *user)
{
	if (splited_line.size() != 5)
		return 0;
	if (user->USER_authenticated == true)
		return (1);
	if (std::find(server_user_names.begin(), server_user_names.end(),
				  splited_line[1]) != server_user_names.end())
	{
		std::string sen = "invalid username :already exist\r\n";
		send(user->client_fd(), sen.c_str(), sen.size(), 0);
		user->PRINTER = false;
	}
	else
	{
		user->username(splited_line[1]);
		server_user_names.push_back(user->username());
		map_for_privat_msg.insert(std::pair<std::string, int>(user->username(), user->client_fd()));
		user->PRINTER = true;
		user->USER_authenticated = true;
	}
	return (1);
}
