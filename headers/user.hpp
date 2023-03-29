/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 03:21:35 by archid            #+#    #+#             */
/*   Updated: 2023/03/29 11:37:13 by mhanda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <string>
#include <set>
#include <map>

enum user_roles { normal_user, _operator };

class user {

	public:
		user(int client_fd);
		~user();

		int client_fd() const { return client_fd_; }

		const std::string &nickname() const;
		void nickname(std::string nickname);

		const std::string &username() const;
		void username(std::string username);

		class channel *chan = nullptr;


		bool PASS_authenticated;
		bool NICK_authenticated;
		bool USER_authenticated;
		bool PRINTER;

	protected:
		int client_fd_;
		std::string nickname_, username_;
};

void send_confirm_msg(user *user_);
#endif
