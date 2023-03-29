
#include "server.hpp"
#include <iostream>
#include <sstream>

void channel::notif_new_client_joined(user *sender) {

	std::string broad = SEND_CHAN(sender->username(), sender->username(),  sender->chan->name());
	for (int user_fd : users_fd) {
		if (sender->client_fd() != user_fd) {
			send(user_fd, broad.c_str(), broad.size(), 0);
		}
	}
}

std::string channel::users_list() {
			
	std::string ret = ":@";

	size_t i = 0;
	size_t itt = 0;
	std::vector<std::string>::iterator it;
	while ( i < how_many_usr())
	{
		if (i == 0)
			ret += admin_names[0] + " ";

		else if (r_user_names.end() != it){
			ret += r_user_names[itt] + " ";
			itt ++;
		}
		it ++;
		i ++;
	}

	return (ret);
}

channel::channel(std::string name, std::string passwd, std::string topic)
	: name_(name), passwd(passwd), topic_(topic) {}

void channel::insert_users(user *user) {
	if (how_many_usr() == 0)
		this->admin_names.push_back(user->username());
	else 
	{
		this->r_user_names.push_back(user->username());
	}
	user->chan = this;
	this->users_fd.push_back(user->client_fd());
}

std::string channel::passwrd(void) {
	return (this->passwd);
}

void channel::broadcast(std::string msg, user *sender) {

	for (int user_fd : users_fd) {
		send(user_fd, msg.c_str(), msg.size(), 0);
	}
}

void channel::part_user(user *user) {

	auto new_end = std::remove(
		users_fd.begin(), users_fd.end(), user->client_fd());
	users_fd.erase(new_end, users_fd.end());
	user->chan = nullptr;
}

bool channel::check_if_user_in() {
	auto it = std::find(users_fd.begin(), users_fd.end(), 3);
	if (it != users_fd.end())
		return (true);
	else
		return(false);
}

std::ostream &operator<<(std::ostream &oss, const channel chan) {
	return oss << "#" << chan.name() << " [" << chan.topic() << "]";
}

channel_map channels;
