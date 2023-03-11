/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:48:54 by mhanda            #+#    #+#             */
/*   Updated: 2023/03/11 14:44:05 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parser.hpp"
#include <iostream>
/*
#include "headers/command.hpp"

namespace yairc {
  std::vector<command> cmds;

  static void initialise_commands() {
	{
	  std::vector<std::string> user_args;
	  user_args.push_back("username");
	  user_args.push_back("hostname");
	  user_args.push_back("servername");
	  user_args.push_back("realname");
	  cmds.push_back(command("user", user_args));
	}
	{
	  std::vector<std::string> user_args;
	  user_args.push_back("username");
	  user_args.push_back("hostname");
	  user_args.push_back("servername");
	  user_args.push_back("realname");
	}
  }


}
*/

int	main(int ac, char **av)
{
  // yairc::initialise_commands();
	if (checker(ac, av) == 0)
		return (0);
	parse_command();
	//enter here : start exec
	return (0);
}
