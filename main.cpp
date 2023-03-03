/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:48:54 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/03 11:27:13 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//irc
#include <cstdlib>
#include <iostream>
#include <string>

int	main(int ac, char **av)
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
		i = 0;
		while (i < port_checking.size())
		{
			if (!(std::isdigit(port_checking[i])))
			{
				std::cerr << "ERROR: <port> must be numeric" << std::endl;
				return (0);
			}
			std::cout << port_checking[i] << std::endl;
			i++;
		}
		port = std::atoi(av[1]);
		std::cout << " port  = " << port << std::endl;
		if (port < 0 || port > 65353)
		{
			std::cerr << "ERROR: <port> must be between 0  and 65353" << std::endl;
			return (0);
		}
		//enter here : start exec
	}
    
	return (0);
}
