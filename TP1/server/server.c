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
    struct sockaddr_in addr;
};


Server* create_server(int port){
    Server* server = (Server*) malloc(sizeof(Server));

    bzero(&(server->addr), sizeof(Server));
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(port);

    server->socket = socket(AF_INET, SOCK_STREAM, 0);

    bind(server->socket, (struct sockaddr*)&(server->addr), sizeof(server->addr));

    return server;
}

int listen_port(Server* server){
    return listen(server->socket, 5);
}

Connection* accept_connection(Server* server){
    struct sockaddr_in* client_addr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
    int len = sizeof(struct sockaddr_in);
    int client_socket = accept(server->socket, (struct sockaddr*) client_addr, (socklen_t*)&len);

    printf("CONNECTED: %s\n", inet_ntoa(client_addr->sin_addr));

    return create_connection(client_socket, client_addr);
}

int shutdown_server(Server* server){
    int status = close(server->socket);
    free(server);
    return status;
}
