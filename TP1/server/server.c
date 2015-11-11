#include "../connection/connection.h"
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct Server Server;
struct Server{
    int socket;
    struct sockaddr_in6 addr;
};


Server* create_server(int port){
    Server* server = (Server*) malloc(sizeof(Server));

    bzero(server, sizeof(Server));
    server->addr.sin6_addr = in6addr_any;
    server->addr.sin6_family = AF_INET6;
    server->addr.sin6_port = htons(port);

    server->socket = socket(AF_INET6, SOCK_STREAM, 0);

    bind(server->socket, (struct sockaddr*)&(server->addr), sizeof(server->addr));

    return server;
}

int listen_port(Server* server){
    return listen(server->socket, 5);
}

Connection* accept_connection(Server* server){
    struct sockaddr_in6* client_addr = (struct sockaddr_in6*) malloc(sizeof(struct sockaddr_in6));
    int len = sizeof(struct sockaddr_in6);
    int client_socket = accept(server->socket, (struct sockaddr*) client_addr, (socklen_t*)&len);

    return create_connection(client_socket, client_addr);
}

int shutdown_server(Server* server){
    int status = close(server->socket);
    free(server);
    return status;
}
