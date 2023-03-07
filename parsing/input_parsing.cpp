/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:22:56 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/07 09:24:35 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	Parameters: <password> (RFC 1459)
*/
		if (splited_line[0] == "PASS")
		{
			std::cout << "PASS Command" << std::endl;
			if (splited_line.size() != 2)
			{
				std::cerr << "PASS Not enough parameters. \t 		Parameters: <password>" << std::endl;
			}
		}
/*
		        Command: NICK
	NICK <nickname> [<hopcount>] (RFC 1459)
	NICK <nickname> (RFC 2812)

*/

if(splited_line[0]  == "NICK")
{
			std::cout << "NICK Command" << std::endl;
			if (splited_line.size() != 2)
			{
				std::cerr << "NICK Not enough parameters. \t 	  Parameters: <nickname>" << std::endl;
			}
}


/*
	          	Command: USER 
	USER <username> <hostname> <servername> <realname> (RFC 1459)
	USER <user> <mode> <unused> <realname> (RFC 2812)
*/
		if (splited_line[0] == "USER")
		{
			std::cout << "PASS USER" << std::endl;
			if (splited_line.size() > 5 || splited_line.size() < 5)
			{
				std::cerr << "USER Not enough parameters. \t Parameters: <username> <hostname> <servername> <realname>" << std::endl;
			}
			std::cout << "USER is found" << std::endl;
		}

/*		  Command: SERVER
   Parameters: <servername> <hopcount> <info> 
*/

		if(splited_line[0] == "SERVER")
		{
			
				std::cout << "SERVER command"  << std::endl;
			if (splited_line.size() != 1)
				std::cerr << "SERVER  parameters error " << std::endl;
			
		}
		if(splited_line[0] == "OPER")
		{
			if(splited_line.size() != 2)
			{

			}
		}

	}
}