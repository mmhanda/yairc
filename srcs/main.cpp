// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 03:13:39 by archid            #+#    #+#             //
//   Updated: 2023/03/08 23:54:39 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "server.hpp"

#define PORT 8881

int main() {
	yairc::server instance(PORT);

	while (true) {
		instance.listen();
		instance.recieve_data();
	}

	return 0;
}
