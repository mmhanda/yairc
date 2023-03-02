/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:40:25 by archid            #+#    #+#             */
/*   Updated: 2023/03/03 11:48:22 by archid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>  // dprintf
#include <stdlib.h> // exit

#include <memory.h> // bzero
#include <unistd.h> // STDERR_FILENO
#include <errno.h>  // perror

#include <arpa/inet.h> // inet_addr
#include <netdb.h>

#include <netinet/in.h> // struct sockaddr_in, htons

#include <sys/socket.h> // struct sockaddr, AF_INET, PF_INET

#define ADDR_SIZE 32
#define BUFF_SIZE 256

#define print_error() perror(__FUNCTION__)


int socket_init(int domain, int mode);
void socket_init_addr(struct sockaddr *sock_addr);

void socket_bind(int sock_fd, struct sockaddr *addr);
void server_connect(int sock_fd, struct sockaddr *addr);
int server_start_session(int sock_fd, struct sockaddr *addr);
ssize_t server_recieve_data(int session_fd, int sock_fd, int8_t *buff, size_t buff_size);
ssize_t client_send_data(int sock_fd, int8_t *buff, size_t buff_size);
