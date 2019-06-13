#include "unp.h"
// header contain numerous system headers that are needed by most network programs and
// defines various constants that we use

int
main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr; // call the sockaddr_in structure

    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");

    // call to socket function which create an internet(AF_INET) stream(SOCK_STREAM) socket for TCP socket
    // function returns a small integer descriptor that we can use to identify the socket in all future function calls
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error"); // print error msg with description of system error that occurred & terminate process

    // fill in sockaddr_in structure named serveraddr with server ip addr & port number, use bzero set entire structure to 0 
    bzero(&servaddr, sizeof(servaddr));
    //  set adddress family to AF_INET & port number to 13
    servaddr.sin_family = AF_INET;
    // hton(host to network short) to convert binary port number 
    servaddr.sin_port = htons(13);

    // inet_pton(presentation to numeric) convert ASCII command-line arg int proper format (such as 206.62.226.35)
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        /* daytime server */
        err_quit("inet_pton error for %s", argv[1]); // return error 

    // connect function applied to a TCP socket, 
    // establishes a TCP connection with the server specified by the socket address structure pointed to by the second argument
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    // In the unp.h header, we #define SA to be struct sockaddr, that is, a generic socket address structure.
    // Everytime one of the socket functions requires a pointer to a socket address structure, that pointer must be cast to a pointer to a generic socket address structure.

    // read the server's reply and display the result using the standard I/O fputs function
    // The server's reply is normally a 26-byte string of the form    "Mon May 26 20 : 58 : 40 2003\r\n"
    // \r is the ASCII carriage return and \n is the ASCII linefeed
    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        /* null terminate */
        err_sys("read error");
    exit(0);
}

// get 