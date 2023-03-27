/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:59:52 by archid            #+#    #+#             */
/*   Updated: 2023/03/26 10:57:13 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

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

server::server(int port, std::string passwd)  : addr_(setup_address(port)), passwd_(passwd) { start(); }


void server::start() {
	if ((sock_fd_ = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		terminate_and_throw();
	int yes = 1;
	if (setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
		terminate_and_throw();

	if (bind(sock_fd_, addr_, sizeof(struct sockaddr)) < 0)
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

void server::message(int client_fd, const std::string &msg, int flags) {
	ssize_t n_bytes = ::send(client_fd, msg.c_str(), msg.size(), flags);
	if (n_bytes < 0)
		terminate_and_throw();
}

ssize_t server::recieve_message(pollfd_iter client) {
	std::int8_t buffer[BUFF_SIZE];
	ssize_t n_bytes = recv(client->fd, buffer, sizeof(buffer), 0);

	if (n_bytes > 0) {
		map_msgs[client->fd].append(buffer, buffer + n_bytes);
	} else if (n_bytes == 0) {
		std::cout << "[ * ]" << map_users.at(client->fd)->username() << " has disconnected\n";
		close(client->fd);
		map_msgs.erase(client->fd);
		clients_.erase(client);
	} else if (errno != EWOULDBLOCK) {
		terminate_and_throw();
	}
	return n_bytes;
}

void server::accept_clients() {
	socklen_t sock_len = sizeof(struct sockaddr);
	int client_fd;

	while ((client_fd = ::accept(sock_fd_, addr_, &sock_len)) >= 0) {
		message(client_fd, "[ Welcome to YAIRC server ]\n");
		map_users.insert(std::pair<int, user *>(client_fd, new user(client_fd)));
		clients_.push_back(client_pollfd(client_fd));
		std::cerr << "New client joined number " << "[ "
				<< map_users.size() << " ]\n";
	}

	if (client_fd < 0 && errno != EWOULDBLOCK) {
		terminate_and_throw();
	}
}

int count;

void server::run() {
	count =  0;
	while (true) {
		int status;
		if ((status = poll(clients_.data(), clients_.size(), TIMEOUT * 1000)) < 0) {
			terminate_and_throw();
		} else if (status == 0) {
			continue;
		}

		for (unsigned i = 0; i < clients_.size(); ++i)
		{
			if (clients_[i].revents & POLLIN) {
				if (clients_[i].fd == sock_fd_) {
					accept_clients();
				} else {
					if(!recieve_message(clients_.begin() + i))
						continue;

					if (map_msgs.at(clients_[i].fd).find(msg_delim) != std::string::npos)
					{
						std::string msg = map_msgs.at(clients_[i].fd);
						if (authenticate(msg, clients_[i].fd, map_users.at(clients_[i].fd)))
						{
							parse_command(msg, clients_[i].fd, map_users.at(clients_[i].fd));
						}

						map_msgs.erase(clients_[i].fd);
						msg.erase();
					}
				}
			}
		}
	}
}

const char *msg_delim = "\n";
std::map<int, std::string> map_msgs;
std::map<int, class user *> map_users;
std::vector<std::string> server_user_names;
std::vector<std::string> server_nick_names;
std::map<std::string, class channel *> map_channels;
std::vector<std::string> channels_name;
