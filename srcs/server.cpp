/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             */
//   Updated: 2023/03/21 03:06:56 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "server.hpp"

struct sockaddr *server::setup_address(const short port) {
	static struct sockaddr_in addr;
	bzero(addr.sin_zero, sizeof(addr.sin_zero)); // set padding

	addr.sin_family = AF_INET;					 // address family
	addr.sin_port = htons(port);				 // address port
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

std::vector<std::string> server::recieve_data(pollfd_iter client) {
	std::vector<std::string> message;
	while (true) {
		int8_t tmp[BUFF_SIZE];
		ssize_t n_bytes = recv(client->fd, tmp, sizeof(tmp), 0);
		if (n_bytes > 0) {
			std::cerr << "recieved from client " << client->fd << "\n";
			message.push_back(std::string(tmp, tmp + n_bytes));
		} else {
			if (n_bytes == 0) {
				std::cerr << "client " << client->fd << " has left\n";
				close(client->fd);
				clients_.erase(client);
			} else if (errno != EWOULDBLOCK) {
				terminate_and_throw();
			}
			break;
		}
	}
	return message;
}

void server::run() {
	while (true) {
		int status;
		// std::cerr << "start poll\n";
		if ((status = poll(clients_.data(), clients_.size(), TIMEOUT * 1000)) < 0) {
			terminate_and_throw();
		} else if (status == 0) {
			// std::cerr << "timeout\n";
			continue;
		}

		std::cerr << "fd cheking\n";
		for (unsigned i = 0; i < clients_.size(); ++i) {
			if (clients_[i].revents & POLLIN) {
				if (clients_[i].fd == sock_fd_) {
					socklen_t sock_len = sizeof(struct sockaddr);
					int client_fd;

					while ((client_fd = accept(sock_fd_, addr_, &sock_len)) >= 0) {
						std::cerr << "server accept adding new client " << client_fd << '\n';
						clients_.push_back(client_pollfd(client_fd));
					}

					if (client_fd < 0 && errno != EWOULDBLOCK) {
						terminate_and_throw();
					}

				} else {
					std::cout << "recieve data \n";
					std::vector<std::string> data = recieve_data(clients_.begin() + i);
					for (unsigned j = 0; j < data.size(); ++j)
						std::cout << "`" << data[j] << "'\n";
				}
			}
		}
	}
}
