/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:13:18 by archid            #+#    #+#             */
/*   Updated: 2023/03/26 02:26:55 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"
#include "channel.hpp"
#include <iostream>

user::user(int client_fd) : PASS_authenticated(false),
				NICK_authenticated(false),
				USER_authenticated(false) {
	client_fd_ = client_fd;
}

const std::string &user::nickname() const { return nickname_; }

void user::nickname(std::string nickname) { nickname_ = nickname; }

const std::string &user::username() const { return username_; }

void user::username(std::string username) { username_ = username; }

void send_confirm_msg(user *user_){

	if (user_->NICK_authenticated && user_->PASS_authenticated
		&&user_->USER_authenticated && user_->PRINTER) {
		std::string sen = ":ircserv 001 " + user_->nickname() + ": Welcome to the ircserv network\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		user_->PRINTER = true;
	}
}
