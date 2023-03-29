/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:01:15 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/29 13:10:56 by atabiti          ###   ########.fr       */
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

		std::map<std::string, std::string>::iterator it;
		it = channels_parse.begin();
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
					std::string send_to_others = PART(user->username(), user->username(), user->chan->name()) + "\r\n";
					user->chan->broadcast(send_to_others, user);
					map_channels.at(channels_[h])->part_user(user);
				}
				else if (user->chan != nullptr && map_channels.at(channels_[h])->how_many_usr() == 1)
				{
					std::string send_to_others = PART(user->username(), user->username(), user->chan->name()) + "\r\n";
					user->chan->broadcast(send_to_others, user);
					map_channels.at(channels_[h])->part_user(user);
					map_channels.erase(channels_[h]);
				}
			}
			h++;
		}
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

int check_PRIVMSG(std::vector<std::string> &splited_line, std::string &back_up, user *user_)
{
	size_t x;
	char *str1;

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
			for (int user_fd : user_->chan->users_fd)
			{
				if (user_->client_fd() != user_fd)
				{
					send(user_fd, broad.c_str(), broad.size(), 0);
				}
			}
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

int check_TOPIC(std::vector<std::string> &splited_line, std::string &back_up_input, user *user_)
{
	// if (splited_line.size() == 1)
	// {
	if (user_->chan != nullptr)
	{
		std::string mesg;

		if (user_->chan->topic().empty())
		{

			mesg = ":ircserv 331 " + user_->chan->name() + " :No topic is set\r\n";
			send(user_->client_fd(), mesg.c_str(), mesg.length(), 0);
			return 0;
		}
		else
		{
			mesg = "TOPIC: ";
			mesg = mesg + user_->chan->topic() + "\r\n";
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
	// to do else if oper
	// }
}