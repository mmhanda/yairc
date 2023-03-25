/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:17:29 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/25 10:47:16 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int check_NICK(std::vector<std::string> const &splited_line, user *user)
{
	if (splited_line.size() != 2)
		return (0);
	if (user->NICK_authenticated == true)
		return(1);
	if (std::find(server_nick_names.begin(), server_nick_names.end(),
		splited_line[1]) != server_nick_names.end()) {
		std::string sen = "invalid nickname :already exist\n";
		send(user->client_fd(), sen.c_str(), sen.size(), 0);
		user->PRINTER = false;
	}
	else{
		user->nickname(splited_line[1]);
		server_nick_names.push_back(user->nickname());
		user->PRINTER = true;
		user->NICK_authenticated = true;
	}
	return (1);
}

int check_USER(std::vector<std::string> const &splited_line, user *user)
{
	if (splited_line.size() != 5)
		return 0;
	if (user->USER_authenticated == true)
		return (1);
	if (std::find(server_user_names.begin(), server_user_names.end(),
		splited_line[1]) != server_user_names.end()) {
		std::string sen = "invalid username :already exist\n";
		send(user->client_fd(), sen.c_str(), sen.size(), 0);
		user->PRINTER = false;
	}
	else{
		user->username(splited_line[1]);
		server_user_names.push_back(user->username());
		user->PRINTER = true;
		user->USER_authenticated = true;
	}
	return (1);
}

int check_OPER(std::vector<std::string> const &splited_line)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	return (0);
}

int check_QUIT(std::string  &back_up_input, user *user)
{
	char *str1;
	back_up_input.erase(std::remove(back_up_input.begin(), back_up_input.end(), '\n'), back_up_input.end());
	back_up_input.erase(std::remove(back_up_input.begin(), back_up_input.end(), '\r'), back_up_input.end());
	str1 = const_cast<char *>(back_up_input.c_str());
	str1 = strtok(str1, ":");
	str1 = strtok(NULL, ":");
	if (str1 != NULL)
	{
		std::string message =  "QUIT ERROR :Closing link: [";
		message = message + str1 + "]\n" ;
		::send(user->client_fd(),  message.c_str() , message.length(), 0);
			close(user->client_fd());
	}
	if (str1 == NULL)
	{
		std::string message =  "QUIT ERROR :Closing link: [User exited]\n";
		::send(user->client_fd(),  message.c_str() , message.length(), 0);
		close(user->client_fd());
	}

	return (0);
}

int check_JOIN(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;
	if (splited_line.size() <= 1)
		send(user->client_fd(), "461 JOIN :Not enough parameters\n", 32, 0);
	else
	{
		std::map<std::string, std::string> channels_map;
		std::vector<std::string> channels;
		std::vector<std::string> password;
		while (splited_line[1].find(",") <= splited_line[1].size())
		{
			channels.push_back((splited_line[1].substr(0,
													   splited_line[1].find(","))));
			splited_line[1].erase(0, splited_line[1].find(",") + 1);
		}
		channels.push_back((splited_line[1].substr(0)));
		while (splited_line[2].find(",") <= splited_line[2].size() && !splited_line[2].empty())
		{
			password.push_back((splited_line[2].substr(0, splited_line[2].find(","))));
			splited_line[2].erase(0, splited_line[2].find(",") + 1);
		}
		password.push_back((splited_line[2].substr(0)));
		h = 0;
		while (h < channels.size())
		{
			channels_map.insert(
				std::pair<std::string, std::string>(channels[h], password[h]));
			if (channels[h].empty())
			{
				return (0);
			}
			h++;
		}
		std::map<std::string, std::string>::iterator it;
		it = channels_map.begin();
		while (it != channels_map.end())
		{

			if (map_channels.find(it->first) != map_channels.end())
			{
				if (map_channels.at(it->first)->passwrd() == it->second)
				{
					channel *tmp = map_channels.at(it->first);
					tmp->insert_users(user);
					std::string sen = "you have joined channel " + it->first + "\n";
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
				}
				else {
					std::string sen = "Pssword needed or wrong password\n";
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
				}
			}
			else
			{
				std::string sen = "Channel "  + it->first +" has been created\n";
				send(user->client_fd(), sen.c_str(), sen.size(), 0);
				channel *tmp = new channel(it->first, it->second);
				map_channels.insert(std::pair<std::string, channel *>(it->first, tmp));
				tmp->insert_users(user);
			}
			it++;
		}
	}
	return (0);
}

int check_PART(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;
	if (splited_line.size() <= 1 || splited_line.size() >= 3)
	{
		std::string sen = "461 PART :Not enough parameters\n";
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
				if (user->chan != nullptr && map_channels.at(channels_[h])->how_many_usr() >= 2) {
					std::string send_to_others = "user " + user->username()
							+ " has left the cahnnel\n";
					user->chan->broadcast(send_to_others, user);
					std::string sen = "you have left channel " + channels_[h];
					map_channels.at(channels_[h])->part_user(user);
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
				}
				else {
					std::string sen = "you have left channel " + channels_[h] + "\n";
					map_channels.at(channels_[h])->part_user(user);
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
					map_channels.erase(channels_[h]);
				}
			}
			h++;
		}
	}
	return (0);
}

int check_PRIVMSG(std::vector<std::string> &splited_line, std::string &back_up)
{
	size_t x;
	char *str1;

	x = 0;
	if (splited_line.size() > 2)
	{
		std::vector<std::string> message_receivers;
		while (splited_line[1].find(",") <= splited_line[1].size())
		{
			message_receivers.push_back((splited_line[1].substr(0,
																splited_line[1].find(","))));
			splited_line[1].erase(0, splited_line[1].find(",") + 1);
		}
		message_receivers.push_back((splited_line[1].substr(0)));
		x = 0;
		while (x < message_receivers.size())
		{
			std::cout << "message_receivers = " << message_receivers[x] << std::endl;
			if (message_receivers[x].empty())
			{
				std::cerr << splited_line[0] << " :Wrong input" << std::endl;
				return (0);
			}
			x++;
		}
		str1 = const_cast<char *>(back_up.c_str());
		str1 = strtok(str1, ":");
		str1 = strtok(NULL, ":");
		if (str1 == NULL || strcmp(str1, "") == 0)
		{
			std::cerr << splited_line[0] << " :Wrong input" << std::endl;
			return (0);
		}
		std::cout << "str1: " << str1 << "||" << std::endl;
	}
	else
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
		return (0);
	}
	return (0);
}

int check_NOTICE(std::vector<std::string> &splited_line,
				 std::string &back_up_input)
{
	if (splited_line.size() >= 3)
	{
		std::string message;
		std::string nickname;
		nickname = splited_line[1];
		back_up_input.erase(back_up_input.find("NOTICE"),
							splited_line[0].length());
		back_up_input.erase(back_up_input.find(splited_line[1]),
							splited_line[1].length());
		std::cout << "nickname " << nickname << std::endl
				  << std::endl
				  << std::endl
				  << std::endl;								  
		std::cout << "MESSAGE:" << back_up_input << std::endl;
	}
	else
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
		return (0);
	}
	return (0);
}

int	check_KICK(std::string &input, user *tmp)
{
	std::string message;
	std::string part_one;
	std::string chan;
	std::string user;


	std::istringstream line_to_stream(input);
	std::getline(line_to_stream , part_one , ':');
	std::getline(line_to_stream , message , ':');
		std::cerr << "input  = " <<  input<<std::endl;
		std::cerr << "message  = " <<  message<<std::endl;
		std::cerr << "part_one  = " <<  part_one<<std::endl;
	return (0);
}