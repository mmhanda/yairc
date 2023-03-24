/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:17:29 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/24 21:18:48 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*
					Command: NICK
	NICK <nickname> [<hopcount>] (RFC 1459)
	NICK <nickname> (RFC 2812)
	ERRORS : ERR_NONICKNAMEGIVEN   ERR_ERRONEUSNICKNAME   ERR_NICKNAMEINUSE        ERR_NICKCOLLISION
	 NICK message is used to give user a nickname or change the previous one.
*/
int check_NICK(std::vector<std::string> const &splited_line, user *tmp)
{
	if (splited_line.size() != 2)
		return (0);
		tmp->nickname(splited_line[1]);
		tmp->NICK_authenticated = true;
	return (1);
}

/*
						Command: USER
	USER <username> <hostname> <servername> <realname> (RFC 1459)
	USER <user> <mode> <unused> <realname> (RFC 2812)
*/
int check_USER(std::vector<std::string> const &splited_line, user *tmp)
{
	if (splited_line.size() != 5)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
		return 0;
	}
	tmp->username(splited_line[1]);
	tmp->USER_authenticated = true;
	if (tmp->PASS_authenticated && tmp->NICK_authenticated && tmp->USER_authenticated)
	{
		std::cout << "\e[1m"
				  << "🅆 🄴 🄻 🄲 🄾 🄼 🄴   🅃 🄾     🅈 🄰 🄸 🅁 🄲    🅂 🄴 🅁 🅅 🄴 🅁 " << std::endl;
	}
	return (1);
}

/*
				Command: OPER   Parameters: <user> <password>
	OPER message is used by a normal user to obtain operator privileges.
	The combination of <user> and <password> are required to gain
	Operator privileges.
*/
int check_OPER(std::vector<std::string> const &splited_line)
{
	if (splited_line.size() != 2)
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	return (0);
}

/*
			Command: QUIT:
				Parameters: [<Quit message>]
*/
int check_QUIT(char *str1, std::string const &back_up_input)
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
		std::cerr << "ERROR :Closing link: [User exited]" << std::endl;
		// ERROR :Closing link: (atabiti@localhost) [User exited]
	}
	return (0);
}
/*    Command: JOIN Parameters: <channel>{,<channel>} [<key>{,<key>}]
					example JOIN #foo,#bar fubar,foobar
*/

int check_JOIN(std::vector<std::string> &splited_line, user *user)
{
	size_t h;

	h = 0;
	if (splited_line.size() <= 1)
		send(user->client_fd(), "461 JOIN :Not enough parameters\n", 32, 0);
	else
	{
		/*use a map of channel name and a password */
		std::map<std::string, std::string> channels_map;
		std::cout << "JOIN COMMAND " << std::endl;
		std::vector<std::string> channels;
		std::vector<std::string> password;
		while (splited_line[1].find(",") <= splited_line[1].size())
		{
			channels.push_back((splited_line[1].substr(0,
													   splited_line[1].find(","))));
			splited_line[1].erase(0, splited_line[1].find(",") + 1);
		}
		channels.push_back((splited_line[1].substr(0)));
		while (splited_line[2].find(",") <= splited_line[2].size())
		{
			password.push_back((splited_line[2].substr(0,
													   splited_line[2].find(","))));
			splited_line[2].erase(0, splited_line[2].find(",") + 1);
		}
		password.push_back((splited_line[2].substr(0)));
		h = 0;
		while (h < channels.size())
		{
			channels_map.insert(std::pair<std::string,
										  std::string>(channels[h],
													   password[h]));
			if (channels[h].empty())
			{
				return (0);
			}
			std::cout << "channels [" << h << "] =" << channels[h] << std::endl;
			h++;
		}
		h = 0;
		while (h < password.size())
		{
			std::cout << "password [" << h << "] =" << password[h] << std::endl;
			h++;
		}
		/*map */
		std::map<std::string, std::string>::iterator it;
		it = channels_map.begin();
		// while (it != channels_map.end())
		// {
			if (map_channels.find(it->first) != map_channels.end()) {
				if (map_channels.find(it->second) != map_channels.end()) {
                    channel *tmp = map_channels.at(splited_line[1]);
                    //     std::cout << "user 1 \n";
                    // if (tmp->check_if_user_in()){
                    //     std::cout << "user 2 \n";
                    //     return ;}
                    // else {
                    tmp->insert_users(user);
                    std::string sen = "you have joined channel \n" + splited_line[1];
                    send(user->client_fd(), sen.c_str(), sen.size(), 0); }
                }
                else {
                    channel *tmp = new channel(splited_line[1]);
                        map_channels.insert(std::pair<std::string, channel *>\
                                (splited_line[1], tmp));
                    tmp->insert_users(user);
                }
			// std::cout << it->first << "::" << it->second << std::endl;
			++it;
		// }
	}
	return (0);
}

