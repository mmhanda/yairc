#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>

class user {

	public:
		user(int client_fd);
		~user();

		int client_fd() const { return client_fd_; }

		const std::string &nickname() const;
		void nickname(std::string nickname);

		const std::string &username() const;
		void username(std::string username);

		class channel *chan;

		bool PASS_authenticated;
		bool NICK_authenticated;
		bool USER_authenticated;
		bool PRINTER;

	protected:
		int client_fd_;
		std::string nickname_, username_;
};

void send_confirm_msg(user *user_);
std::string append_msgs(std::vector<std::string> splited_msg);