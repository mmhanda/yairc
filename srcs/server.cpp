// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             //
//   Updated: 2023/03/14 11:16:48 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "server.hpp"

namespace yairc {
	struct sockaddr	*server::setup_address(const char *host, int port) {
		static struct sockaddr_in addr;
		bzero(addr.sin_zero, sizeof(addr.sin_zero)); // set padding

		addr.sin_family = AF_INET;					 // address family
		addr.sin_port = htons(port);				 // address port
		addr.sin_addr.s_addr = host					 // host address
			? inet_addr(host) : htonl(INADDR_ANY);

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
		if (sock_fd_ != -1)
			close(sock_fd_);
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

	std::string	server::recieve_data(pollfd_iter client) {
		std::string buff;
		while (true) {
			int8_t tmp[BUFF_SIZE];
			ssize_t n_bytes = recv(client->fd, tmp, sizeof(tmp), 0);
			if (n_bytes == 0) {
				close(client->fd);
				clients_.erase(client);
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
		while (true) {
			int status;
			std::cerr << "polling\n";
			if ((status = poll(clients_.data(), clients_.size(), TIMEOUT * 1000)) < 0) {
				terminate_and_throw();
			} else if (status == 0) {
				std::cerr << "here\n";
				continue;
			}

			std::cerr << "ready\n";
			for (unsigned i = 0; i < clients_.size(); ++i) {
				const pollfd &client = clients_[i];
				if (client.revents & POLLIN) {
					if (client.fd == sock_fd_) {
						while (true) {
							std::cerr << "server accept\n";
							socklen_t sock_len = sizeof(struct sockaddr);
							int client_fd;
							if ((client_fd = ::accept(sock_fd_, addr_, &sock_len)) < 0) {
								if (errno != EWOULDBLOCK)
									terminate_and_throw();
								break;
							}

							// if (fcntl(sock_fd_, F_SETFL, O_NONBLOCK) < 0)
							// 	terminate_and_throw();

							clients_.push_back(client_pollfd(client_fd));
						}
					} else {
						std::string data = recieve_data(clients_.begin() + i);
						std::cout << data << '\n';
					}
				}
			}
		}
	}

} // namespace yairc
