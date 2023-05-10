#include "server.hpp"

class bot Helper_BoT;

int parse_command(std::string &input, user *user_)
{
	char *str;
	char *str1;

	str = NULL;
	str1 = NULL;
	std::vector<std::string> splited_line;
	std::string back_up_input;
	back_up_input = input;
	if (!input.empty())
	{
		input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
		input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
		str = const_cast<char *>(input.c_str());
		str = strtok(str, " ");
		if (str != NULL)
		{
			while (str != NULL)
			{
				splited_line.push_back(str);
				str = strtok(NULL, " ");
			}
			std::transform(splited_line[0].begin(), splited_line[0].end(), splited_line[0].begin(), toupper);
			if (splited_line[0] == "PASS")
				check_PASS(splited_line, user_);
			else if (splited_line[0] == "NICK")
				check_NICK(splited_line, user_);
			else if (splited_line[0] == "USER")
				check_USER(splited_line, user_);
			else if (splited_line[0] == "QUIT")
				check_QUIT(back_up_input, user_);
			else if (splited_line[0] == "PART")
				check_PART(splited_line, user_);
			else if (splited_line[0] == "JOIN")
				check_JOIN(splited_line, user_);
			else if (splited_line[0] == "PRIVMSG")
				check_PRIVMSG(splited_line, user_);
			else if (splited_line[0] == "NOTICE")
				check_NOTICE(splited_line, user_);
			else if (splited_line[0] == "TOPIC")
				check_TOPIC(splited_line, user_);
			else if (splited_line[0] == "MODE")
				check_MODE(splited_line, user_);
			else if (splited_line[0] == "KICK")
				check_KICK(splited_line, back_up_input, user_);
			else if (splited_line[0] == "BOT")
			{
				if (splited_line.size() == 1)
					Helper_BoT.start(user_->client_fd());
				if (splited_line.size() == 2 && splited_line[1] == "chan")
					Helper_BoT.channel_list(user_->client_fd());
				if (splited_line.size() == 2 && splited_line[1] == "random")
					Helper_BoT.random_join(user_);
			}
		}
	}
	return 0;
}
