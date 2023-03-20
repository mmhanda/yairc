/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             */
/*   Updated: 2023/03/20 19:07:08 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "data.hpp"

#include <iostream>


int yes;

int server::set_socket_options(int fd){
	return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0 ||
		fcntl(fd, F_SETFL, O_NONBLOCK) < 0 ? -1 : 0;
}

struct sockaddr *server::init_socket_address(const short port) {
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

server::server(const short port) : addr_(init_socket_address(port)) {
	if ((this->sock_fd_ = socket(PF_INET, SOCK_STREAM, 0)) < 0 ||
		bind(this->sock_fd_, this->addr_, sizeof(struct sockaddr)) < 0 ||
		set_socket_options(this->sock_fd_) < 0)
		terminate_and_throw();

	this->clients_.push_back(client_pollfd(this->sock_fd_));
	if (listen(this->sock_fd_, NUM_CONNECTIONS) < 0)
		terminate_and_throw();
}

void server::terminate() {
	for (unsigned i = 0; i < this->clients_.size(); ++i)
		close(this->clients_[i].fd);
	this->clients_.clear();
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

std::string server::recieve_data(pollfd_iter client) {
	std::string buff;
	while (true) {
		int8_t tmp[BUFF_SIZE];
		ssize_t n_bytes = recv(client->fd, tmp, sizeof(tmp), 0);
		if (n_bytes == 0) {
			close(client->fd);
			this->clients_.erase(client);
			break;
		} else if (n_bytes < 0 && errno != EWOULDBLOCK) {
			terminate_and_throw();
		} else {
			buff += std::string(tmp, tmp + BUFF_SIZE);
		}
	}
	return buff;
}

void server::run() {
	std::cerr << "kjjgjk\n";
	socklen_t sock_len = sizeof(struct sockaddr);
	while (true) {
		int status = poll(this->clients_.data(), this->clients_.size(), TIMEOUT * 1000);
		if (status < 0) {
			terminate_and_throw();
		} else if (status == 0) {
			std::cout << "hi" << std::endl;
			continue;
		}

		for (unsigned i = 0; i < this->clients_.size(); ++i) {
			if (this->clients_[i].revents & POLLIN) {
				if (this->clients_[i].fd == this->sock_fd_) {
					while (true) {
						int client_fd;
						if ((client_fd = accept(this->sock_fd_, this->addr_, &sock_len)) < 0) {
							if (errno != EWOULDBLOCK)
								terminate_and_throw();
							break;
						}

						set_socket_options(client_fd);
						this->clients_.push_back(client_pollfd(client_fd));
					}
				} else {
					std::string data = recieve_data(this->clients_.begin() + i);
					std::cout << data << '\n';
				}
			}
		}
	}
}
