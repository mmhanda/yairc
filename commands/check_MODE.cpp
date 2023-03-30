#include "server.hpp"
#include "channel.hpp"

int check_MODE(std::vector<std::string> &splited_line, user *user_)
{
    std::string	broad ;

    if (std::find(server_user_names.begin(), server_user_names.end(), splited_line[1]) == server_user_names.end()
                || user_->chan == nullptr)
        return 0;

        if (user_->chan->how_many_usr() > 1 && splited_line.size() == 3
            && user_->username() != splited_line[1]
            && user_->chan->check_if_s_user_in_by_name(user_->username())) {

                if ((std::find(splited_line[2].begin(), splited_line[2].end(), '+') != splited_line[2].end()
                        && std::find(splited_line[2].begin(), splited_line[2].end(), 'o') != splited_line[2].end())) {
                                    
                    if (!user_->chan->check_if_s_user_in_by_name(splited_line[1])
                            && user_->chan->check_if_r_user_in_by_name(splited_line[1])) {
                        user_->chan->set_in_admins_list(splited_line[1]);
                        broad = ":" + user_->username() + "!" + user_->username()
                        + "@ircserv NOTICE mode has changed for the user given to +o\r\n";
                        send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                        return (0);
                    }
                    else {
                        broad = ":" + user_->username() + "!" + user_->username()
                        + "@ircserv NOTICE user already admin or not found\r\n";
                        send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                        return 0;
                    }
                }

                if ((std::find(splited_line[2].begin(), splited_line[2].end(), '-') != splited_line[2].end()
                        && std::find(splited_line[2].begin(), splited_line[2].end(), 'o') != splited_line[2].end())) {
                            
                    if (user_->chan->check_if_s_user_in_by_name(splited_line[1])) {
                        user_->chan->remove_from_s_list(splited_line[1]);
                        broad = ":" + user_->username() + "!" + user_->username()
                        + "@ircserv NOTICE mode has changed for the user given to -o\r\n";
                        send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                        return (0);
                    }
                    else {
                        broad = ":" + user_->username() + "!" + user_->username()
                        + "@ircserv NOTICE user already not an operator\r\n";
                        send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                        return 0;
                    }
                }
                else {
                    broad = ":" + user_->username() + "!" + user_->username()
                    + "@ircserv NOTICE invalid operation\r\n";
                    send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                    return 0;
                }
        }
    
    // else if (splited_line.size() == 3 && std::find(channels_name.begin(),
    //         channels_name.end(), splited_line[1]) != channels_name.end()
    //             && user_->chan->name() == splited_line[1] && std::find(splited_line[1].begin(),
    //                 splited_line[1].end(), '#') != splited_line[1].end()) {

    //             if ((std::find(splited_line[2].begin(), splited_line[2].end(), '+') != splited_line[2].end()
    //                     && std::find(splited_line[2].begin(), splited_line[2].end(), 'l') != splited_line[2].end())) {

    //                 if (!user_->chan->check_if_s_user_in_by_name(splited_line[1])
    //                         && user_->chan->check_if_r_user_in_by_name(splited_line[1])) {
    //                     user_->chan->set_in_admins_list(splited_line[1]);
    //                     broad = ":" + user_->username() + "!" + user_->username()
    //                     + "@ircserv NOTICE mode has changed for the user given to +l\r\n";
    //                     send(user_->client_fd(), broad.c_str(), broad.size(), 0);
    //                     return (0);
    //                 }
    //                 else {
    //                     broad = ":" + user_->username() + "!" + user_->username()
    //                     + "@ircserv NOTICE user already admin or not found\r\n";
    //                     send(user_->client_fd(), broad.c_str(), broad.size(), 0);
    //                     return 0;
    //                 }
    //             }

    //             if ((std::find(splited_line[2].begin(), splited_line[2].end(), '-') != splited_line[2].end()
    //                     && std::find(splited_line[2].begin(), splited_line[2].end(), 'n') != splited_line[2].end())) {

    //                 if (user_->chan->check_if_s_user_in_by_name(splited_line[1])) {
    //                     user_->chan->remove_from_s_list(splited_line[1]);
    //                     broad = ":" + user_->username() + "!" + user_->username()
    //                     + "@ircserv NOTICE mode has changed for the user given to -n\r\n";
    //                     send(user_->client_fd(), broad.c_str(), broad.size(), 0);
    //                     return (0);
    //                 }
    //                 else {
    //                     broad = ":" + user_->username() + "!" + user_->username()
    //                     + "@ircserv NOTICE user already not an operator\r\n";
    //                     send(user_->client_fd(), broad.c_str(), broad.size(), 0);
    //                     return 0;
    //                 }
    //             }
    //             else {
    //                 broad = ":" + user_->username() + "!" + user_->username()
    //                 + "@ircserv NOTICE invalid operation\r\n";
    //                 send(user_->client_fd(), broad.c_str(), broad.size(), 0);
    //                 return 0;
    //             }
    // }
    return 0;
}
        // if ((std::find(splited_line[2].begin(), splited_line[2].end(), '+') != splited_line[2].end()
        //         && std::find(splited_line[2].begin(), splited_line[2].end(), 'l') != splited_line[2].end())
        //             || (std::find(splited_line[2].begin(), splited_line[2].end(), '-') != splited_line[2].end()
        //                 && std::find(splited_line[2].begin(), splited_line[2].end(), 'l') != splited_line[2].end())
        //             || (std::find(splited_line[2].begin(), splited_line[2].end(), '+') != splited_line[2].end()
        //         && std::find(splited_line[2].begin(), splited_line[2].end(), 'n') != splited_line[2].end())
        //             || (std::find(splited_line[2].begin(), splited_line[2].end(), '-') != splited_line[2].end()
        //                 && std::find(splited_line[2].begin(), splited_line[2].end(), 'n') != splited_line[2].end())) {
                            
        //             }