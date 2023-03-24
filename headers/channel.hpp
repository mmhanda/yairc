/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:43:25 by archid            #+#    #+#             */
/*   Updated: 2023/03/24 21:49:49 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "server.hpp"

enum channel_properties { chan_public, chan_invite, chan_private };

class channel {
	public:
		channel(std::string name, std::string passwd = "", std::string topic = "");
		void insert_users(user *user);
		std::string passwrd(void);
		void broadcast(std::string msg, user *sender);

		const std::string &name() const { return name_; }
		const std::string &topic() const { return topic_; }
		bool	check_if_user_in();

	private:
		std::vector<int> users_fd;
		std::string name_, topic_, passwd;
};

void	send_msg(std::string, user *user);

std::ostream &operator<<(std::ostream &oss, const class channel chan);
typedef std::map<std::string, class channel *> channel_map;
extern channel_map channels;
