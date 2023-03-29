/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:01:15 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 21:51:57 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "channel.hpp"

int check_OPER(std::vector<std::string> const &splited_line)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	return (0);
}

int check_QUIT(std::string &back_up_input, user *user)
{
	char *str1;
	back_up_input.erase(std::remove(back_up_input.begin(), back_up_input.end(), '\n'), back_up_input.end());
	back_up_input.erase(std::remove(back_up_input.begin(), back_up_input.end(), '\r'), back_up_input.end());
	str1 = const_cast<char *>(back_up_input.c_str());
	str1 = strtok(str1, ":");
	str1 = strtok(NULL, ":");
	if (str1 != NULL)
	{
		std::string message = "QUIT ERROR :Closing link: [";
		message = message + str1 + "]\n";
		::send(user->client_fd(), message.c_str(), message.length(), 0);
		close(user->client_fd());
	}
	if (str1 == NULL)
	{
		std::string message = "QUIT ERROR :Closing link: [User exited]\r\n";
		::send(user->client_fd(), message.c_str(), message.length(), 0);
		close(user->client_fd());
	}

	return (0);
}

std::string append_msgs(std::vector<std::string> splited_msg)
{

	std::string ret;
	int dots = 0;

	for (size_t i = 2; i < splited_msg.size(); i++)
	{

		if (std::find(splited_msg[i].begin(), splited_msg[i].end(),
					  ':') == splited_msg[i].end() &&
			dots == 0)
		{
			dots++;
			ret += ":";
		}
		dots++;
		ret += splited_msg[i];
		ret += " ";
	}

	return ret;
}

int check_KICK(std::vector<std::string> const &splited_line, std::string &input, user *tmp)
{
	std::string message;
	std::string part_one;
	std::string chan;
	std::string user;
	std::istringstream line_to_stream(input);
	std::getline(line_to_stream, part_one, ':');
	std::getline(line_to_stream, message, ':');
	std::cerr << "input  = " << input << std::endl;
	std::cerr << "message  = " << message << std::endl;
	std::cerr << "part_one  = " << part_one << std::endl;

	if (splited_line[1].find('#') > splited_line[1].size())
	{
		std::string error_(":ircserv 476 KICK Bad Channel Mask\r\n");
		send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
		return (0);
	}

	// kick the user from the channel here
	return (0);
}

int check_TOPIC(std::vector<std::string> &splited_line, user *user_)
{
	//(332) "<client> <channel> :<topic>"
	std::map<std::string, class channel *>::iterator iter = map_channels.find(splited_line[1]); // find the exact chan

	if (iter == map_channels.end()) {
		std::string msg = ":ircserv 401 " + splited_line[1] + " :Topic No such channel\r\n";
		send(user_->client_fd(), msg.c_str(), msg.length(), 0);
		return (0);
	}

	if (splited_line.size() == 3)
	{
		if (user_->chan != nullptr)
		{
			std::string mesg;

			if (user_->chan->topic().empty())
			{
				mesg = ":ircserv 331 " + user_->username() + " " + user_->chan->name() + " :No topic is set\r\n";
				send(user_->client_fd(), mesg.c_str(), mesg.length(), 0);
				return 0;
			}
			else
			{
				mesg = ":irserv 332 ";
				mesg = mesg + user_->username() + " " + splited_line[1] + " :" + user_->chan->topic() + "\r\n";
				send(user_->client_fd(), mesg.c_str(), mesg.length(), 0);
				return 0;
			}
		}
		else
		{
			std::string msg("403: * No such channel\r\n");
			send(user_->client_fd(), msg.c_str(), msg.length(), 0);
			return 0;
		}
	}
	else // set topic
	{
		// to do else if oper
		
		
		if (user_->chan != NULL)
		{
			std::map<std::string, class channel *>::iterator iter = map_channels.find(splited_line[1]); // find the exact chan
			if (iter != map_channels.end())
			{
				std::string topic(append_msgs(splited_line));
				iter->second->set_topic(topic); // here i change the topic of the chan
			}
			else
			{
				std::string msg("403: * No such channel\r\n");
				send(user_->client_fd(), msg.c_str(), msg.length(), 0);
				return 0;
			}
		}
	}
	return 0;
}