/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 03:21:35 by archid            #+#    #+#             */
//   Updated: 2023/03/23 20:19:44 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <set>
#include <map>
#include <string>
#include <iostream>

enum user_roles { role_user, role_operator };

class user {
	public:
		typedef std::map<class channel *, user_roles> role_map;

		user(int client_fd);
		~user();

		int client_fd() const { return client_fd_; }

		const std::string &nickname() const;
		void nickname(std::string nickname);

		const std::string &username() const;
		void username(std::string username);

		bool join_or_create_channel(const std::string &chan_name);
		bool private_message(const user *user, const std::string &msg);
		void part_channel(class channel *chan);

		bool is_operator(class channel *chan);
		
		bool PASS_authenticated;
		bool NICK_authenticated;
		bool USER_authenticated;

	protected:
		int client_fd_;
		role_map roles_;
		std::string nickname_, username_;
};

std::ostream &operator<<(std::ostream &oss, const user u);

#endif
