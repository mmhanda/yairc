// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   channel.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 04:55:12 by archid            #+#    #+#             //
//   Updated: 2023/03/23 20:20:26 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "server.hpp"

#include <sstream>

channel::channel(std::string name, std::string topic)
	: name_(name), topic_(topic) {}

void channel::first_greet(user *user) {
	std::ostringstream oss;
	oss << "You have just joined " <<  *this << '\n';
	ircserv.message(user->client_fd(), oss.str());
}

void channel::activate(user *user, bool is_active) {
	if (is_active) {
		active_users_.insert(user);
	} else {
		active_users_.erase(user);
	}
	std::cerr << *user << " is " << (is_active ? "in" : "")
						<< "active on " << *this << '\n';
}

void channel::join(user *user) {
	if (active_users_.insert(user).second) {
		if (users_.insert(user).second) {
			first_greet(user);
		}
		std::cerr << *user << " has joined " << *this << "\n";
	}
}

void channel::kick(user *user) {
	user->part_channel(this);
	active_users_.erase(user);
	users_.erase(user);
}

void channel::update() {
	for (channel_map::iterator chan = channels.begin(); chan != channels.end();) {
		channel *tmp = chan->second;
		chan++;
		if (tmp->users_.empty()) {
			delete tmp;
		}
	}
}

std::ostream &operator<<(std::ostream &oss, const channel chan) {
	return oss << "#" << chan.name() << " [" << chan.topic() << "]";
}

channel_map channels;
