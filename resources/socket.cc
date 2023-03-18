// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   socket.c                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 05:34:06 by archid            #+#    #+#             //
//   Updated: 2023/02/26 06:57:33 by archid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

#include <memory.h>				// bzero
#include <stdlib.h>				// exit
#include <stdio.h>				// dprintf
#include <unistd.h>				// STDERR_FILENO

#include <netinet/in.h>			// struct sockaddr_in, htons
#include <arpa/inet.h>			// inet_addr
#include <sys/socket.h>			// struct sockaddr, AF_INET, PF_INET
#include <errno.h>

static int		port = 0x0584;
static char		*host_addr = "10.12.5.8";

static void socket_tcp(struct sockaddr_in *in)
{
	// created socket file
	int sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		perror("setting host address failed");
		exit(EXIT_FAILURE);
	}
}

static void socket_init_addr(struct sockaddr_in *addr)
{
	// socket initialisation
	bzero(addr->sin_zero, sizeof(addr->sin_zero));   // set padding
	addr->sin_family = AF_INET;					   // address family
	addr->sin_port = htons(port);				   // address port
	addr->sin_addr.s_addr = inet_addr(host_addr);   // host address
	if (addr->sin_addr.s_addr < 0) {
		dprintf(STDERR_FILENO,
				"could not set host address to value %s\n", host_addr);
		perror("setting host address failed");
		exit(EXIT_FAILURE);
	}

	printf("> the port from socket %d\n", ntohs(addr->sin_port));

	char host[32];
	strncpy(host_addr, inet_ntoa(addr->sin_addr), sizeof(host));
	printf("> the host addr from socket %s\n", host);
}

static void socket_udp(struct sockaddr_in *in)
{
}

int			main()
{
	printf("> PORT=%d HOST=%s\n", port, host_addr);

	struct sockaddr addr; // internet socket address
	socket_init_addr((struct sockaddr_in *)&addr);
	socket_tcp((struct sockaddr_in *)&addr);
	socket_udp((struct sockaddr_in *)&addr);
	return 0;
}
