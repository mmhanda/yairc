// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             //
//   Updated: 2023/03/05 05:40:13 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <assert.h>
#include <errno.h>

#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include <stdexcept>
#include <vector>

#include "client.hpp"

#define str_error() strerror(errno)
#define NUM_CONNECTIONS 1

namespace yairc {
  class server {
	// FIXME(0x0584): make exception more explicit
	void exception_handler() {
	  throw std::runtime_error(str_error());

	  // switch(errno) {
	  // case EAGAIN:			 // TODO(0x0584): list all possible errors
	  // 	throw std::runtime_error(str_error());
	  //}
	}

	struct sockaddr *setup_address(const char *host, int port) {
	  static struct sockaddr_in addr;
	  bzero(addr.sin_zero, sizeof(addr.sin_zero)); // set padding

	  addr.sin_family = AF_INET;				   // address family
	  addr.sin_port = htons(port);				   // address port
	  addr.sin_addr.s_addr = host				   // host address
		? inet_addr(host) : htonl(INADDR_ANY);

	  if (addr.sin_addr.s_addr < 0) {
		exception_handler();
	  }

	  return reinterpret_cast<struct sockaddr *>(&addr);
	}


  public:

    server(const char *host, int port);

    server(const server &) {
	  assert(false && "Should not copy server");
	  throw std::runtime_error("Should not copy server");
	}

	void server_banner(int client_fd) {
	  char buff[] = "Welcome to YAIRC Server\n";
	  ssize_t n_bytes = send(client_fd, reinterpret_cast<void *>(buff), sizeof(buff), 0);

	}

	void listen() {

	  if ((::listen(sock_fd_, num_connections_)) < 0) {
		exception_handler();
	  }


	  socklen_t sock_len = sizeof(struct sockaddr);
	  int client_fd;
	  if ((client_fd = accept(sock_fd_, addr_, &sock_len)) < 0) {
		exception_handler();
	  }

	  struct pollfd client;
	  client.fd = client_fd;
	  client.events = POLLIN;

	  clients_.push_back(client);
	}

	void recieve_data() {
	  for (poll_vector::iterator itr = clients_.begin(); itr != clients_.end(); ++itr) {
		if (itr->events & POLL_IN) {
		  recieve_data(itr->fd);
		}
	  }
	}



  private:
	typedef 	std::vector<struct pollfd> poll_vector;
	static int num_connections_;

	struct sockaddr *addr_;
	int sock_fd_;
poll_vector clients_;
  };
} // namespace yairc
