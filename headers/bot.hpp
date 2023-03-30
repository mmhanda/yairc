/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  √                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabiti <atabiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:41:58 by atabiti           #+#    #+#             */
/*   Updated: 2023/03/30 10:42:35 by atabiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
