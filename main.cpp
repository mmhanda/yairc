/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:48:54 by mhanda            #+#    #+#             */
//   Updated: 2023/03/06 17:24:27 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "command.hpp"

namespace yairc {
  std::vector<command> cmds;

  static void initialise_commands() {
	{
	  std::vector<std::string> user_args;
	  user_args.push_back("username");
	  user_args.push_back("hostname");
	  user_args.push_back("servername");
	  user_args.push_back("realname");
	  cmds.push_back(command("user", user_args));
	}
	{
	  std::vector<std::string> user_args;
	  user_args.push_back("username");
	  user_args.push_back("hostname");
	  user_args.push_back("servername");
	  user_args.push_back("realname");
	}
  }


}

int	checker(int ac, char **av)
{
	size_t	i;
	int		port;

	if (ac != 3)
	{
		std::cerr << "ERROR: Your executable should be run as follows: \t./ircserv <port> <password>" << std::endl;
		return (0);
	}
	else
	{
		std::string port_checking(av[1]);
		std::string password_checking(av[2]);
		i = 0;
		while (i < port_checking.size())
		{
			if (!(std::isdigit(port_checking[i])))
			{
				std::cerr << "ERROR: <port> must be numeric" << std::endl;
				return (0);
			}
			// std::cout << port_checking[i] << std::endl;
			i++;
		}
		port = std::atoi(av[1]);
		// std::cout << " port  = " << port << std::endl;
		if (port < 0 || port > 65353)
		{
			std::cerr << "ERROR: <port> must be between 0  and 65353" << std::endl;
			return (0);
		}
		std::string::iterator it = password_checking.begin();
		it = std::remove_if(password_checking.begin(), password_checking.end(),
				isspace);
		// std::cout << "it = "<< *it<< std::endl;
		// std::cout << "password   = " << password_checking << std::endl;
		password_checking.erase(it, password_checking.end());
		// std::cout << "it = "<< *it<< std::endl;
		// std::cout << "password   = " << password_checking << std::endl;
		if (password_checking.empty()
			|| password_checking.find_first_of(" ") < password_checking.size())
		{
			std::cerr << "ERROR:<password> sould not be empty" << std::endl;
			return (0);
		}
	}
	return (1);
}

int	parse_coommand(void)
{
	size_t	position;
	size_t	i;

	while (1)
	{
		std::vector<std::string> splited_line;
		std::string input;
		std::getline(std::cin, input); // read a line
		position = 0;
		// std::cout << "input = " << input << std::endl;
		while ((position = input.find(" ")) < input.size())
		{
			// std::cout << "position = " << position << std::endl;
			splited_line.push_back(input.substr(0, position));
			input.erase(0, position + 1);
			// std::cout << "input = " << input << std::endl;
			// std::cout << "splited_line = " << splited_line[0] << std::endl;
		}
		splited_line.push_back(input.substr(0, position));
		i = 0;
		while (i < splited_line.size())
		{
			// std::cout << "splited_line [] = " << splited_line[i] << std::endl;
			i++;
		}
		/*
 		Command: PASS
		Parameters: <password>
*/
		if (splited_line[0] == "/PASS")
		{
			std::cout << "PASS Command" << std::endl;
			if (splited_line.size() != 2)
			{
				std::cerr << "PASS Not enough parameters. \t 		Parameters: <password>" << std::endl;
			}
		}
		/*
		Command: USER
		Parameters: <username> <hostname> <servername> <realname>
*/
		if (splited_line[0] == "/USER" || splited_line[0] == "/user")
		{
			std::cout << "PASS USER" << std::endl;
			if (splited_line.size() > 5 || splited_line.size() < 5)
			{
				std::cerr << "USER Not enough parameters. \t Parameters: <username> <hostname> <servername> <realname>" << std::endl;
			}
			std::cout << "USER is found" << std::endl;
		}
	}
}

int	main(int ac, char **av)
{
  yairc::initialise_commands();
	if (checker(ac, av) == 0)
		return (0);
	parse_coommand();
	//enter here : start exec
	return (0);
}
