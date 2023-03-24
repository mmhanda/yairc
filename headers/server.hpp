/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             */
<<<<<<< Updated upstream
//   Updated: 2023/03/23 20:44:05 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

// #pragma once
=======
/*   Updated: 2023/03/18 05:51:00 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
>>>>>>> Stashed changes

#include <assert.h>
#include <errno.h>

#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include <string>
#include <iostream>
#include <utility>
#include <stdexcept>

#include <algorithm>
#include <vector>
#include <map>

#include "user.hpp"
#include "channel.hpp"

#define str_error() strerror(errno)

#define NUM_CONNECTIONS 16
#define BUFF_SIZE 256
#define TIMEOUT 1								// seconds
#define PORT 8881

class server {
private:
  typedef std::vector<struct pollfd> pollfd_vector;
	typedef std::map<int, std::string> message_map;
	typedef std::map<int, class user *> user_map;

	message_map map_msgs_;
	user_map map_users_;
  pollfd_vector clients_;

	int sock_fd_;
	struct sockaddr *addr_;
	short port_;
	std::string passwd_;

	struct sockaddr *setup_address(const short port);
  void terminate_and_throw();
  ssize_t recieve_message(pollfd_vector::iterator client);
  void accept_clients();

public:
  server();
	~server();
  server(int port, std::string passwd);

	user *get_user(int client_fd) const;

	void message(int client_fd, const std::string &msg, int flags = 0);
  void mode(user *user, channel *chan, user_roles role);
  void mode(channel *chan, channel_properties prop);

  void terminate();
  void run();
};

void authenticate(const std::string &msg, const int fd);

extern const char *msg_delim;

<<<<<<< Updated upstream
extern server ircserv;
=======
void parse_args(int argc, const char *argv[]);
>>>>>>> Stashed changes
