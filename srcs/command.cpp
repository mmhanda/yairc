/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:11:23 by archid            #+#    #+#             */
/*   Updated: 2023/03/24 04:54:53 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
#include "server.hpp"
#include "user.hpp"
#include "parser.hpp"

void authenticate(std::string &msg, const int fd)
{

        char	*str;
        char	*str1;

        str = NULL;
        str1 = NULL;

		std::vector<std::string> splited_line;
		std::string back_up_msg;
		back_up_msg = msg;
		// std::cout << "before msg = " << msg << std::endl << std::endl;
		if (!msg.empty())
		{
			msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
			msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
									// std::cerr <<	"msg :: " << msg  << "|||||||||";

			str = const_cast<char *>(msg.c_str());

			str = strtok(str, " ");
			if (str != NULL)
			{
				while (str != NULL)
				{
					splited_line.push_back(str);
					str = strtok(NULL, " ");
				}

				user *tmp = NULL;
				tmp = ircserv.get_user(fd);

				if (splited_line[0] == "PASS")
				{
					check_PASS(splited_line , tmp);
				}
				else if (splited_line[0] == "NICK")
				{
					check_NICK(splited_line, tmp);
				}
				else if (splited_line[0] == "USER")
				{
					check_USER(splited_line, tmp);
				}
            }
        }
//     user *tmp = NULL;

//     tmp = map_users.at(fd);
//     if (msg.find("NICK ") != std::string::npos && tmp->nickname().empty())
//     {
//         if (msg.length() > 6){
//             tmp->nickname(msg.substr(5));
//             std::cout << "nick name set\n";
//             return ;
//         }
//     }

//     if (msg.find("USER ") != std::string::npos && tmp->username().empty()) {
//         if (msg.length() > 6)
//         {
//             tmp->username(msg.substr(5));
//             std::cout << "user set\n";
//             return ;
//         }
//     }

//     if (msg.find("PASS ") != std::string::npos)
//     {
//         if (msg.length() > 6){
//             std::string tmp1 = msg.substr(5);
//             if (tmp1 == "123")
//             {
//                 return ;
//             }
//             std::cerr << "464 " << "PASS" << " :Password incorrect" << tmp1 <<"|"<< std::endl;
//     }
//     send(fd, "wrong arg\n", 10, 0);
// }
}
