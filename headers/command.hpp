// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   command.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/06 17:10:03 by archid            #+#    #+#             //
//   Updated: 2023/03/07 02:55:27 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <vector>
#include <string>

namespace yairc {
  namespace detail {
	std::string tolower(std::)
  }

  struct command {
	typedef command *command_ptr;

	command(std::string cmd);

	void set_args(std::vector<std::string> args) { args_ = args; }

	virtual void exec(std::vector<std::string> params) = 0;

	virtual  bool is_command(std::string cmd) = 	0;

  protected:
	std::vector<std::string> args_;
  };

  class user_command : public command {
	user_command() : command("user") {
	}


	virtual void exec(std::vector<std::string> params) {

	}

	virtual bool is_command(std::string cmd) {std::to_lower()
	}
  };

  extern std::vector<command::command_ptr> cmds;
} // namespace yairc
