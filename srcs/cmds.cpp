#include "server.hpp"

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
		if (user->chan != nullptr) {
			std::vector<std::string> msg;
			msg.push_back("PART");
			msg.push_back(user->username() );
			msg.push_back(user->chan->name());
				check_PART(msg, user);
		}
		std::string message = "QUIT ERROR :Closing link: [";
		message = message + str1 + "]\n";
		user->NICK_authenticated = false;
		user->PASS_authenticated = false;
		user->USER_authenticated = false;
		server_nick_names.erase(std::remove(server_nick_names.begin(),
			server_nick_names.end(),user->nickname()),server_nick_names.end());
		server_user_names.erase(std::remove(server_user_names.begin(),
			server_user_names.end(),user->username()),server_user_names.end());
		close(user->client_fd());
	}
	if (str1 == NULL)
	{
		std::string message = "QUIT ERROR :Closing link: [User exited]\r\n";
		::send(user->client_fd(), message.c_str(), message.length(), 0);
		if (user->chan != nullptr) {
		std::vector<std::string> msg;
		msg.push_back("PART");
		msg.push_back(user->username() );
		msg.push_back(user->chan->name());
			check_PART(msg, user);
		}
		user->NICK_authenticated = false;
		user->PASS_authenticated = false;
		user->USER_authenticated = false;
		server_nick_names.erase(std::remove(server_nick_names.begin(),
			server_nick_names.end(),user->nickname()),server_nick_names.end());
		server_user_names.erase(std::remove(server_user_names.begin(),
			server_user_names.end(),user->username()),server_user_names.end());
		close(user->client_fd());
	}

	return (0);
}

std::string append_msgs(std::vector<std::string> splited_msg)
{
	std::string ret;
	for (size_t i = 2; i < splited_msg.size(); i++)
	{
		ret += splited_msg[i];
		ret += " ";
	}
	return ret;
}
