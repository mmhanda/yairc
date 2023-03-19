// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             //
//   Updated: 2023/03/19 22:25:31 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <assert.h>
#include <errno.h>

#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>

#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

#include "client.hpp"

#define str_error() strerror(errno)

#define NUM_CONNECTIONS 16
#define BUFF_SIZE 256
#define TIMEOUT 1	// in seconds
#define PORT 8881

class server {
	typedef std::vector<struct pollfd>::iterator pollfd_iter;

	struct sockaddr *init_socket_address(const char *host, int port);
	int set_socket_options(int fd);

	void start();
	void terminate();
	void terminate_and_throw();
	void server_banner(int client_fd);

	std::string recieve_data(pollfd_iter client);

public:
	server(int port, const char *host = NULL)
		: addr_(init_socket_address(host, port)) {
		start();
	}

	void run();

private:
	struct sockaddr *addr_;
	int sock_fd_;

	std::vector<struct pollfd> clients_;
};

extern short num_port;
extern char *passwd;

void parse_args(int argc, const char *argv[]);
