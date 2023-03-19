// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   data.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/19 21:49:29 by archid            #+#    #+#             //
//   Updated: 2023/03/19 22:00:22 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <vector>
#include <sys/socket.h>

// user defined allocation
// side-effect deallcoation
template <typename T> struct data {
	typedef T type;

	explicit data(type *ptr) : _(ptr) {}
	virtual ~data() { delete _; }

	virtual std::vector<std::int8_t> as_buffer() const = 0;
	virtual size_t size() const = 0;
	ssize_t send(int fd, int flags = 0) {
		return ::send(fd, as_buffer().data(), size(), flags);
	}

protected:
	type *_;
};

template <typename T> struct integral_data : data<T> {
	explicit integral_data(T *ptr) : data<T>(ptr) {}

	virtual std::vector<std::int8_t> as_buffer() const {
		std::int8_t buff[sizeof(T)];
		*reinterpret_cast<T *>(buff) = *this->_;
		return std::vector<std::int8_t>(buff, buff + sizeof(T));
	}

	virtual size_t size() const { return sizeof(T); }
};

struct string_data : data<char> {
	explicit string_data(char *str) : data<char>(str), sz_(std::strlen(str)) {}
	string_data(char *str, size_t size) : data<char>(str), sz_(size) {}

	virtual std::vector<std::int8_t> as_buffer() const {
		std::vector<std::int8_t> buff;
		buff.reserve(sz_);
		std::copy_n(this->_, sz_, buff.begin());
		return buff;
	}

	virtual size_t size() const { return sz_; }

private:
	size_t sz_;
};
