/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:17:29 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/26 11:45:07 by mhanda           ###   ########.fr       */
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
	if (std::find(server_nick_names.begin(), server_nick_names.end(),
				  splited_line[1]) != server_nick_names.end())
	{
		std::string sen = "invalid nickname :already exist\r\n";
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

int check_JOIN(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;

	if (splited_line.size() <= 1)
		send(user->client_fd(), "461 JOIN :Not enough parameters\r\n", 33, 0);
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
			std::cout << "already  " << std::endl;
			if (map_channels.find(it->first) != map_channels.end())
			{
				if (map_channels.at(it->first)->passwrd() == it->second)
				{
					channel *tmp = map_channels.at(it->first);
					tmp->insert_users(user);
					std::string sen = ":" + user->nickname() + "!" + user->username() + "@localhost JOIN " + user->chan->name() + "\r\n";
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
				}
				else
				{
					std::string sen = "ERROR :Incorrect password\r\n";
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
				}
			}
			else
			{
				std::cout << "new channel  " << std::endl;

				channel *tmp = new channel(it->first, it->second);
				map_channels.insert(std::pair<std::string, channel *>(it->first, tmp));
				tmp->insert_users(user);
				channels_name.push_back(it->first);

				// std::string msg ("JOIN ");
				// std::string msg1 (":");
				// msg1 = msg1 + user->username() + " " + "JOIN " + it->first + "\r\n";

				// msg = msg + "#"+it->first+" \r\n";
				// send(user->client_fd(), msg.c_str() , msg.length() , 0);
				// send(user->client_fd(), msg1.c_str() , msg1.length() , 0);

				std::string sen1 = ":" + user->nickname() + "!" + user->username() + "@localhost JOIN " + user->chan->name() + "\n";
				send(user->client_fd(), sen1.c_str(), sen1.size(), 0);
				std::string sen2 = "NOTICE " + user->username() + " :Mode: +nt test only!\r\n";
				send(user->client_fd(), sen2.c_str(), sen2.size(), 0);
				time_t now = time(NULL);
				char message[256];
				snprintf(message, 256, "NOTICE %s :This channel was created at %s\n",
						 user->chan->name().c_str(), ctime(&now));
				send(user->client_fd(), message, strlen(message), 0);
			}
			it++;
		}
	}
	return (0);
}

int check_LIST(std::vector<std::string> &splited_line, user *user)
{
	std::string list;
	std::map<std::string, class channel *>::iterator iter;
	std::string channel_list;
	iter = map_channels.begin();

	while (iter != map_channels.end())
	{

		channel_list += iter->second->name() + " ";
		iter++;
	}
	std::string numeric_reply = "322";
	std::string properties = " :End of /LIST";
	std::string response = ":" + std::string("127.0.0.1") + " " + numeric_reply + " " + channel_list + properties + "\r\n";
	send(user->client_fd(), response.c_str(), response.length(), 0);
}

int check_PART(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;
	if (splited_line.size() <= 1 || splited_line.size() >= 3)
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
					std::string send_to_others = "user " + user->username() + " has left the cahnnel\n";
					user->chan->broadcast(send_to_others, user);
					std::string sen = "you have left channel " + channels_[h];
					map_channels.at(channels_[h])->part_user(user);
					send(user->client_fd(), sen.c_str(), sen.size(), 0);
				}
				else
				{
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

int check_PRIVMSG(std::vector<std::string> &splited_line, std::string &back_up, user *user_)
{
	size_t x;
	char *str1;

	x = 0;
	if (splited_line.size() == 3)
	{
		std::cout << "hada howa message  " << splited_line[2] << std::endl;
		if (user_->chan != nullptr)
		{
			std::string broad = "PRIVMSG " + user_->chan->name() + " " + splited_line[2] + "\r\n";
			std::map<std::string, class channel *>::iterator iter;
			iter  = channels.begin();
			for (int user_fd : user_->chan->users_fd) 
			{

				{
					if (user_->client_fd() != user_fd)
					{
						send(user_fd, broad.c_str(), broad.size(), 0);
					}
				}
			}
		}
	}
	else if (splited_line.size() > 3)
	{
		std::string message;
		std::string channel_name;
		std::istringstream line_to_stream(back_up);
		std::getline(line_to_stream, channel_name, ':');
		std::getline(line_to_stream, message, ':');
		std::cerr << "input  = " << back_up << std::endl;
		std::cerr << "message  = " << message << std::endl;
		std::string remove_command("PRIVMSG");
		size_t i = channel_name.find(remove_command);
		if (i < channel_name.npos)
			channel_name.erase(i, remove_command.length());
		std::cerr << "part_one  removed = " << channel_name << std::endl;
		if (user_->chan != nullptr)
		{
			if (user_->chan != nullptr)
		{
			std::string broad = "PRIVMSG " + user_->chan->name() + " " + message + "\r\n";
			std::map<std::string, class channel *>::iterator iter;
			iter  = channels.begin();
			for (int user_fd : user_->chan->users_fd) 
			{

				{
					if (user_->client_fd() != user_fd)
					{
						send(user_fd, broad.c_str(), broad.size(), 0);
					}
				}
			}
		}
		}
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

int check_KICK(std::string &input, user *tmp)
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
	return (0);
}