// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 02:31:40 by archid            #+#    #+#             //
//   Updated: 2023/03/18 04:51:01 by archid           ###   ########.fr       //
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


class server {
	typedef std::vector<pollfd>::iterator pollfd_iter;

	struct sockaddr									*setup_address(const char *host, int port);

	void														start();
	void														terminate();
	void														terminate_and_throw();
	void														server_banner(int client_fd);

	std::string											recieve_data(pollfd_iter client);

public:

	server(int port, const char *host = NULL)
		: addr_(setup_address(host, port)) {
		start();
	}

	server(const server &) {
		assert(false && "Should not copy server");
		throw std::runtime_error("Should not copy server");
	}

	void														run();

private:

	struct sockaddr								*addr_;
	int														sock_fd_;
	std::vector<pollfd>						clients_;
};

// user defined allocation
// side-effect deallcoation
template <typename T> struct data {
	typedef T													type;

	explicit data(type *ptr) : _(ptr) {}
	virtual ~data() { delete _; }

	virtual std::vector<std::int8_t>	as_buffer() const = 0;
	virtual size_t										size() const = 0;
	ssize_t														send(int fd, int flags = 0) {
		return ::send(fd, as_buffer().data(), size(), flags);
	}

protected:
	type										*_;
};

template <typename T> struct integral_data : data<T> {
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
	size_t									sz_;
};

extern short	num_port;
extern char		*passwd;

void parse_args(int argc, const char *argv[]);
