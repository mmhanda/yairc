/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:55:59 by archid            #+#    #+#             */
/*   Updated: 2023/03/10 01:40:38 by archid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.h"

static void socket_init_addr(const char *host, int port, struct sockaddr *sock_addr)
{
	struct sockaddr_in *addr = (struct sockaddr_in *)sock_addr;

	bzero(addr->sin_zero, sizeof(addr->sin_zero)); // set padding
	addr->sin_family = AF_INET;										 // address family
	addr->sin_port = htons(port);									 // address port
	addr->sin_addr.s_addr = host									 // host address
		? inet_addr(host) : htonl(INADDR_ANY);
	if (addr->sin_addr.s_addr < 0)
		server_destroy();

	printf("> the port from socket %d\n", ntohs(addr->sin_port));

	char host_addr[ADDR_SIZE];
	strncpy(host_addr, inet_ntoa(addr->sin_addr), sizeof(host_addr));
	printf("> the host addr from socket %s\n", host_addr);
}

static int socket_init(int domain, int type, struct pollfd *pollfd)
{
	int sock_fd = socket(domain, type, 0);
	if (sock_fd < 0)
		server_destroy();

	int yes = 1; // set socket option to reuse the port
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
		server_destroy();

	if (fcntl(sock_fd, F_SETFL, fcntl(sock_fd, F_GETFL, 0) | O_NONBLOCK) < 0)
	  server_destroy();

	return sock_fd;
}

static void socket_bind(int sock_fd, struct sockaddr *addr)
{
	if (bind(sock_fd, addr, sizeof(struct sockaddr)) < 0)
	  server_destroy();
}

int socket_create(const char *host, int port, struct sockaddr *addr, struct pollfd *pollfd)
{
	socket_init_addr(host, port, addr);

	int sock_fd = socket_init(PF_INET, SOCK_STREAM, pollfd);
	socket_bind(sock_fd, addr);

	return sock_fd;
}

int sock_fd, session_fd;
