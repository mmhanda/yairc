#include "server.hpp"
#include "channel.hpp"

int check_OPER(std::vector<std::string> const &splited_line, user *tmp)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	// else
	// {
	// 	/*ERR_PASSWDMISMATCH (464)  "<client> :Password incorrect"*/
	// 	/*RPL_YOUREOPER (381)  "<client> :You are now an IRC operator"*/
	// 	tmp->chan();
	// 	// if(tmp->) //   OPER foo bar
	// 	// {

	// 	// }
	// }
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

int check_TOPIC(std::vector<std::string> &splited_line, user *user_)
{
	std::map<std::string, class channel *>::iterator it = map_channels.find(splited_line[1]);
	if (it == map_channels.end())
	{
		std::string msg("403: * No such channel\r\n");
		send(user_->client_fd(), msg.c_str(), msg.length(), 0);
		return 0;
	}
	std::vector<std::string> admins_list = it->second->get_admins_list();
	// if(admins_list.find(splited_line[2]) == admins_list.end())
	if (std::find(admins_list.begin(), admins_list.end(), user_->username()) == admins_list.end())
	{
		// ERR_CHANOPRIVSNEEDED (482)  "<client> <channel> :You're not channel operator"
		std::string error_(":ircserv 482 KICK : :You're not channel operator\r\n");
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
		// to do else if oper
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
