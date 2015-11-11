#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "connection.h"
typedef struct Connection Connection;

struct Connection{
    int socket;
    struct sockaddr_in6* addr;
};

Connection* create_connection(int sock_id, struct sockaddr_in6* addr){
    Connection* con = (Connection*) malloc(sizeof(Connection));
    con->socket = sock_id;
    con->addr = addr;
    return con;
}

void receive_data(Connection* con, char* buffer, int buffer_size){
    read(con->socket, buffer, buffer_size);
}

void send_data(Connection* con, char* buffer, int buffer_size){
    write(con->socket, buffer, buffer_size);
}

int close_connection(Connection* con){
    int status = close(con->socket);
    free(con->addr);
    free(con);
    return status;
}

void get_connection_address(Connection* con, char* dest){
    inet_ntop(AF_INET6, &con->addr->sin6_addr, dest, INET6_ADDRSTRLEN);
}
