// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             //
//   Updated: 2023/03/14 01:29:29 by archid           ###   ########.fr       //
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

	void server::start() {
		if ((sock_fd_ = socket(PF_INET, SOCK_STREAM, 0)) < 0
				|| ((bind(sock_fd_, addr_, sizeof(struct sockaddr))) < 0))
			terminate_and_throw();
		int flags = fcntl(sock_fd_, F_GETFL, 0);
		if (flags < 0 || fcntl(sock_fd_, F_SETFL, flags | O_NONBLOCK) < 0)
			terminate_and_throw();
		clients_.push_back(poll_fd(sock_fd_, POLLIN));

		if ((::listen(sock_fd_, NUM_CONNECTIONS)) < 0)
			terminate_and_throw();
	}

	void server::terminate() {
		if (sock_fd_ != -1)
			close(sock_fd_);
		for (unsigned i = 0; i < clients_.size(); ++i)
			close(clients_[i].fd());
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

	bool server::fetch() {
		socklen_t sock_len = sizeof(struct sockaddr);
		int client_fd;
		if ((client_fd = ::accept(sock_fd_, addr_, &sock_len)) < 0) {
			if (errno != EWOULDBLOCK)
				terminate_and_throw();
			return false;
		}
		clients_.push_back(poll_fd(client_fd, POLLIN));
		return true;
	}

	std::string	server::recieve_data(poll_fd client) {
		std::string buff;
		while (true) {
			int8_t tmp[BUFF_SIZE];
			ssize_t n_bytes = recv(client.fd(), tmp, BUFF_SIZE, 0);
			if (n_bytes == 0) {
				close(client.fd());
				clients_.erase(std::find(clients_.begin(), clients_.end(), client));
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
			if ((status = poll_fd::fetch(clients_, TIMEOUT * 1000)) < 0) {
				terminate_and_throw();
			} else if (status == 0) {
				continue;
			}

			for (unsigned i = 0; i < clients_.size(); ++i) {
				if (!(clients_[i].revents() & POLLIN)) {
					continue;
				} if (clients_[i].fd() == sock_fd_ && !fetch()) {
					break;
				} else {
					std::string data = recieve_data(clients_[i]);
					std::cout << data << '\n';
				}
			}
		}
	}

} // namespace yairc
