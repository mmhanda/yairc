// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   socket.c                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid <archid-@1337.student.ma>           +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2023/02/25 05:34:06 by archid            #+#    #+#             //
/*   Updated: 2023/03/03 11:51:03 by archid           ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

// /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

#include "socket.h"

int port = 8881;

#ifdef STATIC_ADDRESS
char *host = "192.168.0.1";
#endif

void socket_init_addr(struct sockaddr *sock_addr) {
  struct sockaddr_in *addr = (struct sockaddr_in *)sock_addr;

  bzero(addr->sin_zero, sizeof(addr->sin_zero)); // set padding
  addr->sin_family = AF_INET;                    // address family
  addr->sin_port = htons(port);                  // address port
#ifdef STATIC_ADDRESS
  addr->sin_addr.s_addr = inet_addr(host); // host address
#else
  addr->sin_addr.s_addr = htonl(INADDR_ANY); // deduce host address
#endif
  if (addr->sin_addr.s_addr < 0) {
    print_error();
    exit(EXIT_FAILURE);
  }

  printf("> the port from socket %d\n", ntohs(addr->sin_port));

  char host_addr[ADDR_SIZE];
  strncpy(host_addr, inet_ntoa(addr->sin_addr), sizeof(host_addr));
  printf("> the host addr from socket %s\n", host_addr);
}

int socket_init(int domain, int mode) {
  int sock_fd = socket(domain, mode, 0);
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

  return sock_fd;
}

#ifdef SERVER

void socket_bind(int sock_fd, struct sockaddr *addr) {
  if (bind(sock_fd, addr, sizeof(struct sockaddr)) < 0) {
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }
}

void server_connect(int sock_fd, struct sockaddr *addr) {
  if (connect(sock_fd, addr, sizeof(struct sockaddr)) < 0) {
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }

}

int server_start_session(int sock_fd, struct sockaddr *addr) {
  socklen_t addrlen;
  int session_fd = accept(sock_fd, addr, &addrlen);
  if (session_fd < 0) {
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }
  return session_fd;
}

ssize_t server_recieve_data(int session_fd, int sock_fd, int8_t *buff, size_t buff_size) {
  ssize_t n_bytes = recv(session_fd, buff, buff_size, 0);
  if (n_bytes < 0) {
    close(session_fd);
    close(sock_fd);
    print_error();
    exit(EXIT_FAILURE);
  }
  return n_bytes;
}

#else

ssize_t client_send_data(int sock_fd, int8_t *buff, size_t buff_size) {
  ssize_t n_bytes = send(sock_fd, buff, buff_size, 0);
  if (n_bytes < 0) {
    print_error();
    close(sock_fd);
    exit(EXIT_FAILURE);
  }
  return n_bytes;
}

#endif

int main(int argc, char *argv[]) {
  struct sockaddr addr; // internet socket address
  socket_init_addr(&addr);

  int sock_fd = socket_init(PF_INET, SOCK_STREAM);
  socket_bind(sock_fd, &addr);

  int8_t buff[BUFF_SIZE];
#ifdef SERVER

  server_connect(sock_fd, &addr);
  int session_fd = server_start_session(sock_fd, &addr);
  server_recieve_data(session_fd, sock_fd, buff, sizeof(buff));
  close(session_fd);

#else

  strncpy((char *)buff, argv[1], sizeof(buff));
  client_send_data(sock_fd, buff, sizeof(buff));

#endif

  close(sock_fd);

  return 0;
}
