/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:36:28 by archid            #+#    #+#             */
/*   Updated: 2023/03/07 22:40:32 by archid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

#include "socket.h"

#define MAX_CONNECTIONS 16

#define server_destroy_session(fd) close(fd)

static struct pollfd fds[MAX_CONNECTIONS];

static int server_start_session(int sock_fd, struct sockaddr *addr) {
	if (listen(sock_fd, 1) < 0) {
		close(sock_fd);
		print_error();
		exit(EXIT_FAILURE);
	}

	socklen_t addrlen;
	int session_fd = accept(sock_fd, addr, &addrlen);
	if (session_fd < 0) {
		close(sock_fd);
		print_error();
		exit(EXIT_FAILURE);
	}

	return session_fd;
}

static ssize_t n_bytes[sizeof(fds)];
static void server_recieve_data(int session_fd, int sock_fd,
														int8_t *buff, size_t buff_size) {
	for(unsigned i = 0; i < sizeof(fds); ++i) {
		n_bytes[i] = recv(session_fd, buff, buff_size, 0);
		if (n_bytes < 0) {
			close(session_fd);
			close(sock_fd);
			print_error();
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, socket_destroy);
	signal(SIGKILL, socket_destroy);

	int8_t buff[BUFF_SIZE + 1];
	struct sockaddr addr;

	sock_fd = socket_create(NULL, 8881, &addr);
	printf("%d socket created\n", sock_fd);
	session_fd = server_start_session(sock_fd, &addr);
	printf("%d session created\n", session_fd);

	for (ssize_t n_bytes = -1; n_bytes != 0; puts((char *)buff)) {
		n_bytes = server_recieve_data(session_fd, sock_fd, buff, sizeof(buff));
		printf("recieved %ld Bytes\n", n_bytes);
		buff[n_bytes] = '\0';
	}



	socket_destroy();

	return 0;
}

int sock_fd, session_fd;
