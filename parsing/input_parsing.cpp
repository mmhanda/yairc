/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
//   Updated: 2023/03/14 01:51:07 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "../headers/server.hpp"
#include "../headers/client.hpp"


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
	 			client *tmp = NULL;
				tmp = map_clients.at(fd);

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
