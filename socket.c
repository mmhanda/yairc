/*  ************************************************************************* */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    socket.c                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: archid <archid-@1337.student.ma>           +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/02/25 05:34:06 by archid            #+#    #+#            */
/*   Updated: 2023/03/07 22:36:17 by archid           ###   ########.fr       */
/*                                                                            */
/*  ************************************************************************* */

#include "socket.h"

static void socket_init_addr(const char *host, int port, struct sockaddr *sock_addr) {
	struct sockaddr_in *addr = (struct sockaddr_in *)sock_addr;

	bzero(addr->sin_zero, sizeof(addr->sin_zero)); // set padding
	addr->sin_family = AF_INET;										 // address family
	addr->sin_port = htons(port);									 // address port
	addr->sin_addr.s_addr = host									 // host address
		? inet_addr(host) : htonl(INADDR_ANY);
	if (addr->sin_addr.s_addr < 0) {
		print_error();
		exit(EXIT_FAILURE);
	}

	printf("> the port from socket %d\n", ntohs(addr->sin_port));

	char host_addr[ADDR_SIZE];
	strncpy(host_addr, inet_ntoa(addr->sin_addr), sizeof(host_addr));
	printf("> the host addr from socket %s\n", host_addr);
}

static int socket_init(int domain, int type) {
	int sock_fd = socket(domain, type, 0);
	if (sock_fd < 0) {
		print_error();
		exit(EXIT_FAILURE);
	}

	int yes = 1; // set socket option to reuse the port
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
		close(sock_fd);
		print_error();
		exit(EXIT_FAILURE);
	}

	//fcntl(sock_fd, F_SETFL, O_NONBLOCK);

	struct pollfd *current = &fds[n_fds++];

	current->fd = sock_fd;
	current->events = POLLIN;
	return sock_fd;
}

static void socket_bind(int sock_fd, struct sockaddr *addr) {
	if (bind(sock_fd, addr, sizeof(struct sockaddr)) < 0) {
		close(sock_fd);
		print_error();
		exit(EXIT_FAILURE);
	}
}

int socket_create(const char *host, int port, struct sockaddr *addr) {
	socket_init_addr(host, port, addr);

	int sock_fd = socket_init(PF_INET, SOCK_STREAM);
	socket_bind(sock_fd, addr);
	fcntl(sock_fd, O_NONBLOCK);

	return sock_fd;
}

void socket_destroy() {
	server_destroy_session(session_fd);
	close(sock_fd);
}
