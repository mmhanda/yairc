/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 04:55:12 by archid            #+#    #+#             */
/*   Updated: 2023/03/24 13:54:51 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include <sstream>

channel::channel(std::string name, std::string topic)
	: name_(name), topic_(topic) {}

void channel::insert_users(user *user) {
	// need to check priviliges first

	this->users_fd.push_back(user->client_fd());
}

void channel::broadcast(std::string msg, user *sender) {

	for (int user_fd : users_fd) {

		if (sender->client_fd() != user_fd)
			send(user_fd, msg.c_str(), msg.size(), 0);
			// std::cout << user_fd << std::endl;
	}
}

bool	channel::check_if_user_in(){

	auto it = std::find(users_fd.begin(), users_fd.end(), 3);
	if (it != users_fd.end())
		return (true);
	else
		return(false);
}

std::ostream &operator<<(std::ostream &oss, const channel chan) {
	return oss << "#" << chan.name() << " [" << chan.topic() << "]";
}

channel_map channels;
