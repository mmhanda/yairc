// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   client.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 03:21:35 by archid            #+#    #+#             //
//   Updated: 2023/03/05 04:44:56 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <string>

namespace yairc {
  class client {
    friend class channel;

	int client_fd_;
    std::string nickname_, username_;
	//std::vector<channel_ptr> channels_;

  public:
	typedef client *client_ptr;

    client(int client_fd);

    client(const client &) {
	  assert(false && "Should not copy client");
	  throw std::runtime_error("Should not copy client");
	}

	const std::string &nickname() const { return nickname_; }
	void nickname(std::string nickname) {
	  nickname_ = nickname;
	}

	const std::string &username() const { return username_; }
	void username(std::string username) {
	  username_ = username;
	}

  };

  typedef client::client_ptr client_ptr;
} // namespace yairc
