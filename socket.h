/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:40:25 by archid            #+#    #+#             */
/*   Updated: 2023/03/03 16:27:32 by archid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>  // dprintf
#include <stdlib.h> // exit

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

#define ADDR_SIZE 32
#define BUFF_SIZE 256

#define print_error() printf("%d %s\n", perror(__FUNCTION__)

#ifdef __cplusplus
extern "C" {
#endif
int socket_create(const char *host, int port, struct sockaddr *addr);

int server_start_session(int sock_fd, struct sockaddr *addr);
#define server_destroy_session(fd) close(fd)

ssize_t server_recieve_data(int session_fd, int sock_fd, int8_t *buff, size_t buff_size);
ssize_t client_send_data(int sock_fd, int8_t *buff, size_t buff_size);
#ifdef __cplusplus
}
#endif
