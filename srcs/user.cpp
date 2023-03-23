/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 01:13:18 by archid            #+#    #+#             */
//   Updated: 2023/03/23 20:14:36 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"
#include "channel.hpp"

user::user(int client_fd) : PASS_authenticated(false),
														NICK_authenticated(false),
														USER_authenticated(false) {
	client_fd_ = client_fd;
}

user::~user() {
	for (user::role_map::iterator role = roles_.begin(); role != roles_.end();) {
		channel *chan = role->first;
		role++;
		chan->kick(this);
	}
}

const std::string &user::nickname() const { return nickname_; }

void user::nickname(std::string nickname) { nickname_ = nickname; }

const std::string &user::username() const { return username_; }

void user::username(std::string username) { username_ = username; }

bool user::join_or_create_channel(const std::string &chan_name) {
	channel *&chan = channels[chan_name];
	if (chan != nullptr) {
		chan = new channel(chan_name);
		channels.insert(std::make_pair<std::string, channel *>(chan_name, chan));
		std::cerr << *this << " created " << *chan << "\n";
		chan->join(this);
		roles_[chan] = role_operator;
		return true;
	} else {
		chan->join(this);
		roles_[chan] = role_user;
		return false;
	}
}

bool user::private_message(const user *user, const std::string &msg) {
	// serve.message(user->)
}

void user::part_channel(class channel *chan) {
	roles_.erase(chan);
}

std::ostream &operator<<(std::ostream &oss, const class user u) {
	return oss << u.username() << " (" << u.nickname() << ")";
}
