#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include "../connection/connection.h"
#include "client.h"
#include <stdlib.h>

Connection* connect_to_server(char* addr, int port){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in* dest = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
    
    bzero(dest, sizeof(*dest));
    dest->sin_family = AF_INET;
    dest->sin_port = htons(port);
    inet_aton(addr, &dest->sin_addr);
    
    connect(s, (struct sockaddr*) dest, sizeof(*dest));
    
    return create_connection(s, dest);
    
}