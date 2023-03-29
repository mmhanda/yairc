/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_PART.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:14:50 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 21:57:34 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"
#include "channel.hpp"

int check_PART(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;
	if (splited_line.size() <= 1 || splited_line.size() > 3)
	{
		std::string sen = "461 PART :Not enough parameters\r\n";
		send(user->client_fd(), sen.c_str(), sen.size(), 0);
	}
	else
	{
		std::vector<std::string> channels_;
		while (splited_line[1].find(",") <= splited_line[1].size())
		{
			channels_.push_back((splited_line[1].substr(0, splited_line[1].find(","))));
			splited_line[1].erase(0, splited_line[1].find(",") + 1);
		}
		channels_.push_back((splited_line[1].substr(0)));
		while (h < channels_.size())
		{
			if (map_channels.find(channels_[h]) != map_channels.end())
			{
				if (user->chan != nullptr && map_channels.at(channels_[h])->how_many_usr() >= 2)
				{
					std::string send_to_others = PART(user->username(), user->username(), user->chan->name()) + msg_delim;
					user->chan->broadcast(send_to_others);
					map_channels.at(channels_[h])->part_user(user);
				}
				else if (user->chan != nullptr && map_channels.at(channels_[h])->how_many_usr() == 1)
				{
					std::string send_to_others = PART(user->username(), user->username(), user->chan->name()) + msg_delim;
					user->chan->broadcast(send_to_others);
					map_channels.at(channels_[h])->part_user(user);
					map_channels.erase(channels_[h]);
				}
			}
			h++;
		}
	}
	return (0);
}