#pragma once
#include "server.hpp"

class bot
{
    public:
        void start(int fd);
        void channel_list(int fd);
        void random_join(user *);
        bot();
        ~bot();
};
