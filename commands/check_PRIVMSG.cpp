#include "server.hpp"
#include "channel.hpp"

int check_PRIVMSG(std::vector<std::string> &splited_line, user *user_)
{
	if (splited_line.size() >= 3 && (std::find(server_user_names.begin(), server_user_names.end(),
											   splited_line[1]) != server_user_names.end())) {
		std::cout << "USER \n";
		std::string broad;
		if (splited_line.size() == 3)
			broad = ":" + user_->username() + "!" + user_->username()
				+ "@ircserv PRIVMSG " + splited_line[1] + " " + splited_line[2] + "\r\n";
		else
			broad = ":" + user_->username() + "!" + user_->username()
				+ "@ircserv PRIVMSG " + splited_line[1] + " " + append_msgs(splited_line) + "\r\n";

		send(map_for_privat_msg.at(splited_line[1]), broad.c_str(), broad.size(), 0);
	}

	else if (splited_line.size() >= 1 && std::find(channels_name.begin(), channels_name.end(), splited_line[1]) != channels_name.end())
	{
		std::cout << "BREFOR  \n"; 
		if (user_->chan != nullptr)
		{
			std::cout << "AFTER \n";
			std::string broad;
			if (splited_line.size() == 3)
				broad = SEND_TO_USRS(user_->username(), user_->username(), user_->chan->name(), splited_line[2]);
			else
				broad = SEND_TO_USRS(user_->username(), user_->username(), user_->chan->name(), append_msgs(splited_line));
			std::map<std::string, class channel *>::iterator iter;
			std::cout << broad << std::endl;

			iter = channels.begin();

			for (std::vector<int>::iterator it = user_->chan->users_fd.begin(); it != user_->chan->users_fd.end(); ++it)
			{
				int user_fd = *it;
				if (user_->client_fd() != user_fd)
				{
					send(user_fd, broad.c_str(), broad.size(), 0);
				}
			}
		}
	}
	else
	{
		std::string sen = ":ircserve 401 " + splited_line[1] + " No such channel or user name\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		return (0);
	}
	return (0);
}
