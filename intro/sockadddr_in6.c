

struct in6_addr {
uint8_t s6_addr[16];
/* 128-bit IPv6 address */
/* network byte ordered */
};

#define SIN6_LEN
/* required for compile-time tests */

struct sockaddr_in6 {
uint8_t sin6_len;   /* length of this struct (28) */

sa_family_t sin6_family;    /* AF_INET6 */
in_port_t sin6_port;    /* transport layer port# */
                        /* network byte ordered */

uint32_t    sin6_flowinfo; /* flow information, undefined */
                            // low-order 20 bits are the flow label
                            // high-order 12 bits are reserved

struct in6_addr sin6_addr;  /* IPv6 address */
                            /* network byte ordered */

uint32_t    sin6_scope_id; /* set of interfaces for a scope */
// identifies the scope zone in which a scoped address is meaningful, most commonly an interface index for a link-local address
};


struct sockaddr_storage {
    uint8_t ss_len; /* length of this struct (implementation dependent) */

    sa_family_t ss_family;  /* address family: AF_xxx value */
    /* implementation-dependent elements to provide:
    * a) alignment sufficient to fulfill the alignment requirements of
    *
    all socket address types that the system supports.
    * b) enough storage to hold any type of socket address that the
    *
    system supports.
    */
};
