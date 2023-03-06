// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   socket.c                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 05:34:06 by archid            #+#    #+#             //
/*   Updated: 2023/03/05 06:29:00 by archid           ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

// /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

#include "socket.h"

#define MAX_CONNECTIONS 16

unsigned n_fds = 0;
struct pollfd fds[MAX_CONNECTIONS];

static void socket_init_addr(const char *host, int port, struct sockaddr *sock_addr) {
  struct sockaddr_in *addr = (struct sockaddr_in *)sock_addr;

  bzero(addr->sin_zero, sizeof(addr->sin_zero)); // set padding
  addr->sin_family = AF_INET;                    // address family
  addr->sin_port = htons(port);                  // address port
  addr->sin_addr.s_addr = host			 // host address
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

  return sock_fd;
}

int server_start_session(int sock_fd, struct sockaddr *addr) {
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
  puts("//");

  return session_fd;
}

ssize_t server_recieve_data(int session_fd, int sock_fd,
			    int8_t *buff, size_t buff_size) {
  ssize_t n_bytes = recv(session_fd, buff, buff_size, 0);
  if (n_bytes < 0) {
    close(session_fd);
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }
  return n_bytes;
}

void client_start_session(int sock_fd, struct sockaddr *addr) {
  if (connect(sock_fd, addr, sizeof(struct sockaddr)) < 0) {
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }
}

ssize_t client_send_data(int sock_fd, int8_t *buff, size_t buff_size) {
  ssize_t n_bytes = send(sock_fd, buff, buff_size, 0);
  if (n_bytes < 0) {
    print_error();
    close(sock_fd);
    exit(EXIT_FAILURE);
  }
  return n_bytes;
}

int main(int argc, char *argv[]) {
  int8_t buff[BUFF_SIZE + 1];
  struct sockaddr addr;

  int sock_fd = socket_create(NULL, 8881, &addr);

#ifdef SERVER

  int session_fd = server_start_session(sock_fd, &addr);
  ssize_t n_bytes = server_recieve_data(session_fd, sock_fd, buff, sizeof(buff));
  buff[n_bytes] = '\0';
  puts((char *)buff);
  server_destroy_session(session_fd);

#else

  int yes = 1; // set socket option to reuse the port
  if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }

  strncpy((char *)buff, argv[1], sizeof(buff));
  client_start_session(sock_fd, &addr);
  client_send_data(sock_fd, buff, sizeof(buff));

#endif

  close(sock_fd);

#define SIZE 16


  return 0;
}
