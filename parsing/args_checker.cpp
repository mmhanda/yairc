/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:23:40 by atabiti           #+#    #+#             */
//   Updated: 2023/03/22 22:35:59 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include <iostream>
#include <stdlib.h> //for atoi
std::string PASSWORD;

/*
		Command: PASS
	Parameters: <password> (RFC 1459)
	ERRORS : ERR_ALREADYREGISTRED  ERR_NEEDMOREPARAMS
*/
int	check_PASS(std::vector<std::string> const &splited_line , user *tmp)
{
				std::cout << splited_line[1] <<std::endl;
				std::cout << splited_line[1].size() <<std::endl;

	if(tmp->PASS_authenticated == true)
	{
		std::cerr << "462 " << splited_line[0] << " :ERR_ALREADYREGISTRED" << std::endl;
		return 0;
	}
	else
	{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	else
	{
		if (splited_line[1] != PASSWORD)
		{
			std::cerr << "464 " << splited_line[0] << " :Password incorrect "  << std::endl;
			return (0);
		}
		tmp->PASS_authenticated = true;
		if(	tmp->PASS_authenticated && 	tmp->NICK_authenticated && 	tmp->USER_authenticated)
		{
					std::cout << "\e[1m"<< "🅆 🄴 🄻 🄲 🄾 🄼 🄴   🅃 🄾     🅈 🄰 🄸 🅁 🄲    🅂 🄴 🅁 🅅 🄴 🅁 " << std::endl;

		}
	}
	}

	return (0);
}

void parse_args(int argc, char *argv[], int &num_port, std::string &passwd) {
	if (argc != 3 || std::strlen(argv[1]) == 0 || std::strlen(argv[2]) == 0) {
		std::cerr << "run as " << argv[0] << " <PORT> <PASSWD>\n";
		exit(EXIT_FAILURE);
	}

	for (const char *port = argv[1]; *port != '\0'; ++port) {
		if (!std::isdigit(*port) || port - argv[1] > NUM_DIGITS) {
			std::cerr << argv[1] << " is not correct\n";
			exit(EXIT_FAILURE);
		}
	}

	int tmp = std::atoi(argv[1]);
	if (tmp < 1026 || tmp > (int)SHRT_MAX) {
		std::cerr << argv[1] << " is invalid\n";
		exit(EXIT_FAILURE);
	}
	num_port = tmp;

	for (const char *passwd = argv[2]; *passwd != '\0'; ++passwd) {
		if (!std::isprint(*passwd) || passwd - argv[2] > PASSWD_SIZE) {
			std::cerr << argv[2] << " is invalid\n";
			exit(EXIT_FAILURE);
		}
	}
	passwd = argv[2];
}
