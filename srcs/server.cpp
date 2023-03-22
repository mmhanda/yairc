/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             */
/*   Updated: 2023/03/22 05:47:43 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "server.hpp"
#include "command.hpp"

struct sockaddr *server::setup_address(const short port) {
	static struct sockaddr_in addr;
	bzero(addr.sin_zero, sizeof(addr.sin_zero));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (addr.sin_addr.s_addr < 0)
		terminate_and_throw();

	return reinterpret_cast<struct sockaddr *>(&addr);
}

struct pollfd client_pollfd(int client_fd) {
	struct pollfd fd;
	fd.fd = client_fd;
	fd.events = POLLIN;
	fd.revents = 0;
	return fd;
}

void server::start() {
	if ((sock_fd_ = socket(PF_INET, SOCK_STREAM, 0)) < 0
			|| ((bind(sock_fd_, addr_, sizeof(struct sockaddr))) < 0))
		terminate_and_throw();

	int yes = 1;
	if (setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
		terminate_and_throw();
	if (fcntl(sock_fd_, F_SETFL, O_NONBLOCK) < 0)
		terminate_and_throw();

	clients_.push_back(client_pollfd(sock_fd_));

	if ((::listen(sock_fd_, NUM_CONNECTIONS)) < 0)
		terminate_and_throw();
}

void server::terminate() {
	for (unsigned i = 0; i < clients_.size(); ++i)
		close(clients_[i].fd);
	clients_.clear();
}

void server::terminate_and_throw() {
	terminate();
	throw std::runtime_error(str_error());
}

void server::server_banner(int client_fd) {
	char buff[] = "Welcome to YAIRC Server\n";
	string_data tmp(buff, sizeof(buff));
	ssize_t n_bytes = tmp.send(client_fd);
	if (n_bytes < 0)
		terminate_and_throw();
}

ssize_t server::recieve_message(pollfd_iter client) {
	std::int8_t buffer[BUFF_SIZE];
	ssize_t n_bytes = recv(client->fd, buffer, sizeof(buffer), 0);

	if (n_bytes > 0) {
		std::cerr << "recieved from " << n_bytes << " from client " << client->fd << "\n";
		map_msgs[client->fd].append(buffer, buffer + n_bytes);
	} else if (n_bytes == 0) {
		std::cerr << "client " << client->fd << " has left\n";
		// map_msgs.erase(clients_) // need to be ereased
		close(client->fd);
		clients_.erase(client);
	} else if (errno != EWOULDBLOCK) {
		std::cout << "catch\n" ;
		terminate_and_throw();
	}
	return n_bytes;
}

void server::accept_clients() {
	socklen_t sock_len = sizeof(struct sockaddr);
	int client_fd;

	while ((client_fd = ::accept(sock_fd_, addr_, &sock_len)) >= 0) {
		std::cerr << "new client joined number " << client_fd << '\n';
		send(client_fd, "Welcom to yairc server\n", 23, 0);
		clients_.push_back(client_pollfd(client_fd));
	}

	if (client_fd < 0 && errno != EWOULDBLOCK) {
		terminate_and_throw();
	}
}

void server::run() {
	while (true) {
		int status;
		if ((status = poll(clients_.data(), clients_.size(), TIMEOUT * 1000)) < 0) {
			terminate_and_throw();
		} else if (status == 0) {
			continue;
		}

		for (unsigned i = 0; i < clients_.size(); ++i) {
			if (clients_[i].revents & POLLIN) {
				if (clients_[i].fd == sock_fd_) {
					accept_clients();
				} else {
					if(!recieve_message(clients_.begin() + i))
						continue;

					const std::string &msg = map_msgs.at(clients_[i].fd);
					// if (msg.find(delimiter) != std::string::npos) {
						// if(authenthic())
					// std::cout << msg ;
					// 	command::pointer irc_cmd = parse_command(msg);
						
					// 	// if (irc_cmd->exec() < 0)
					// 	// 	terminate_and_throw();
					// }
				}
			}
		}
	}
}

const char *delimiter = "\n";
std::map<int, std::string> map_msgs;
