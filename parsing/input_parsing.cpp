/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/24 04:58:11 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "server.hpp"
#include "user.hpp"

int	parse_command(std::string &input , const int fd)
{
	char	*str;
	char	*str1;

	str = NULL;
	str1 = NULL;

		std::vector<std::string> splited_line;
		std::string back_up_input;
		back_up_input = input;
		// std::cout << "before input = " << input << std::endl << std::endl;
		if (!input.empty())
		{
			/*const_cast <new_type> (expression) why? strtok uses char
				* and input.c_str() return const char* */
			input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
			input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());  /*IRC messages are always lines of characters terminated with a CR-LF (Carriage Return - Line Feed)*/
									// std::cerr <<	"input :: " << input  << "|||||||||";

			str = const_cast<char *>(input.c_str());
			/*
			strtok() stores the pointer in static variable where did you last time left off ,
			so on its 2nd call , when we pass the null ,
	strtok() gets the pointer from the static variable .
			If you provide the same string name ,
	it again starts from beginning.
*/
			str = strtok(str, " ");
			// std::cout << "after input = " << input << std::endl << std::endl;
			if (str != NULL)
			{
				while (str != NULL)
				{
					splited_line.push_back(str);
					str = strtok(NULL, " ");
				}

				// size_t i = 0;
				// while (i < splited_line.size())
				// {
				// 	std::cout << "splited_line [] = " << splited_line[i] << std::endl;
				// 	i++;
				// }
				user *tmp = NULL;
				tmp = ircserv.get_user(fd);

				if (splited_line[0] == "PASS")
				{
					check_PASS(splited_line , tmp);
				}
				else if (splited_line[0] == "NICK")
				{
					check_NICK(splited_line, tmp);
					// std::cout<< "tmp nick name is "<<tmp->nickname() <<std::endl;
				}
				else if (splited_line[0] == "USER")
				{
					check_USER(splited_line, tmp);
				}
				else if (splited_line[0] == "OPER")
				{
					check_OPER(splited_line);
				}
				// else if (splited_line[0] == "QUIT")
				// {
				// 	check_QUIT(str1, back_up_input);
				// }
				else if (splited_line[0] == "JOIN")
				{
					// char join_message[256];
					// snprintf(join_message, sizeof(join_message), "JOIN tty\r\n");

					// char str[] = "JOIN #chain\r\n";
					// send(fd, str , strlen(str) , 0);
					char str[] = "JOIN tty\r\n";
					send(fd, str, strlen(str), 0);
					char str_[] = ":abc JOIN #tyy\r\n";
					send(fd, str_ , strlen(str_) , 0);
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
