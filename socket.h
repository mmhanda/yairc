/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:40:25 by archid            #+#    #+#             */
/*   Updated: 2023/03/07 22:34:51 by archid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string.h>
#include <stdio.h>  // dprintf
#include <stdlib.h> // exit
#include <stdbool.h>

#include <memory.h> // bzero
#include <unistd.h> // STDERR_FILENO
#include <assert.h>
#include <errno.h>  // perror

#include <arpa/inet.h> // inet_addr
#include <netdb.h>
#include <netinet/in.h> // struct sockaddr_in, htons
#include <sys/socket.h> // struct sockaddr, AF_INET, PF_INET

#include <poll.h>
#include <fcntl.h>
#include <signal.h>

#define ADDR_SIZE 32
#define BUFF_SIZE 256

#define print_error() ("%d: %s\n", errno, strerror(errno))

#ifdef __cplusplus
extern "C" {
#endif

  int socket_create(const char *host, int port, struct sockaddr *addr);
	void socket_destroy();

  extern int sock_fd, session_fd;

#ifdef __cplusplus
}
#endif
