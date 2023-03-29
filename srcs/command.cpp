

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
            std::transform(splited_line[0].begin(), splited_line[0].end(),
                            splited_line[0].begin(), toupper);
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




		// input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
		// input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
		// str = const_cast<char *>(input.c_str());
		// str = strtok(str, " ");
		// if (str != NULL)
		// {
		// 	int x = 0;
		// 	while (str != NULL)
		// 	{
		// 		if(x == 0)
		// 		{
		// 			int i = 0;
		// 			while (str[i])
		// 			{
		// 				toupper(str[i]);
		// 				i++;
		// 			}
					
		// 		}
		// 		x++;
		// 		splited_line.push_back(str);
		// 		str = strtok(NULL, " ");
		// 	}
			