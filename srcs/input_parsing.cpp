/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/26 11:20:07 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "server.hpp"
#include "user.hpp"

int parse_command(std::string &input, const int fd, user *user_)
{
	char *str;
	char *str1;

	str = NULL;
	str1 = NULL;
	std::cout << "from limchat= " << input << std::endl;
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
			user *tmp = NULL;
			tmp = map_users.at(fd);

			if (splited_line[0] == "PASS")
			{
				check_PASS(splited_line, tmp);
			}
			else if (splited_line[0] == "NICK")
			{
				check_NICK(splited_line, tmp);
			}
			else if (splited_line[0] == "USER")
			{
				check_USER(splited_line, tmp);
			}
			else if (splited_line[0] == "OPER")
			{
				check_OPER(splited_line);
			}
			else if (splited_line[0] == "QUIT")
			{
				check_QUIT(back_up_input, user_);
			}
			else if (splited_line[0] == "JOIN")
			{
				////           may be for later !
				// char join_message[256];
				// snprintf(join_message, sizeof(join_message), ":abc JOIN #test\r\n");
				// std::cout << join_message;
				// send(fd, join_message , strlen(join_message) , 0);
				/////
				check_JOIN(splited_line, user_);
				// char join_message[256];
				// snprintf(join_message, sizeof(join_message), ":%s!%s@%s JOIN #%s\r\n", user_->nickname().c_str(), user_->username().c_str(), "127.0.0.1", splited_line[1].c_str());
				// send(fd, join_message, strlen(join_message), 0);
				// snprintf(join_message, sizeof(join_message), "JOIN %s\r\n", splited_line[1].c_str());
				// send(user_->client_fd(), join_message, strlen(join_message), 0);
			}
			else if (splited_line[0] == "LIST" && splited_line.size() == 1)
			{
				check_LIST(splited_line, user_);
			}
			else if (splited_line[0] == "PART")
			{
				check_PART(splited_line, user_);
			}
			else if (splited_line[0] == "MODE")
			{
				std::cout << "MODE COMMAND" << std::endl;
			}
			else if (splited_line[0] == "PRIVMSG")
			{
				check_PRIVMSG(splited_line, back_up_input, user_);
			}
			else if (splited_line[0] == "NOTICE")
			{
				check_NOTICE(splited_line, back_up_input, user_);
			}
			else if (splited_line[0] == "TOPIC")
			{
				// check_NOTICE(splited_line, back_up_input);
			}
			// else if (user_->chan != nullptr) {
			// 	user_->chan->broadcast(back_up_input, user_);
			// }
		}
	}
	return 0;
}
