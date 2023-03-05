/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:48:54 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/05 10:03:18 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

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
	while (1)
	{
		std::string input;
		std::getline(std::cin, input);
		std::string::iterator iter = input.begin();
		iter = std::remove_if(input.begin(), input.end(), isspace);
		input.erase(iter, input.end());
		std::cout << "input = " << input << std::endl;

/*
				Command: USER  
		Parameters: <username> <hostname> <servername> <realname>
*/
		if(input.rfind("USER", 0) < input.size())
		{
			std::cout <<"USER is found" << std::endl;
		}

	}
}

int	main(int ac, char **av)
{
	if (checker(ac, av) == 0)
		return (0);
	parse_coommand();
	//enter here : start exec
	return (0);
}
