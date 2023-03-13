// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             //
//   Updated: 2023/03/13 04:19:55 by archid           ###   ########.fr       //
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
#define TIMEOUT 1								// seconds
#define PORT 8881

namespace yairc {

	struct poll_fd {
		poll_fd(int fd, short e) {
			_.fd = fd, _.events = e, _.revents = 0;
		}

		struct pollfd		operator*() { return _; };
		bool						operator==(const poll_fd &rhs) const {
			return _.fd == rhs._.fd && _.events == rhs._.events
				&& _.revents == rhs._.revents;
		}

		int							fd() const { return _.fd; }
		void						fd(int fd) { _.fd = fd; }

		int							events() const { return _.events; }
		void						events(short e) { _.events = e; }

		int							revents() const { return _.revents; }
		void						revents(short re) { _.revents = re; }

		static int			fetch(const std::vector<poll_fd> &foo, int timeout) {
			inserter_ftor inserter(foo);
			std::for_each(foo.begin(), foo.end(), inserter);
			return poll(inserter.bar.data(), inserter.bar.size(), timeout);
		}

	private:
		struct inserter_ftor {
			std::vector<struct pollfd> bar;

			inserter_ftor(const std::vector<poll_fd> &foo) {
				bar.reserve(foo.size());
			}

			void operator()(poll_fd foo) { bar.push_back(foo._); }
		};

		struct pollfd _;
	};

	class server {
		struct sockaddr									*setup_address(const char *host, int port);

		void														start();
		void														terminate();
		void														terminate_and_throw();
		void														server_banner(int client_fd);

		bool														fetch();
		std::string											recieve_data(poll_fd pollfd);

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
	};


	// user defined allocation
	// side-effect deallcoation
	template <typename T> struct data {
		typedef T													type;

		explicit data(type *ptr) : _(ptr) {}
		virtual ~data() { delete _; }

		virtual std::vector<std::int8_t>	as_buffer() const = 0;
		virtual size_t										size() const = 0;

	protected:
		type *_;
	};

	template <typename T>
	struct integral_data : data<T> {
		explicit integral_data(T *ptr) : data<T>(ptr) {}

		virtual std::vector<std::int8_t>	as_buffer() const {
			std::int8_t buff[sizeof(T)];
			*reinterpret_cast<T *>(buff) = *this->_;
			return std::vector<std::int8_t>(buff, buff + sizeof(T));
		}

		virtual size_t										size() const {
			return sizeof(T);
		}
	};

	struct string_data : data<char> {
		explicit string_data(char *str) : data<char>(str), sz_(std::strlen(str)) {}
		string_data(char *str, size_t size) : data<char>(str), sz_(size) {}

		virtual std::vector<std::int8_t>	as_buffer() const {
			std::vector<std::int8_t> buff;
			buff.reserve(sz_);
			std::copy_n(this->_, sz_, buff.begin());
			return buff;
		}

		virtual size_t										size() const {
			return sz_;
		}

	private:
		size_t sz_;
	};

	template <typename T> ssize_t	send_data(int client_fd, data<T> data, int flags = 0) {
		return ::send(client_fd, data.as_buffer().data, data.size(), flags);
	}


} // namespace yairc
