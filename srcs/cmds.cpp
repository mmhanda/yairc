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

