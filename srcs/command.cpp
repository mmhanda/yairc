/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:30:49 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/24 08:32:25 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "user.hpp"

void authenticate(const std::string &msg, const int fd)
{

    user *tmp = NULL;

    tmp = map_users.at(fd);
    if (msg.find("NICK ") != std::string::npos && tmp->nickname().empty())
    {
        if (msg.length() > 6){
            tmp->nickname(msg.substr(5));
            std::cout << "nick name set\n";
            return ;
        }
    }

    if (msg.find("USER ") != std::string::npos && tmp->username().empty()) {
        if (msg.length() > 6)
        {
            tmp->username(msg.substr(5));
            std::cout << "user set\n";
            return ;
        }
    }

    if (msg.find("PASS ") != std::string::npos)
    {
        if (msg.length() > 6){
            std::string tmp1 = msg.substr(5);
            if (tmp1 == "123")
            {
                return ;
            }
            std::cerr << "464 " << "PASS" << " :Password incorrect" << tmp1 <<"|"<< std::endl;
    }
    send(fd, "wrong arg\n", 10, 0);
}
}
