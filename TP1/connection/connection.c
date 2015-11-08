#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#include "connection.h"
typedef struct Connection Connection;

struct Connection{
    int socket;
    struct sockaddr_in* addr;
};

Connection* create_connection(int sock_id, struct sockaddr_in* addr){
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
