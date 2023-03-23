/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
//   Updated: 2023/03/23 21:09:06 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "parser.hpp"

int	parse_command(std::string &input , const int fd) {
	char	*str;
	char	*str1;

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
				user *tmp = NULL;
				tmp = ircserv.get_user(fd);

				if (splited_line[0] == "PASS")
				{
					check_PASS(splited_line , tmp);
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
					check_QUIT(str1, back_up_input);
				}
				else if (splited_line[0] == "JOIN")
				{
					check_JOIN(splited_line);
				}
				else if (splited_line[0] == "PART")
				{
					check_PART(splited_line);
				}
				else if (splited_line[0] == "MODE")
				{
					std::cout << "MODE COMMAND" << std::endl;
				}
				else if (splited_line[0] == "PRIVMSG")
				{
					check_PRIVMSG(splited_line, back_up_input);
				}
				else if (splited_line[0] == "NOTICE")
				{
					check_NOTICE(splited_line, back_up_input);
				}
			}
		}
		return 0;
}
