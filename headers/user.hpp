/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 03:21:35 by archid            #+#    #+#             */
//   Updated: 2023/03/22 19:21:27 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <string>
#include <set>
#include <map>

enum user_roles { role_user, role_operator };

class user {

public:
	user(int client_fd);

	int client_fd() const { return client_fd_; }

	const std::string &nickname() const;
	void nickname(std::string nickname);

	const std::string &username() const;
	void username(std::string username);

	bool join_or_create_channel(const std::string &chan_name);
	bool private_message(const user *user, const std::string &msg);
	void leave_channel(class channel *chan);


	bool PASS_authenticated;
	bool NICK_authenticated;
	bool USER_authenticated;

protected:
	int client_fd_;
	std::map<class channel *, user_roles> roles_;
	std::string nickname_, username_;

};

std::ostream &operator<<(std::ostream &oss, const class user u);

#endif
