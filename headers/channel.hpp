// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   channel.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/08 23:43:25 by archid            #+#    #+#             //
//   Updated: 2023/03/22 18:47:33 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <set>
#include <map>
#include <string>

enum channel_properties { chan_public, chan_invite, chan_private };

class channel {
	void first_greet(class user *user);

public:
	channel(std::string name, std::string topic = "");

	void activate(class user *user, bool is_active);
	void join(class user *user);
	void kick(class user *user);

	const std::string &name() const { return name_; }
	const std::string &topic() const { return topic_; }

private:
	std::string name_, topic_;
	std::set<class user *> active_users_, users_;
};

std::ostream &operator<<(std::ostream &oss, const class channel chan);

typedef std::map<std::string, class channel *> channel_map;
extern channel_map channels;
