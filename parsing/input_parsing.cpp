/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/07 12:09:27 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstring> 
int	parse_coommand(void)
{
	size_t	position;
	size_t	i;
/*

  1235 642 TEXT 0-=+ aKU
*/
	while (1)
	{
		std::vector<std::string> splited_line;
		std::string input;
		std::getline(std::cin, input); // read a line
		position = 0;
		std::cout << "input = " << input << std::endl << std::endl;
        if(!input.empty())
        {
            position = input.find(" ");
            int start = 0 ;
            int end = 0 ;

            int x = 0;
                char* str = const_cast<char*>(input.c_str());

           str =  strtok(str , " ");
           while (str != NULL)
           {
                  std:: cout <<  "str|"<<str << std::endl;
                  splited_line.push_back(str);
                str =  strtok(NULL , " ");
           }
           
		i = 0;
		while (i < splited_line.size())
		{
			std::cout << "splited_line [] = " << splited_line[i] << std::endl;
			i++;
            
		}
/*
 		Command: PASS 
	Parameters: <password> (RFC 1459)
    ERRORS : ERR_ALREADYREGISTRED  ERR_NEEDMOREPARAMS
*/
// 		if (splited_line[0] == "PASS")
// 		{
// 			std::cout << "PASS Command" << std::endl;
// 			if (splited_line.size() != 2)
// 			{
// 				std::cerr  << "461 " << splited_line[0] <<" :Not enough parameters" << std::endl;
// 			}
// 		}
// /*
// 		        Command: NICK
// 	NICK <nickname> [<hopcount>] (RFC 1459)
// 	NICK <nickname> (RFC 2812)
//     ERRORS : ERR_NONICKNAMEGIVEN   ERR_ERRONEUSNICKNAME   ERR_NICKNAMEINUSE        ERR_NICKCOLLISION
// */

// if(splited_line[0]  == "NICK")
// {
// 			std::cout << "NICK Command" << std::endl;
// 			if (splited_line.size() != 2)
// 			{
// 				std::cerr  << "431 " << splited_line[0] <<" :No nickname given" << std::endl;
// 			}
// }


// /*
// 	          	Command: USER 
// 	USER <username> <hostname> <servername> <realname> (RFC 1459)
// 	USER <user> <mode> <unused> <realname> (RFC 2812)
// */
// 		if (splited_line[0] == "USER")
// 		{
// 			std::cout << "PASS USER" << std::endl;
// 			if (splited_line.size() > 5 || splited_line.size() < 5)
// 			{
// 				std::cerr << "USER Not enough parameters. \t Parameters: <username> <hostname> <servername> <realname>" << std::endl;
// 			}
// 			std::cout << "USER is found" << std::endl;
// 		}

// /*		  Command: SERVER
//    Parameters: <servername> <hopcount> <info> 
// */

// 		if(splited_line[0] == "SERVER")
// 		{
			
// 				std::cout << "SERVER command"  << std::endl;
// 			if (splited_line.size() != 1)
// 				std::cerr << "SERVER  parameters error " << std::endl;
			
// 		}
// 		if(splited_line[0] == "OPER")
// 		{
// 			if(splited_line.size() != 2)
// 			{

// 			}
// 		}

	}
    }
}