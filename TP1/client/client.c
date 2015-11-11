#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include "../connection/connection.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Connection* connect_to_server(char* addr, int port){
    int s = socket(AF_INET6, SOCK_STREAM, 0);
    struct sockaddr_in6* dest = (struct sockaddr_in6*) malloc(sizeof(struct sockaddr_in6));

    bzero(dest, sizeof(*dest));
    dest->sin6_family = AF_INET6;
    dest->sin6_port = htons(port);

    //Treat non ipv6 address
    //First try to convert the address as received to network bytes format
    //If fail it assumes that the address is in IPv4 format and append a preffix to make it compatible to IPv6
    //Try to convert again the new address to network byte format
    //If fails again the address is not in a supported format
    if(!inet_pton(AF_INET6, addr, &dest->sin6_addr)){
        char* preffix = "::ffff:";
        char ipv6[strlen(preffix)+strlen(addr)+1];

        strcpy(ipv6, preffix);
        strcat(ipv6, addr);
        printf("%s\n", ipv6);
        if(!inet_pton(AF_INET6, ipv6, &dest->sin6_addr)){
            return NULL;
        }
    }

    int status = connect(s, (struct sockaddr*) dest, sizeof(*dest));

    return status == 0?create_connection(s, dest):NULL;

}
