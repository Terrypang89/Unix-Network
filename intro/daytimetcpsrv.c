#include "unp.h".
#include <time.h>

int
main(int argc, char **argv)
{
    int
    listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    // create internet stream socket
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // fill in sockaddr_in structure named serveraddr with server ip addr & port number, use bzero set entire structure to 0 
    bzeros(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // specify ip addrs as INADDR_ANY which allows the server to accept a client connection on any interface
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // hton(host to network short) to convert binary port number 
    servaddr.sin_port = htons(13); /* daytime server */

    // server's well-known port (13 for the daytime service) is bound to the socket
    // by filling in an Internet socket address structure and calling bind
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // calling listen, the socket is converted into a listening socket, 
    // on which incoming connections from clients will be accepted by the kernel
    Listen(listenfd, LISTENQ);

    //  constant LISTENQ is from our unp.h header. 
    //  It specifies the maximum number of client connections that the kernel will queue for this listening descriptor.

    for ( ; ; ) {
        // the server process is put to sleep in the call to accept, 
        // waiting for a client connection to arrive and be accepted.
        connfd = Accept(listenfd, (SA *) NULL, NULL);
        // Accept return value from the function is a new descriptor (connfd)
        // that is called the connected descriptor. 
        // This new descriptor is used for communication with the new client.

        // current time and date are returned by the library function time
        ticks = time(NULL);

        // ctime, converts this integer value into a human-readable string such as Mon May 26 20:58:40 2003
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        // A carriage return and linefeed are appended to the string by snprintf, 
        // the result is written to the client by write
        Write(connfd, buff, strlen(buff));

        // server closes its connection with the client by calling close
        Close(connfd);
    }
}