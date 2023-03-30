/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_PRIVMSG.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:16:29 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 21:48:04 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

int check_PRIVMSG(std::vector<std::string> &splited_line, user *user_)
{
	size_t x;
	x = 0;
	if (splited_line.size() >= 3 && (std::find(server_user_names.begin(), server_user_names.end(),
											   splited_line[1]) != server_user_names.end()))
	{
		std::cout << "USER \n";
		std::string broad;
		if (splited_line.size() == 3)
		{

			broad = ":" + user_->username() + "!" + user_->username() + "@ircserv PRIVMSG " + splited_line[1] + " " + splited_line[2] + "\r\n";
		}
		else
		{
			broad = ":" + user_->username() + "!" + user_->username() + "@ircserv PRIVMSG " + splited_line[1] + " " + append_msgs(splited_line) + "\r\n";
		}
		send(map_for_privat_msg.at(splited_line[1]), broad.c_str(), broad.size(), 0);
	}

	else if (splited_line.size() >= 1 && std::find(channels_name.begin(), channels_name.end(), splited_line[1]) != channels_name.end())
	{
		if (user_->chan != nullptr)
		{
			std::string broad;
			if (splited_line.size() == 3) {
				broad = "PRIVMSG " + user_->chan->name() + " " + splited_line[2] + "\r\n";
			}
			else {
				broad = "PRIVMSG " + user_->chan->name() + " " + append_msgs(splited_line) + "\r\n";
			}
			std::map<std::string, class channel *>::iterator iter;
			iter = channels.begin();

			for (std::vector<int>::iterator it = user_->chan->users_fd.begin(); it != user_->chan->users_fd.end(); ++it)
			{
				int user_fd = *it;
				if (user_->client_fd() != user_fd)
				{
					send(user_fd, broad.c_str(), broad.size(), 0);
				}
			}

			// for (int user_fd : user_->chan->users_fd)
			// {
			// 	if (user_->client_fd() != user_fd)
			// 	{
			// 		send(user_fd, broad.c_str(), broad.size(), 0);
			// 	}
			// }
		}
	}
	else
	{
		std::string sen = ":loacalhost 401 " + splited_line[1] + " No such channel or user name\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		return (0);
	}
	return (0);
}
