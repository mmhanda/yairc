/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:10:03 by archid            #+#    #+#             */
/*   Updated: 2023/03/22 04:43:47 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

// class command {
// public:
// 	typedef command *pointer;

// 	command(std::string cmd);

// 	void set_args(std::vector<std::string> args) { args_ = args; }

// 	virtual void exec(std::vector<std::string> params) = 0;

// 	virtual  bool is_command(std::string cmd) = 	0;

// protected:
// 	std::vector<std::string> args_;
// };

// class user_command : public command {
// public:
// 	user_command() : command("user") {}

// 	virtual void exec(std::vector<std::string> params) {}

// 	virtual bool is_command(std::string cmd) {}
// };

// extern std::vector<command::pointer> cmds;

class command {

	public:
		typedef command *pointer;

		command(std::vector<std::string> parts) : parts_(parts) {}

		virtual int exec() const = 0;

		std::vector<std::string> parts_;

		const std::vector<std::string> &parts() const { return parts_; }
};

command::pointer parse_command(const std::string &msgs);
int exec_command(const std::string &msgs);
