#include "server.hpp"

void handler(int) {
    ircserv.terminate();
    exit(0);
}

server ircserv;

server& server::operator = (const server &copyfrom) {

    if (this != &copyfrom) {
        this->sock_fd_ = copyfrom.sock_fd_;
        this->clients_ = copyfrom.clients_;
        this->passwd_ = copyfrom.passwd_;
        this->addr_ = copyfrom.addr_;
    }

    return (*this);
}

int main(int argc, char *argv[]) {
    int port;
    std::string passwd = "abc";

    signal(SIGINT, handler);

    if (checker(argc, argv , port) == 0)
        return (0);
    try {
        server tmpserv;
        tmpserv = server(port, passwd.c_str());
        ircserv = tmpserv;
        tmpserv.~server();
        ircserv.run();
        return EXIT_SUCCESS;
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

