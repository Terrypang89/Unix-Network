// Internet socket address structure
<netinet/in.h>

struct in_addr {
    in_addr_t s_addr;
    /* 32-bit IPv4 address */
    /* network byte ordered */
};

struct sockaddr_in {
    uint8_t sin_len;    /* length of structure (16) */

    sa_family_t sin_family; /* AF_INET */
    in_port_t sin_port;     /* 16-bit TCP or UDP port number */
                            /* network byte ordered */

    struct in_addr sin_addr;    /* 32-bit IPv4 address */
                                /* network byte ordered */

    char sin_zero[8];           /* unused */
};

// four socket functions that pass a socket address structure from the process to the kernel, 
// bind, connect, sendto, and sendmsg, all go through the sockargs function

// sockargs function copies the socket address structure from the process and 
// explicitly sets its sin_len member to the size of the structure that was passed as an argument to these four functions.

// The five socket functions that pass a socket address structure from the kernel to the process, 
// accept, recvfrom, recvmsg, getpeername, and getsockname, all set the sin_len member before returning to the process.

// POSIX specification requires only three members in the structure: sin_family, sin_addr, and sin_port.
// add the sin_zero member so that all socket address structures are at least 16 bytes in size.



struct sockaddr {
    uint8_t     sa_len;
    sa_family_t     sa_family;  /* address family: AF_xxx value */
    char    sa_data[14];    /* protocol-specific address */
};

int bind(int, struct sockaddr *, socklen_t);

struct sockaddr_in serv;
/* IPv4 socket address structure */

// pass by reference
bind(sockfd, (struct sockaddr *) &serv, sizeof(serv));

//Two other functions pass socket address structures: recvmsg and sendmsg