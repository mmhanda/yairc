// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   yairc.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/24 23:53:44 by mhanda            #+#    #+#             //
//   Updated: 2023/03/05 03:21:28 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <sys/socket.h>
#include <sys/types.h>

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

namespace yairc {
  template<typename T>

  class command {
  public:
    command();

    bool exec();
  };

  class channel;
  typedef class channel *channel_ptr;

  class channel {
  public:
    channel();

    bool join(client &foo);
  };


} // namespace yairc
