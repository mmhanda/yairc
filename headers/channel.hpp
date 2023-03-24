/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:43:25 by archid            #+#    #+#             */
/*   Updated: 2023/03/24 03:40:14 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <set>
#include <map>
#include <string>
#include <iostream>

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

		static void update();

	private:
		std::string name_, topic_;
		std::set<class user *> active_users_, users_;
};

std::ostream &operator<<(std::ostream &oss, const channel chan);

typedef std::map<std::string, channel *> channel_map;
extern channel_map channels;
