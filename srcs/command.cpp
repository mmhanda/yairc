/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:30:49 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/24 14:18:06 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

bool    authenticate(std::string &msg , const int fd)
{
	char	*str;
	char	*str1;

	str = NULL;
	str1 = NULL;

    std::vector<std::string> splited_line;
    user *tmp = NULL;
    tmp = map_users.at(fd);

    if (tmp->NICK_authenticated && tmp->PASS_authenticated && tmp->USER_authenticated)
    {
        // std::string str = "462 " + tmp->username() + " :You may not reregister\n";
        // ::send(fd, str.c_str(), str.length(), 0);
        return (true);
    }

    if (!msg.empty())
    {
        msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
        msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());

        str = const_cast<char *>(msg.c_str());

        str = strtok(str, " ");
        if (str != NULL)
        {
            while (str != NULL)
            {
                splited_line.push_back(str);
                str = strtok(NULL, " ");
            }

            if (splited_line[0] == "PASS"){
                if (!check_PASS(splited_line , tmp)){
                    ::send(fd, "461 PASS :Not enough parameters\n", 32, 0);}}
            else if (splited_line[0] == "NICK"){
                if (!check_NICK(splited_line, tmp)){
                    ::send(fd, "431 NICK :No nickname given\n", 29, 0);}}
            else if (splited_line[0] == "USER"){
                if (!check_USER(splited_line, tmp)){
                    send(fd, "461 USER :Not enough parameters\n", 32, 0);}}
        }
    }
    return (false);
}

void    join_channel(std::string msg, user *user){
    
    char *str = NULL;
    
    std::vector<std::string> splited_line;

    msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
        msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());

    str = const_cast<char *>(msg.c_str());

    str = strtok(str, " ");
    if (str != NULL)
    {
        while (str != NULL)
        {
            splited_line.push_back(str);
            str = strtok(NULL, " ");
        }
        if (splited_line.size() != 2 && splited_line[0] != "JOIN"
            && splited_line[0] != "#JOIN" && splited_line[0] != "&JOIN"){
            send(user->client_fd(), "461 USER :Not enough parameters\n", 32, 0);}
        else if (splited_line[0] == "JOIN" || splited_line[0] == "#JOIN"
            || splited_line[0] == "&JOIN"){
                if (map_channels.count(splited_line[1]) && map_channels.size() == 1) {
                    channel *tmp = map_channels.at(splited_line[1]);
                    //     std::cout << "user 1 \n";
                    // if (tmp->check_if_user_in()){
                    //     std::cout << "user 2 \n";
                    //     return ;}
                    // else {
                    tmp->insert_users(user);
                    std::string sen = "you have joined channel \n" + splited_line[1];
                    send(user->client_fd(), sen.c_str(), sen.size(), 0);
                }
                else {
                    channel *tmp = new channel(splited_line[1]);
                    std::cout << "joined " << splited_line[1] << std::endl;
                        map_channels.insert(std::pair<std::string, channel *>\
                                (splited_line[1], tmp));
                    tmp->insert_users(user);
                }
            }
    }
}




