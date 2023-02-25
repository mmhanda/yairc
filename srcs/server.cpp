// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             //
//   Updated: 2023/02/25 04:56:42 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "yairc.hpp"

namespace yairc {
server::server() {}

server::server(const server &) {
	assert(false && "Should not copy server");
	throw std::runtime_error("Should not copy server");
}
} // namespace yairc
