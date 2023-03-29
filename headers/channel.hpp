
#pragma once

#include "server.hpp"

enum channel_properties { chan_public, chan_invite, chan_private };

class channel {
	public:
		channel(std::string name, std::string passwd = "", std::string topic = "");
		std::string passwrd(void);
		void broadcast(std::string msg, user *sender);
		
		std::string users_list();
		void notif_new_client_joined(user *sender);
		
		void insert_users(user *user);
		void part_user(user *user);

		const std::string &name() const { return name_; }
		const std::string &topic() const { return topic_; }
		void set_topic(const std::string &top) {topic_ = top;}

		int 	how_many_usr() const {return users_fd.size();}
		bool	check_if_user_in();

		std::vector<int> users_fd;
	private:
		std::vector<std::string> admin_names;
		std::vector<std::string> r_user_names;
		std::string name_, topic_, passwd;
};

void	send_msg(std::string, user *user);
std::string get_tim();

std::ostream &operator<<(std::ostream &oss, const class channel chan);
typedef std::map<std::string, class channel *> channel_map;
extern channel_map channels;
extern std::vector<std::string> channels_name;