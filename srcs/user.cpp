#include "user.hpp"
#include "channel.hpp"
#include <iostream>

user::user(int client_fd) : PASS_authenticated(false),
				NICK_authenticated(false),
				USER_authenticated(false) {
	client_fd_ = client_fd;
	chan = NULL; 
	// i removed this
}

user::~user() {
	
	delete map_users.at(this->client_fd());
 	map_users.erase(this->client_fd());
	
}

const std::string &user::nickname() const { return nickname_; }

void user::nickname(std::string nickname) { nickname_ = nickname; }

const std::string &user::username() const { return username_; }

void user::username(std::string username) { username_ = username; }

std::string get_tim() {

	time_t now = time(NULL);
	char *time = ctime(&now);
	std::string tim = time;

	std::size_t pos = tim.find("\n");

	if (pos != std::string::npos){
		tim.erase(pos, 1);
	}
	return (tim);
}

void send_confirm_msg(user *user_){

	if (user_->NICK_authenticated && user_->PASS_authenticated
		&&user_->USER_authenticated && user_->PRINTER) {
		std::string sen = ":ircserv 001 " + user_->nickname()
		+ " :Welcome To Internet Relay Chat "
		+ user_->username() + "!"+ user_->nickname() + "@" + "127.0.0.1" + "\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		sen = ":ircserv 002 " + user_->nickname() +
		  " :Host is ircserv, running version 1.1.2\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		sen = ":ircserv 003 " + user_->nickname() +  " :Server created at "
		+ get_tim() + "\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		sen = ":ircserv 004 " + user_->nickname() +  " :ircserv 1.1.2 - -\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		sen = ":ircserv 251 " + user_->nickname() +  " :There are "
		+ std::to_string(server_user_names.size()) + " connected clients\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		sen = ":ircserv 372 " + user_->nickname() +  " :ENJOY\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);
		sen = ":ircserv 376 " + user_->nickname() +  " :Made by Anas and Anas and Simo\r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);

		
		sen = ":ircserv 376 " + user_->nickname() +  " :If you want help use BOT \r\n";
		send(user_->client_fd(), sen.c_str(), sen.size(), 0);



		
		user_->PRINTER = true;
	}
}
