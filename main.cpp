/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:48:54 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/03 23:20:24 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

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
        // password_checking.erase(std::remove_if(password_checking.begin(), password_checking.end(), ::isspace),   password_checking.end());
        std::string::iterator  it = password_checking.begin();
        it = std::remove_if(password_checking.begin(), password_checking.end(), isspace);
        std::cout << "it = "<< *it<< std::endl;
		std::cout << "password   = " << password_checking << std::endl;
        
        password_checking.erase(it,   password_checking.end());
        std::cout << "it = "<< *it<< std::endl;
		std::cout << "password   = " << password_checking << std::endl;
        if(password_checking.empty() || password_checking.find_first_of(" ") < password_checking.size())
        {
			std::cerr << "ERROR:<password> sould not be empty" << std::endl;
			return (0);
        }
		//enter here : start exec
	}
    
	return (0);
}
