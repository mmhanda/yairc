// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             //
//   Updated: 2023/03/10 23:05:43 by archid           ###   ########.fr       //
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

#include "client.hpp"

#define str_error() strerror(errno)

#define NUM_CONNECTIONS 16
#define BUFF_SIZE 256
#define TIMEOUT 1								// seconds
#define PORT 8881

namespace yairc {

	struct poll_fd {
		poll_fd(int fd, short e) {
			_.fd = fd, _.events = e, _.revents = 0;
		}

		bool operator==(const poll_fd &rhs) const {
			return _.fd == rhs._.fd && _.events == rhs._.events
				&& _.revents == rhs._.revents;
		}

		struct pollfd operator*() { return _; };

		int fd() const { return _.fd; }
		void fd(int fd) { _.fd = fd; }

		int events() const { return _.events; }
		void events(short e) { _.events = e; }

		int revents() const { return _.revents; }
		void revents(short re) { _.revents = re; }

		struct inserter_ftor {
			std::vector<struct pollfd> bar;

			inserter_ftor(const std::vector<poll_fd> &foo) {
				bar.reserve(foo.size());
			}

			void operator()(poll_fd foo) { bar.push_back(foo._); }
		};

		static int fetch(const std::vector<poll_fd> &foo, int timeout) {
			inserter_ftor inserter(foo);
			std::for_each(foo.begin(), foo.end(), inserter);
			return poll(inserter.bar.data(), inserter.bar.size(), timeout);
		}

	private:
		struct pollfd _;
	};

	class server {
		void														terminate_and_throw();
		struct sockaddr									*setup_address(const char *host, int port);
		template <typename T> ssize_t		send(int fd, T buff, size_t size) {
			return ::send(fd, reinterpret_cast<void *>(buff), size, 0);
		}

		void														start();
		void														terminate();
		void														recieve_data(poll_fd pollfd);
		void														server_banner(int client_fd);

		bool														fetch();

	public:

		server(int port, const char *host = NULL);
		server(const server &) {
			assert(false && "Should not copy server");
			throw std::runtime_error("Should not copy server");
		}

		void														run();

	private:

		struct sockaddr									*addr_;
		int															sock_fd_;
		std::vector<poll_fd>						clients_;
		bool														running_;
	};

} // namespace yairc
