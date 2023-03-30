#include "server.hpp"
#include "channel.hpp"

int check_MODE(std::vector<std::string> &splited_line, user *user_)
{

    // /* check if the user is an operator */
    // if (user_->chan != nullptr)
    // {
    //     std::map<std::string, class channel *>::iterator it = map_channels.find(user_->chan->name());
    //     if (it != map_channels.end())
    //     {

    //         std::vector<std::string> admins_list = it->second->get_admins_list();
    //         // if(admins_list.find(splited_line[2]) == admins_list.end())
    //         if (std::find(admins_list.begin(), admins_list.end(), user_->username()) == admins_list.end())
    //         {
    //             // ERR_CHANOPRIVSNEEDED (482)  "<client> <channel> :You're not channel operator"
    //             std::string error_(":ircserv 482 KICK : :You're not channel operator\r\n");
    //             send(user_->client_fd(), error_.c_str(), error_.length(), 0);
    //             return 0;
    //         }

    //         if (splited_line.size() >= 2)
    //         {

    //             size_t i = 0;
    //             while (i < splited_line[1].size())
    //             {
    //                 if (splited_line.size() == 3 && splited_line[2].at(i) == '+' && splited_line[2].at(i + 1) == 'o')
    //                 {

    //                     std::cout << "  splited_line[1].at(i) == 'o'" << std::endl;
    //                 }
    //                 if (splited_line[1].at(i) == 'l' && !splited_line[2].empty())
    //                 {
    //                     std::cout << splited_line[2] << " splited_line[2]" << std::endl;
    //                 }

    //                 std::cout << splited_line[1].at(i) << std::endl;
    //                 i++;
    //             }
    //             return 0;
    //         }
    //     }
    // }
    std::string broad;
    /* works of mhanda */
    if (std::find(server_user_names.begin(), server_user_names.end(), splited_line[1]) == server_user_names.end() || user_->chan == nullptr || splited_line.size() <= 1)
        return 0;
    if (user_->chan->how_many_usr() > 1 && splited_line.size() == 3 && user_->username() != splited_line[1] && user_->chan->check_if_s_user_in_by_name(user_->username()))
    {

        if ((std::find(splited_line[2].begin(), splited_line[2].end(), '+') != splited_line[2].end() && std::find(splited_line[2].begin(), splited_line[2].end(), 'o') != splited_line[2].end()))
        {

            if (!user_->chan->check_if_s_user_in_by_name(splited_line[1]) && user_->chan->check_if_r_user_in_by_name(splited_line[1]))
            {
                user_->chan->set_in_admins_list(splited_line[1]);
                broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE mode has changed for the user given to +o\r\n";
                send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                return (0);
            }
            else
            {
                broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE user already admin or not found\r\n";
                send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                return 0;
            }
        }

        if ((std::find(splited_line[2].begin(), splited_line[2].end(), '-') != splited_line[2].end() && std::find(splited_line[2].begin(), splited_line[2].end(), 'o') != splited_line[2].end()))
        {

            if (user_->chan->check_if_s_user_in_by_name(splited_line[1]))
            {
                user_->chan->remove_from_s_list(splited_line[1]);
                broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE mode has changed for the user given to -o\r\n";
                send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                return (0);
            }
            else
            {
                broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE user already not an operator\r\n";
                send(user_->client_fd(), broad.c_str(), broad.size(), 0);
                return 0;
            }
        }
        else
        {
            broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE invalid operation\r\n";
            send(user_->client_fd(), broad.c_str(), broad.size(), 0);
            return 0;
        }
    }

//   else  if (user_->chan->how_many_usr() > 1 && splited_line.size() == 3 && user_->username() != splited_line[1] && user_->chan->check_if_s_user_in_by_name(user_->username()))
//     {

//         if ((std::find(splited_line[2].begin(), splited_line[2].end(), 'l') != splited_line[2].end() && std::find(splited_line[2].begin(), splited_line[2].end(), 'o') != splited_line[2].end()))
//         {

//             if (!user_->chan->check_if_s_user_in_by_name(splited_line[1]) && user_->chan->check_if_r_user_in_by_name(splited_line[1]))
//             {
//                 user_->chan->set_in_admins_list(splited_line[1]);
//                 broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE mode has changed for the user given to +o\r\n";
//                 send(user_->client_fd(), broad.c_str(), broad.size(), 0);
//                 return (0);
//             }
//             else
//             {
//                 broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE user already admin or not found\r\n";
//                 send(user_->client_fd(), broad.c_str(), broad.size(), 0);
//                 return 0;
//             }
//         }

//         if ((std::find(splited_line[2].begin(), splited_line[2].end(), '-') != splited_line[2].end() && std::find(splited_line[2].begin(), splited_line[2].end(), 'o') != splited_line[2].end()))
//         {

//             if (user_->chan->check_if_s_user_in_by_name(splited_line[1]))
//             {
//                 user_->chan->remove_from_s_list(splited_line[1]);
//                 broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE mode has changed for the user given to -o\r\n";
//                 send(user_->client_fd(), broad.c_str(), broad.size(), 0);
//                 return (0);
//             }
//             else
//             {
//                 broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE user already not an operator\r\n";
//                 send(user_->client_fd(), broad.c_str(), broad.size(), 0);
//                 return 0;
//             }
//         }
//         else
//         {
//             broad = ":" + user_->username() + "!" + user_->username() + "@ircserv NOTICE invalid operation\r\n";
//             send(user_->client_fd(), broad.c_str(), broad.size(), 0);
//             return 0;
//         }
//     }

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