/*
					Command: PART
	Parameters: <channel>{,<channel>}
	example   PART #oz-ops,&group5
*/
int check_PART(std::vector<std::string> &splited_line)
{
	size_t h;

	h = 0;
	std::cout << "PART COMMAND" << std::endl;
	if (splited_line.size() <= 1 || splited_line.size() >= 3)
	/* why 3? to avoid : PART #oz-ops,
					&dsd   there is a space after ,*/
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
	}
	else
	{
		std::vector<std::string> channels;
		while (splited_line[1].find(",") <= splited_line[1].size())
		{
			channels.push_back((splited_line[1].substr(0,
													   splited_line[1].find(","))));
			splited_line[1].erase(0, splited_line[1].find(",") + 1);
		}
		channels.push_back((splited_line[1].substr(0)));
		while (h < channels.size())
		{
			std::cout << "channels [" << h << "] =" << channels[h] << std::endl;
			h++;
		}
	}
	return (0);
}

/*
		Command: PRIVMSG
		Parameters: <receiver>{,<receiver>} <text to be sent>
*/

int check_PRIVMSG(std::vector<std::string> &splited_line, std::string &back_up)
{
	size_t x;
	char *str1;

	x = 0;
	if (splited_line.size() > 2)
	{
		std::vector<std::string> message_receivers; /*send message to this*/
		while (splited_line[1].find(",") <= splited_line[1].size())
		{
			message_receivers.push_back((splited_line[1].substr(0,
																splited_line[1].find(","))));
			splited_line[1].erase(0, splited_line[1].find(",") + 1);
		}
		message_receivers.push_back((splited_line[1].substr(0)));
		x = 0;
		while (x < message_receivers.size())
		{
			std::cout << "message_receivers = " << message_receivers[x] << std::endl;
			if (message_receivers[x].empty())
			{
				std::cerr << splited_line[0] << " :Wrong input" << std::endl;
				return (0);
			}
			x++;
		}
		str1 = const_cast<char *>(back_up.c_str());
		str1 = strtok(str1, ":");
		str1 = strtok(NULL, ":");
		if (str1 == NULL || strcmp(str1, "") == 0) // no ":"" is provided //PRIVMSG ff fff :
		{
			std::cerr << splited_line[0] << " :Wrong input" << std::endl;
			return (0);
		}
		std::cout << "str1: " << str1 << "||" << std::endl; // message
	}
	else
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
		return (0);
	}
	return (0);
}

/*
	  Command: NOTICE
   Parameters: <nickname> <text>
*/

int check_NOTICE(std::vector<std::string> &splited_line,
				 std::string &back_up_input)
{
	if (splited_line.size() >= 3)
	{
		std::string message;
		std::string nickname;
		nickname = splited_line[1];
		back_up_input.erase(back_up_input.find("NOTICE"),
							splited_line[0].length());
		back_up_input.erase(back_up_input.find(splited_line[1]),
							splited_line[1].length());
		std::cout << "nickname " << nickname << std::endl
				  << std::endl
				  << std::endl
				  << std::endl;								   // nickname
		std::cout << "MESSAGE:" << back_up_input << std::endl; // ,message
															   // exit(1);
	}
	else
	{
		std::cerr << "461 " << splited_line[0] << " :Not enough parameters" << std::endl;
		return (0);
	}
	return (0);
}
