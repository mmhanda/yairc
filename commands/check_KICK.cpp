#include "server.hpp"

int check_KICK(std::vector<std::string> const &splited_line, std::string &input, user *tmp)
{
	std::string message;
	std::string part_one;
	std::string chan;
	if (splited_line.size() <= 2)
	{
		std::string error_(":ircserv 461 KICK  :Not enough parameters\r\n");
		send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
		return 0;
	}
	if (splited_line.size() > 3)
	{
		std::istringstream line_to_stream(input);
		std::getline(line_to_stream, part_one, ':');
		std::getline(line_to_stream, message, ':');
		std::cerr << "input  = " << input << std::endl;
		std::cerr << "message  = " << message << std::endl;
		std::cerr << "part_one  = " << part_one << std::endl;
	}
	// else
	// {
	// 	std::cerr << "input  = " << input << std::endl;
	// }
	if (splited_line[1].find('#') > splited_line[1].size())
	{
		std::string error_(":ircserv 476 KICK Bad Channel Mask\r\n");
		send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
		return (0);
	}

	if (map_channels.find(splited_line[1]) == map_channels.end())
	{
		std::string error_(":ircserv 403 KICK :No such channel\r\n");
		send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
		return 0;
	}
	else
	{
		if (tmp->chan == NULL)
		{
			std::string error_(":ircserv 442 KICK :You're not on that channel\r\n");
			send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
			return 0;
		}

		std::map<std::string, class channel *>::iterator iter = map_channels.find(splited_line[1]);
		// if (iter->second->name() != splited_line[1])
		if (tmp->chan->name() != splited_line[1])
		{
			std::string error_(":ircserv 442 KICK :You're not on that channel\r\n");
			send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
		}
		return 0;
	}
std::cout << ""
	if (map_channels.find(splited_line[1]) != map_channels.end())
	{
		if (tmp->chan != nullptr && map_channels.at(splited_line[1])->how_many_usr() >= 2)
		{
			std::string send_to_others = KICK(tmp->username(), splited_line[2], splited_line[1]) + "\r\n";
			tmp->chan->broadcast(send_to_others);
			map_channels.at(splited_line[1])->part_user(map_channels.at(splited_line[1])->kick_list().at(splited_line[2]));
		}
		else if (tmp->chan != nullptr && map_channels.at(splited_line[1])->how_many_usr() == 1)
		{
			std::string send_to_others = KICK(tmp->username(), splited_line[2], splited_line[1]) + "\r\n";
			tmp->chan->broadcast(send_to_others);
			map_channels.at(splited_line[1])->part_user(map_channels.at(splited_line[1])->kick_list().at(splited_line[2]));
			map_channels.erase(splited_line[1]);
		}
	}

	// kick the user from the channel here
	return (0);
}