#include "server.hpp"
#include <iostream>
#include <sstream>

void channel::notif_new_client_joined(user *sender)
{
	std::string broad = SEND_CHAN(sender->username(), sender->username(), sender->chan->name());
	for (std::vector<int>::iterator it = users_fd.begin(); it != users_fd.end(); ++it)
	{
		int user_fd = *it;
		if (sender->client_fd() != user_fd)
		{
			send(user_fd, broad.c_str(), broad.size(), 0);
		}
	}
}

std::string channel::users_list()
{
	std::string ret = ":@";

	int i = 0;
	size_t itt = 0;
	std::vector<std::string>::iterator it;
	while (i < how_many_usr())
	{
		if (i == 0)
			ret += admin_names[0] + " ";

		else if (r_user_names.end() != it)
		{
			ret += r_user_names[itt] + " ";
			itt++;
		}
		it++;
		i++;
	}
	return (ret);
}

channel::channel(std::string name, std::string passwd, std::string topic)
	: name_(name), passwd(passwd), topic_(topic) {}

void channel::insert_users(user *user)
{
	if (how_many_usr() == 0)
	{
		this->admin_names.push_back(user->username());
		all_users.insert(std::make_pair(user->username() , user));
	}
	else
	{
		this->r_user_names.push_back(user->username());
		all_users.insert(std::make_pair(user->username() , user));
	}
	user->chan = this;
	this->users_fd.push_back(user->client_fd());
}

void channel::insert_in_kick_list(user *user_) {
	this->map_users_for_kick.insert(std::pair<std::string, user*>(
		user_->username(), user_));
}

std::string channel::passwrd(void)
{
	return (this->passwd);
}

void channel::broadcast(std::string msg)
{
	for (std::vector<int>::iterator it = users_fd.begin(); it != users_fd.end(); ++it)
	{
		int user_fd = *it;
		send(user_fd, msg.c_str(), msg.size(), 0);
	}
}

void channel::part_user(user *user)
{
	std::vector<int>::iterator new_end = std::remove(users_fd.begin(), users_fd.end(), user->client_fd());
	users_fd.erase(new_end, users_fd.end());
	user->chan = nullptr;
}

bool channel::check_if_user_in(user *user_to_check)
{
	std::vector<int>::iterator it = std::find(users_fd.begin(), users_fd.end(), user_to_check->client_fd());
	if (it != users_fd.end())
		return (true);
	else
		return (false);
}

bool channel::check_if_s_user_in_by_name(std::string user_to_check)
{
	std::vector<std::string>::iterator it_s = std::find(this->admin_names.begin(), this->admin_names.end(), user_to_check);
	if (it_s != admin_names.end())
		return (true);
	else
		return (false);
}

bool channel::check_if_r_user_in_by_name(std::string user_to_check)
{
	std::vector<std::string>::iterator it_r = std::find(this->r_user_names.begin(), this->r_user_names.end(), user_to_check);
	if (it_r != this->r_user_names.end())
		return (true);
	else
		return (false);
}

std::ostream &operator<<(std::ostream &oss, const channel chan)
{
	return oss << "#" << chan.name() << " [" << chan.topic() << "]";
}

channel_map channels;
