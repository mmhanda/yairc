/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 04:55:12 by archid            #+#    #+#             */
/*   Updated: 2023/03/24 08:13:20 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include <sstream>

channel::channel(std::string name, std::string topic)
	: name_(name), topic_(topic) {}


std::ostream &operator<<(std::ostream &oss, const channel chan) {
	return oss << "#" << chan.name() << " [" << chan.topic() << "]";
}

channel_map channels;
