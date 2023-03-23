# Yet Another Internet Relay Chat

# Networking API

All networking API function are considered equivalent to system calls
such as `read`{.verbatim} or `write`{.verbatim}, they lay in man(2).

``` c
#define INADDR_ANY              (u_int32_t)0x00000000

in_addr_t inet_addr(const char *cp);

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

int socket(int domain, int type, int protocol);
int bind(int sock_fd, struct sockaddr *addr, socklen_t addr_size);

int listen(int socket, int backlog);
int connect(int socket, const struct sockaddr *address, socklen_t address_len);

ssize_t send(int socket, const void *buffer, size_t length, int flags);
ssize_t recv(int socket, void *buffer, size_t length, int flags);
```

## `socket()`{.verbatim} and `struct sockaddr`{.verbatim}

When `socket()`{.verbatim} is created, which is just allocating a file
resource in the OS, by specifiying the protocol family and type, and
which mode of transmission i.e. UDP or TCP. It requires additional
information on the address itself, namelty the host and the port, which
both should be in machine encoding i.e. same behaviour as
`hton()`{.verbatim}.

-   Except that `inet_addr()`{.verbatim} returns the address in machine
    encoding already

> As a legacy, there are two types `struct sockaddr`{.verbatim} and
> `struct sockaddr_in`{.verbatim}, they represent the same information,
> but the later is more convenient to work with.

At last, both the socket and the address are entangeled using
`bind()`{.verbatim}

## `listen()`{.verbatim}, `accept()`{.verbatim} and `poll()`{.verbatim} multiple clients

When getting a socket for the server, we may `listen()`{.verbatim} for
incoming connections. Each new connection is a new `socket()`{.verbatim}
associated with a client, that is created after calling
`accept()`{.verbatim}.

However, `listen()`{.verbatim} runs asynchronously,
`accept()`{.verbatim} should be called for as many clients that ahve
sent the request. Yet, it blocks e.g. same as waiting for IO. Thus if no
new request has been sent, `accept()`{.verbatim} will await and blocks
the process.

This can be resolved using multitasking, by telling the OS to not block
using `fcntl()`{.verbatim} to alter the flags of the socket file. And
then use `poll()`{.verbatim} to fetch only the ones that are ready to be
fetched. By setting event `POLLIN`{.verbatim} on creation, the OS would
set flags in return when it is unblocking. Now instead of blocking the
process, an `EWOULDBLOCK`{.verbatim} (or `EAGAIN`{.verbatim}) would be
raised, resolving the block.

## `recv()`{.verbatim} data

For each client that has sent, we may `recv()`{.verbatim} some data to
be put in a buffer, the length of the data is returned, and a closed
connection would return 0. However, the total length of the incoming
data may overfit the size of the buffer, thus it may require multiple
reads until it blocks by raising `errno`{.verbatim}.

## Sending Data

# Internet Relay Chat ([RFC1459](https://www.rfc-editor.org/rfc/rfc1459))

## Server

## Client

## Messages

Each IRC message may consist of up to three main parts that are separated by one or more spaces (`0x20`):

- prefix (optional) :: indicated with prefix colon `:` (`0x3b`), attached to the message
- command :: either be a valid IRC command or a 3 digits number as ASCII, and may have parameters
- command parameters :: (of which there may be up to 15)

IRC messages are always lines of characters terminated with a CR-LF (Carriage Return - Line Feed) pair, in ASCII (`0x0a 0x0d`). However, current implementation treats the appearance of either as the end of the message.

# References

-   [IRC Standard](https://www.rfc-editor.org/rfc/rfc1459)
-   [Using Freenode IRC
    Server](https://unicorn-utterances.com/posts/joining-freenode-irc)
-   [Beej\'s Guide to Network
    Programming](https://beej.us/guide/bgnet/html)
-   [DWise1\'s Sockets Programming
    Pages](http://dwise1.net/pgm/sockets/)
-   [Handling multiple users](http://www.kegel.com/c10k.html)

![visual_reference](https://user-images.githubusercontent.com/94152392/226868617-2b778553-9795-42b7-aa1d-ba27ec688cbd.png)

## Stackoverflow

-   [disable `recv`{.verbatim}
    blocking](https://stackoverflow.com/questions/36985793/blocking-recv-vs-fcntl)
-   [How to change a tcp socket to be non
    blocking](https://stackoverflow.com/questions/1543466/how-do-i-change-a-tcp-socket-to-be-non-blocking)
