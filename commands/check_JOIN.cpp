/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_JOIN.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:13:03 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 16:31:18 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"
#include "channel.hpp"


int check_JOIN(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;

	if (splited_line.size() <= 1)
	{
		send(user->client_fd(), "461 JOIN :Not enough parameters\r\n", 33, 0);
		return 0;
	}
	else
	{
		std::map<std::string, std::string> channels_parse;
		std::vector<std::string> channels;
		std::vector<std::string> password;

		std::istringstream line_to_stream(splited_line[1]);
		std::string read_here;
		if (splited_line.size() == 3)
		{

			std::istringstream line_to_stream_2(splited_line[2]);

			while (getline(line_to_stream_2, read_here, ','))
				password.push_back(read_here);
		}
		while (getline(line_to_stream, read_here, ','))
		{
			if (read_here.find('#') > read_here.size())
			{
				std::string error_(":localhost 476 JOIN Bad Channel Mask\r\n");
				send(user->client_fd(), error_.c_str(), error_.length(), 0);
				return (0);
			}
			channels.push_back(read_here);
		}

		h = 0;
		while (h < channels.size())
		{
			if (password.empty())
				channels_parse.insert(std::pair<std::string, std::string>(channels[h], std::string("")));
			else
				channels_parse.insert(std::pair<std::string, std::string>(channels[h], password[h]));
			h++;
		}

		std::map<std::string, std::string>::iterator it = channels_parse.begin();
		while (it != channels_parse.end())
		{
			std::map<std::string, class channel *>::iterator is_found;

			if (map_channels.find(it->first) != map_channels.end())
			{
				is_found = map_channels.find(it->first);
				if (is_found->second->passwrd() == it->second)
				{
					if (user->chan == nullptr || user->chan->name() != it->first)
					{
						channel *tmp = map_channels.at(it->first);

						tmp->insert_users(user);
						user->chan->notif_new_client_joined(user);

						std::string sen = SEND_CHAN(user->username(), user->username(), user->chan->name());
						send(user->client_fd(), sen.c_str(), sen.length(), 0);

						sen = USERS_LIST(user->username(), it->first, user->chan->users_list());
						send(user->client_fd(), sen.c_str(), sen.size(), 0);

						sen = LIST_EN(user->username(), user->chan->name());
						send(user->client_fd(), sen.c_str(), sen.size(), 0);
					}
				}
				else
				{
					std::string sen = "ERROR :Incorrect password\r\n";
					send(user->client_fd(), sen.c_str(), sen.length(), 0);
					return 0;
				}
			}
			else
			{
				channel *tmp = new channel(it->first, it->second);
				map_channels.insert(std::pair<std::string, channel *>(it->first, tmp));
				tmp->insert_users(user);
				channels_name.push_back(it->first);

				std::string sen = SEND_CHAN(user->username(), user->username(), user->chan->name());
				send(user->client_fd(), sen.c_str(), sen.size(), 0);

				sen = USERS_LIST(user->username(), user->chan->name(), user->chan->users_list());
				send(user->client_fd(), sen.c_str(), sen.size(), 0);

				sen = LIST_EN(user->username(), user->chan->name());
				send(user->client_fd(), sen.c_str(), sen.size(), 0);

				sen = "NOTICE " + user->username() + " :Mode: +nt test only!\r\n";
				send(user->client_fd(), sen.c_str(), sen.size(), 0);
				std::string tim = "NOTICE " + user->chan->name() + " :This channel was created at " + get_tim() + "\r\n";
				time_t now = time(NULL);
				char message[256];
				snprintf(message, 256, "NOTICE %s :This channel was created at %s\n", user->chan->name().c_str(), ctime(&now));
				send(user->client_fd(), tim.c_str(), tim.length(), 0);
			}
			it++;
		}
	}
	return (0);
}
