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
	}

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
		std::map<std::string, class channel *>::iterator it = map_channels.find(splited_line[1]); 
		std::vector<std::string> admins_list  = it->second->get_admins_list();
		if(std::find(admins_list.begin(), admins_list.end(),  tmp->username()) == admins_list.end())
		{
			std::string error_(":ircserv 482 KICK : :You're not channel operator\r\n");
			send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
			return 0;
		}
		if (tmp->chan == NULL)
		{
			std::string error_(":ircserv 442 KICK :You're not on that channel\r\n");
			send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
			return 0;
		}

		if (tmp->chan->name() != splited_line[1])
		{
			std::string error_(":ircserv 442 KICK :You're not on that channel\r\n");
			send(tmp->client_fd(), error_.c_str(), error_.length(), 0);
		}
	}
	if (map_channels.find(splited_line[1]) != map_channels.end())
	{
		if (tmp->chan != nullptr && map_channels.at(splited_line[1])->how_many_usr() >= 2)
		{
			std::map<std::string, class channel *>::iterator iter = map_channels.find(splited_line[1]);
			if (iter != map_channels.end())
			{

				iter->second->banned_kicked_users.push_back(splited_line[2]);
				std::string send_to_others(":");
				send_to_others = send_to_others + tmp->nickname() + "!" + tmp->username() + "localhost" + " KICK " + splited_line[1] + " " + splited_line[2] + "\r\n";
				tmp->chan->broadcast(send_to_others);
				std::string send_to_others_2 = PART(splited_line[2], splited_line[2], splited_line[1]) + "\r\n";
				tmp->chan->broadcast(send_to_others_2);

				user *to_kick = iter->second->all_users.at(splited_line[2]);
				iter->second->part_user(to_kick);
			}

		}
	}

	return (0);
}