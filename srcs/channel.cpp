// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   channel.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 04:55:12 by archid            #+#    #+#             //
//   Updated: 2023/02/25 04:56:39 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "yairc.hpp"

namespace yairc {
channel::channel() {}

bool channel::join(client &foo) {
	if (foo.channels_.end() == std::find(foo.channels_.begin(),
										 foo.channels_.end(), this)) {
		return false;
	} else {
		foo.channels_.push_back(this);
		return true;
	}
}
} // namespace yairc
