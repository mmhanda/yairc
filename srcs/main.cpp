// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/03/05 03:13:39 by archid            #+#    #+#             //
//   Updated: 2023/03/05 05:15:03 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "server.hpp"

int main() {
  yairc::server instance(NULL, 8881);

  while (true) {
	instance.listen();
	instance.recieve_data();
  }


  return 0;
}
