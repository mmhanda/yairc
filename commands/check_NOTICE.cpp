/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_NOTICE.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:01:09 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 14:59:56 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

int check_NOTICE(std::vector<std::string> &splited_line, user *user_)
{
	// if (splited_line.size() >= 3)
	// {
	// 	std::string message;
	// 	std::string nickname;
	// 	nickname = splited_line[1];
	// 	back_up_input.erase(back_up_input.find("NOTICE"), splited_line[0].length());
	// 	back_up_input.erase(back_up_input.find(splited_line[1]), splited_line[1].length());
	// 	back_up_input.erase(std::remove(back_up_input.begin(), back_up_input.end(), '\r'), back_up_input.end());
	// 	back_up_input.erase(std::remove(back_up_input.begin(), back_up_input.end(), '\n'), back_up_input.end());

	// 	std::cout << "MESSAGE:" << back_up_input << std::endl;
	// 	std::string broad;
	// 	broad = ":" + user_->username() + "!" + user_->username() + "@localhost " + back_up_input + "\r\n";
	// 	std::cout << "broad :" << back_up_input << std::endl;

	// 		user_->chan->broadcast(broad, user_);

	// }
	// else
	// {
	// 	std::string sen = "461 NOTICE  :Not enough parameters \r\n";
	// 	send(user_->client_fd(), sen.c_str(), sen.size(), 0);
	// 	return (0);
	// }
	// return (0);
	size_t x;

	x = 0;
	if (splited_line.size() >= 3 && (std::find(server_user_names.begin(), server_user_names.end(),
											   splited_line[1]) != server_user_names.end()))
	{
		std::cout << "USER \n";
		std::string broad;
		if (splited_line.size() == 3)
		{

			broad = ":" + user_->username() + "!" + user_->username() + "@localhost PRIVMSG " + splited_line[1] + " " + splited_line[2] + "\r\n";
		}
		else
		{
			broad = ":" + user_->username() + "!" + user_->username() + "@localhost PRIVMSG " + splited_line[1] + " " + append_msgs(splited_line) + "\r\n";
		}
		send(map_for_privat_msg.at(splited_line[1]), broad.c_str(), broad.size(), 0);
	}

	else if (splited_line.size() >= 1 && std::find(channels_name.begin(), channels_name.end(), splited_line[1]) != channels_name.end())
	{
		if (user_->chan != nullptr)
		{
			std::string broad;
			if (splited_line.size() == 3)
			{
				broad = "PRIVMSG " + user_->chan->name() + " " + splited_line[2] + "\r\n";
			}
			else
			{
				broad = "PRIVMSG " + user_->chan->name() + " " + append_msgs(splited_line) + "\r\n";
			}
			std::map<std::string, class channel *>::iterator iter;
			iter = channels.begin();

			for (std::vector<int>::iterator it =  user_->chan->users_fd.begin(); it !=  user_->chan->users_fd.end(); ++it)
			{
				int user_fd = *it;
				if (user_->client_fd() != user_fd)
				{
					send(user_fd, broad.c_str(), broad.size(), 0);
				}
			}
			//working
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
