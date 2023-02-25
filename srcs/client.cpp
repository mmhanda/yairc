// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   client.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 01:13:18 by archid            #+#    #+#             //
//   Updated: 2023/02/25 04:54:25 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "yairc.hpp"

namespace yairc {
client::client(const std::string &nickname, const std::string &username)
	: nickname_(nickname), username_(username) {}

client::client(const client &) {
	assert(false && "Should not copy client");
	throw std::runtime_error("Should not copy client");
}
}
