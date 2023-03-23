/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:10:03 by archid            #+#    #+#             */
//   Updated: 2023/03/23 21:14:49 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

class command {
	public:

		command(std::vector<std::string> parts) : parts_(parts) {}

		virtual int exec() const = 0;

		const std::vector<std::string> &params() const { return params_; }

protected:
	std::vector<std::string> params_;
};

class user : public command {
};

class nick : public command {
};

class pass : public command {
};

class kick : public command {
};

class join : public command {
};

class privmsg : public command {
};

class oper : public command {
};

class mode : public command{
};

command *parse_command(const std::string &msg);
int exec_command(const std::string &msg);
