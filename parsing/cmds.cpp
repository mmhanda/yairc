/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:17:29 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/11 09:46:15 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

/*
		Command: PASS
	Parameters: <password> (RFC 1459)
	ERRORS : ERR_ALREADYREGISTRED  ERR_NEEDMOREPARAMS
*/
int	check_PASS(std::vector<std::string> const &splited_line)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	return (0);
}
/*
					Command: NICK
	NICK <nickname> [<hopcount>] (RFC 1459)
	NICK <nickname> (RFC 2812)
	ERRORS : ERR_NONICKNAMEGIVEN   ERR_ERRONEUSNICKNAME   ERR_NICKNAMEINUSE        ERR_NICKCOLLISION
*/
int	check_NICK(std::vector<std::string> const &splited_line)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "431 " << splited_line[0] << " :No nickname given" << std::endl;
	}
	return (0);
}
/*
						Command: USER
	USER <username> <hostname> <servername> <realname> (RFC 1459)
	USER <user> <mode> <unused> <realname> (RFC 2812)
*/
int	check_USER(std::vector<std::string> const &splited_line)
{
	std::cout << "PASS USER" << std::endl;
	if (splited_line.size() != 5)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	std::cout << "USER is found" << std::endl;
	return (0);
}

/*
				Command: OPER   Parameters: <user> <password>
    OPER message is used by a normal user to obtain operator privileges.
    The combination of <user> and <password> are required to gain
    Operator privileges.
*/
int	check_OPER(std::vector<std::string> const &splited_line)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	return (0);
}

/*
			Command: QUIT
				Parameters: [<Quit message>]
*/
int	check_QUIT(char *str1, std::string const &back_up_input)
{
	str1 = const_cast<char *>(back_up_input.c_str());
	str1 = strtok(str1, ":");
	str1 = strtok(NULL, ":");
	if (str1 != NULL)
	{
		/*  If a "Quit Message" is given,
			this will be sent instead of the default message, the nickname. */
		std::cerr << "ERROR :Closing link: [" << str1 << "]" << std::endl;
		// str1 is the full message  without : ERROR :Closing link: (asd@localhost) [Gone to have lunch]
	}
	if (str1 == NULL)
	{
		std::cerr << "ERROR :Closing link: [Client exited]" << std::endl;
		// ERROR :Closing link: (atabiti@localhost) [Client exited]
	}
	return (0);
}