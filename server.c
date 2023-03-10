/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:36:28 by archid            #+#    #+#             */
/*   Updated: 2023/03/10 01:40:38 by archid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

#include "socket.h"

#define MAX_SERVER_CONNECTIONS 16


static struct pollfd fds[MAX_SERVER_CONNECTIONS];

static int server_start_session(int sock_fd, struct sockaddr *addr)
{
	if (listen(sock_fd, MAX_SERVER_CONNECTIONS) < 0)
		server_destroy();

	socklen_t addrlen;
	int session_fd = accept(sock_fd, addr, &addrlen);
	if (session_fd < 0)
		server_destroy();

	pollfd->fd = session_fd;
	pollfd->events = POLLIN;

	return session_fd;
}

static void server_create()
{
	struct sockaddr addr;

	sock_fd = socket_create(NULL, 8881, &addr);
	printf("%d socket created\n", sock_fd);
	session_fd = server_start_session(sock_fd, &addr);


	printf("%d session created\n", session_fd);
}

static void server_destroy()
{
	if (session_fd > 0)
		close(session_fd);
	if (sock_fd > 0)
		close(sock_fd);
	if (session_fd < 0 || sock_fd < 0) {
		print_error();
		exit(EXIT_FAILURE);
	}
}

static char buff[sizeof(fds)][BUFF_SIZE + 1];
static ssize_t n_bytes[sizeof(fds)];

static void server_recieve_data(int session_fd, int sock_fd)
{
	memset(n_bytes, -1, sizeof(ssize_t) * sizeof(fds));

	for(unsigned i = 0; i < sizeof(fds); ++i) {
		if (n_bytes[i] != 0) {
		  n_bytes[i] = recv(session_fd, buff[i], sizeof(buff[i]), 0);
			if (n_bytes[i] < 0)
				server_destroy();
		}
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, server_destroy);
	signal(SIGKILL, server_destroy);

	struct server server;
	server_create(&server);


	for (ssize_t n_bytes = -1; n_bytes != 0; puts((char *)buff)) {
		server_recieve_data(session_fd, sock_fd);
		printf("recieved %ld Bytes\n", n_bytes);
		buff[n_bytes] = '\0';
	}



	server_destroy();

	return 0;
}
