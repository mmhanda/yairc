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
#include <iostream>
#include <string>
#include "server.hpp"
#include "channel.hpp"
#include <vector>
#include "user.hpp"

class bot
{
private:
public:
    void start(std::vector<std::string> splited_line, int fd);
    void channel_list(int fd);
    void random_join(user *);
    bot();
    ~bot();
};
