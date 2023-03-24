/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:43:25 by archid            #+#    #+#             */
/*   Updated: 2023/03/24 08:13:41 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <set>
#include <map>
#include <string>

enum channel_properties { chan_public, chan_invite, chan_private };

class channel {
	public:
		channel(std::string name, std::string topic = "");

		const std::string &name() const { return name_; }
		const std::string &topic() const { return topic_; }

	private:
		std::string name_, topic_;
};

std::ostream &operator<<(std::ostream &oss, const class channel chan);

typedef std::map<std::string, class channel *> channel_map;
extern channel_map channels;
