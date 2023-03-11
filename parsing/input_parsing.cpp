/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/11 09:46:26 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

int	parse_command(void)
{
	size_t	i;
	char	*str  =NULL;
	char	*str1 = NULL;
	size_t	x;
	size_t	h;

	/*
  1235 642 TEXT 0-=+ aKU
*/
	while (1)
	{
		std::vector<std::string> splited_line;
		std::string input;
		std::string back_up_input;
		std::getline(std::cin, input); // read a line
		back_up_input = input;
		// std::cout << "before input = " << input << std::endl << std::endl;
		if (!input.empty())
		{
			/*const_cast <new_type> (expression) why? strtok uses char
				* and input.c_str() return const char* */
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
				i = 0;
				while (i < splited_line.size())
				{
					std::cout << "splited_line [] = " << splited_line[i] << std::endl;
					i++;
				}
				if (splited_line[0] == "PASS")
				{
					check_PASS(splited_line);
				}
				else if (splited_line[0] == "NICK")
				{
					check_NICK(splited_line);
				}
				else if (splited_line[0] == "USER")
				{
					check_USER(splited_line);
				}
				else if (splited_line[0] == "OPER")
				{
					check_OPER(splited_line);
				}
				else if (splited_line[0] == "QUIT")
				{
					check_QUIT(str1, back_up_input);
				}
				/*    Command: JOIN Parameters: <channel>{,<channel>} [<key>{,<key>}]
					example JOIN #foo,#bar fubar,foobar
			*/
				if (splited_line[0] == "JOIN")
				{
					if (splited_line.size() <= 1)
					{
						std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
					}
					else
					{
						/*use a map of channel name and a password */
						std::map<std::string, std::string> channels_map;
						std::cout << "JOIN COMMAND " << std::endl;
						x = 0;
						std::vector<std::string> channels;
						std::vector<std::string> password;
						while (splited_line[1].find(",") <= splited_line[1].size())
						{
							channels.push_back((splited_line[1].substr(0,
																		splited_line[1].find(","))));
							splited_line[1].erase(0, splited_line[1].find(",")
									+ 1);
						}
						channels.push_back((splited_line[1].substr(0)));
						while (splited_line[2].find(",") <= splited_line[2].size())
						{
							password.push_back((splited_line[2].substr(0,
																		splited_line[2].find(","))));
							splited_line[2].erase(0, splited_line[2].find(",")
									+ 1);
						}
						password.push_back((splited_line[2].substr(0)));
						h = 0;
						while (h < channels.size())
						{
							channels_map.insert(std::pair<std::string,
															std::string>(channels[h],
																		password[h]));
							if (channels[h].empty())
							{
								return (0);
							}
							std::cout << "channels [" << h << "] =" << channels[h] << std::endl;
							h++;
						}
						h = 0;
						while (h < password.size())
						{
							std::cout << "password [" << h << "] =" << password[h] << std::endl;
							h++;
						}
						/*map */
						std::map<std::string, std::string>::iterator it;
						it = channels_map.begin();
						while (it != channels_map.end())
						{
							std::cout << it->first << "::" << it->second << std::endl;
							++it;
						}
					}
				}
				/*
					Command: PART
								Parameters: <channel>{,<channel>}
								example   PART #oz-ops,&group5
				*/
				if (splited_line[0] == "PART")
				{
					std::cout << "PART COMMAND" << std::endl;
					if (splited_line.size() <= 1 || splited_line.size() >= 3)
					/* why 3? to avoid : PART #oz-ops,
					&dsd   there is a space after ,*/
					{
						std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
					}
					else
					{
						std::vector<std::string> channels;
						while (splited_line[1].find(",") <= splited_line[1].size())
						{
							channels.push_back((splited_line[1].substr(0,
																		splited_line[1].find(","))));
							splited_line[1].erase(0, splited_line[1].find(",")
									+ 1);
						}
						channels.push_back((splited_line[1].substr(0)));
						h = 0;
						while (h < channels.size())
						{
							std::cout << "channels [" << h << "] =" << channels[h] << std::endl;
							h++;
						}
					}
				}
				if (splited_line[0] == "MODE")
				{
					std::cout << "MODE COMMAND" << std::endl;
				}
			}
		}
	}
}

				/*			Command: SERVER
   Parameters: <servername> <hopcount> <info>
*/
				// if (splited_line[0] == "SERVER")
				// {
				// 	std::cout << "SERVER command" << std::endl;
				// 	if (splited_line.size() != 1)
				// 		std::cerr << "SERVER  parameters error " << std::endl;
				// }