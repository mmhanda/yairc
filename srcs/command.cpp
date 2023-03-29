

#include "server.hpp"

bool    authenticate(std::string &msg , const int fd, user *user_)
{
	char	*str;
	char	*str1;
	str = NULL;
	str1 = NULL;
    std::vector<std::string> splited_line;
    user *tmp = NULL;
    tmp = map_users.at(fd);
    if (tmp->NICK_authenticated && tmp->PASS_authenticated
        && tmp->USER_authenticated && tmp->PRINTER)
        return (true);

    if (!msg.empty()) {

        msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
        msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());

        str = const_cast<char *>(msg.c_str());

        str = strtok(str, " ");
        if (str != NULL)
        {
            while (str != NULL)
            {
                splited_line.push_back(str);
                str = strtok(NULL, " ");
            }

            if (splited_line[0] == "PASS"){
                if (!check_PASS(splited_line , tmp)){
                    ::send(fd, "461 PASS :Not enough parameters\n", 32, 0);}
                else { send_confirm_msg(user_);} }
            else if (splited_line[0] == "NICK"){
                if (!check_NICK(splited_line, tmp)){
                    ::send(fd, "431 NICK :No nickname given\n", 29, 0);}
                else { send_confirm_msg(user_);} }
            else if (splited_line[0] == "USER"){
                if (!check_USER(splited_line, tmp)){
                    ::send(fd, "461 USER :Not enough parameters\n", 32, 0);}
                else { send_confirm_msg(user_);} }
            else if (splited_line[0] == "QUIT")
                check_QUIT(msg, user_);
        }
    }
    return (false);
}
