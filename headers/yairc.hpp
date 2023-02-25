// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   yairc.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/24 23:53:44 by mhanda            #+#    #+#             //
//   Updated: 2023/02/25 04:56:03 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <sys/socket.h>
#include <sys/types.h>

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

namespace yairc {
template<typename T>

class command {
public:
	command();

	bool exec();
};

class channel;
typedef class channel *channel_ptr;

class client {
	friend class channel;

	std::string nickname_, username_;
	std::vector<channel_ptr> channels_;

public:
	client(const std::string &nickname, const std::string &username);
	client(const client &);

	bool send_msg(const channel &, const std::string &);
	bool send_dm(const client &, const std::string &);
	bool recv_dm(const client &, std::string &);
};

class channel {
public:
	channel();

	bool join(client &foo);
};

class server {
public:
	server();
	server(const server &);

	bool auth_client(const client &);
};
} // namespace yairc
