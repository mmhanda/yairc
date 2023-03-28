/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             */
/*   Updated: 2023/03/28 15:24:56 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <assert.h>
#include <errno.h>

#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>

# define   SEND_CHAN(nick_name, user_name, channel_name) ":" + nick_name + "!" + user_name + "@localhost JOIN " + channel_name + "\r\n"
# define   USERS_LIST(nick_name, channel_name)           ":localhost 353 " + nick_name + " = "  + channel_name + "\r\n" // problem was here segfault!
# define   END_LIST(nick_name, channel_name)             ":localhost 366 " + nick_name + " " + channel_name + " :End of /NAMES list.\r\n"
# define   PART(nick_name, nick_name1, channel_name)  ":" + nick_name + "!" + nick_name1 + "@localhost PART " + channel_name

#include "user.hpp"
#include "channel.hpp"
#include "parser.hpp"

#define str_error() strerror(errno)

#define NUM_CONNECTIONS 16
#define BUFF_SIZE 256
#define TIMEOUT 1
#define PORT 8881


#include "user.hpp"
#include "channel.hpp"

#define str_error() strerror(errno)

#define NUM_CONNECTIONS 16
#define BUFF_SIZE 256
#define TIMEOUT 1
#define PORT 8881

class server {
    private:
      typedef std::vector<pollfd>::iterator pollfd_iter;
      struct sockaddr *setup_address(const short port);
      struct sockaddr *addr_;

      int sock_fd_;
      std::vector<pollfd> clients_;
      std::string passwd_;

      void start();
      void terminate_and_throw();
      void server_banner(int client_fd);
      ssize_t recieve_message(pollfd_iter client);
      void accept_clients();

    public:
      server() {};
      
      // ~server() {
      //   std::cout << "des called" << std::endl;
      //   terminate(); };
      server(int port, std::string passwd);
      server &operator = (const server &copyfrom);

      void message(int client_fd, std::string msg = "", int flags = 0);

      void terminate();
      void run();
};

void authenticate(const std::string &msg, const int fd);

extern const char *msg_delim;
extern std::map<int, std::string> map_msgs;
extern std::map<int, class user *> map_users;
extern std::vector<std::string> server_user_names;
extern server ircserv;


void authenticate(const std::string &msg, const int fd);
bool join_or_create_channel(const std::string &chan_name);
bool private_message(const user *user, const std::string &msg);
void leave_channel(class channel *chan, class user *usr);

extern const char *msg_delim;
extern std::map<int, std::string> map_msgs;
extern std::map<int, class user *> map_users;
extern std::map<std::string, class channel *> map_channels;
extern std::vector<std::string> server_nick_names;
extern server ircserv;
