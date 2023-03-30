#pragma once

#include "server.hpp"

enum channel_properties { disabled_n, enabled_n };

class channel {
	public:
		std::vector<std::string> banned_kicked_users;
		std::map<std::string,user *> all_users; 

		typedef std::map<std::string, class user *> for_kick;
		channel(std::string name, std::string passwd = "", std::string topic = "");
		std::string passwrd(void);
		void broadcast(std::string msg);
		
		std::string users_list();
		void notif_new_client_joined(user *sender);
		
		void insert_users(user *user);
		void insert_in_kick_list(user *user);

		for_kick kick_list() { return map_users_for_kick; }
		void part_user(user *user);
		int  how_many_usr() const {return users_fd.size();}
		// enum channel_properties out_side_msg = enabled_n;

		const std::string &name() const { return name_; }
		const std::string &topic() const { return topic_; }

		std::vector<std::string> get_admins_list() { return this->admin_names; }
							bool get_limit_state() { return this->limit; }
							int  get_limit() { return this->chan_limit; }

		void set_topic(const std::string &top) {topic_ = top;}
		void set_in_admins_list(std::string admin) { this->admin_names.push_back(admin); }
		void set_in_regular_list(std::string admin) { this->r_user_names.push_back(admin); }
		void set_chan_limit(int limit) { this->chan_limit = limit; this->limit = true; }

		void remove_limit() { this->limit = false; }
		void remove_from_s_list(std::string old_admin) { admin_names.erase(std::remove(admin_names.begin(),
						admin_names.end(), old_admin) , admin_names.end()); }

		bool check_if_user_in(user *user_to_check);
		bool check_if_r_user_in_by_name(std::string user_to_check);
		bool check_if_s_user_in_by_name(std::string user_to_check);

		std::vector<int> users_fd;
	private:
		for_kick map_users_for_kick;
		std::vector<std::string> admin_names;
		std::vector<std::string> r_user_names;
		std::string name_,  passwd,topic_;
		bool limit;
		int chan_limit;
};

void	send_msg(std::string, user *user);
std::string get_tim();

std::ostream &operator<<(std::ostream &oss, const class channel chan);
typedef std::map<std::string, class channel *> channel_map;
extern channel_map channels;
extern std::vector<std::string> channels_name;