/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanda <mhanda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 03:13:39 by archid            #+#    #+#             */
//   Updated: 2023/03/21 03:07:40 by archid           ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <climits>
#include <iostream>
#include "server.hpp"
#include "../parsing/parser.hpp"
#define NUM_DIGITS 5
#define PASSWD_SIZE 32

short num_port;
char *passwd;

// void parse_args(int argc, char *argv[]) {
// 	if (argc != 3) {
// 		std::cerr << "run as " << argv[0] << " <PORT> <PASSWD>\n";
// 		exit(EXIT_FAILURE);
// 	}

// 	for (const char *port = argv[1]; *port != '\0'; ++port) {
// 		if (!std::isdigit(*port) || port - argv[1] > NUM_DIGITS) {
// 			std::cerr << argv[1] << " is not correct\n";
// 			exit(EXIT_FAILURE);
// 		}
// 	}

// 	int tmp = std::atoi(argv[1]);
// 	if ((int)SHRT_MAX < tmp) {
// 		std::cerr << argv[1] << " is invalid\n";
// 		exit(EXIT_FAILURE);
// 	}
// 	num_port = tmp;

// 	for (const char *passwd = argv[2]; *passwd != '\0'; ++passwd) {
// 		if (!std::isprint(*passwd) || passwd - argv[2] > PASSWD_SIZE) {
// 			std::cerr << argv[2] << " is invalid\n";
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	passwd = argv[2];
// }

server serve;

void handler(int) {
	serve.terminate();
	exit(0);
}

int main(int argc, char *argv[]) {
	int		port = 0;
	signal(SIGINT, handler);
	// parse_args(argc, argv);
	if (checker(argc, argv , port) == 0)
		return (0);
	try {
		serve = server(port);
		serve.run();
		return EXIT_SUCCESS;
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
}
