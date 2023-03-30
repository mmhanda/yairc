#include "server.hpp"

int check_TOPIC(std::vector<std::string> &splited_line, user *user_)
{
    if (splited_line.size() <= 1)
        return 0;
	std::map<std::string, class channel *>::iterator it = map_channels.find(splited_line[1]);
	if (it == map_channels.end())
	{
		std::string msg("403: * No such channel\r\n");
		send(user_->client_fd(), msg.c_str(), msg.length(), 0);
		return 0;
	}
	std::vector<std::string> admins_list = it->second->get_admins_list();

	if (std::find(admins_list.begin(), admins_list.end(), user_->username()) == admins_list.end())
	{
		std::string error_(":ircserv 482 TOPIC  :You're not channel operator\r\n");
		send(user_->client_fd(), error_.c_str(), error_.length(), 0);
		return 0;
	}
	if (splited_line.size() == 2)
	{
		if (user_->chan != nullptr)
		{
			std::string mesg;
			if (user_->chan->topic().empty() && (std::find(channels_name.begin(), channels_name.end(), splited_line[1]) != channels_name.end()) && user_->chan->name() == splited_line[1])
			{
				mesg = ":ircserv 331 " + user_->chan->name() + " :No topic is set or channel not found\r\n";
				send(user_->client_fd(), mesg.c_str(), mesg.length(), 0);
				return 0;
			}
			else
			{
				if (std::find(channels_name.begin(), channels_name.end(), splited_line[1]) != channels_name.end() && user_->chan->name() == splited_line[1])
				{

					mesg = ":irserv 332 ";
					mesg = mesg + user_->username() + " " + splited_line[1] + " :" + user_->chan->topic() + "\r\n";
					send(user_->client_fd(), mesg.c_str(), mesg.length(), 0);
					return 0;
				}
			}
		}
	}
	else
	{
		if (user_->chan != nullptr)
		{
			if (std::find(channels_name.begin(), channels_name.end(), splited_line[1]) != channels_name.end() && user_->chan->name() == splited_line[1])
			{
				std::cout << "user_->chan->name() " << user_->chan->name() << std::endl;
				std::map<std::string, class channel *>::iterator iter = map_channels.find(splited_line[1]);
				std::string topic(append_msgs(splited_line));
				iter->second->set_topic(topic);
				std::string msg = "NOTICE " + user_->username() + " : Topic has been set \r\n";
				send(user_->client_fd(), msg.c_str(), msg.length(), 0);
			}
		}
	}
	return (0);
}
