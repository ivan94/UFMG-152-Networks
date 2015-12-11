#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#include "socket.h"

char* ACK = "ACK";
int TIMEOUT_LIMIT = 30;
int TIMEOUT_INIT = 1;
int MAX_MSG_SIZE = 2000;

Socket create_socket(){
    int sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sockfd < 0)
        printf("ERROR opening socket\n");

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
        (const void *)&optval , sizeof(int));

    return (Socket) sockfd;
}

int bind_socket(Socket socket, int port){
    struct sockaddr_in6 serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin6_addr = in6addr_any;
    serveraddr.sin6_family = AF_INET6;
    serveraddr.sin6_port = htons(port);

    if(bind((int)socket, (struct sockaddr*)&serveraddr, sizeof(serveraddr))){
        printf("ERROR on binding\n");
        return -1;
    }
    return 0;
}

int send_message(Socket socket, char* to, int port, char* msg){
    struct addrinfo hints;
    struct addrinfo* result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    char port_s[6];
    sprintf(port_s, "%d", port);

    int s = getaddrinfo(to, port_s, &hints, &result);
    if(s == -1){
        printf("Invalid server address");
        return -1;
    }
    struct addrinfo* rp;
    for(rp = result; rp != NULL; rp = result->ai_next){
        int bytes_sent = sendto((int) socket, msg, strlen(msg)+1, 0, rp->ai_addr, rp->ai_addrlen);
        if(bytes_sent != -1){
            break;
        }
    }
    if(rp == NULL){
        printf("Invalid server address");
        return -1;
    }
    //Awaits for response
    int timeout = TIMEOUT_INIT;
    while(1){
        //set timeout for receive for 1 sec;
        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

        //waits for ack
        struct sockaddr_in6 addr;
        int len = sizeof(struct sockaddr_in6);
        int buffer_size = 10;
        char buffer[buffer_size];
        bzero(buffer, buffer_size);

        recvfrom((int)socket, buffer, buffer_size, 0, (struct sockaddr*)&addr, (socklen_t*)&len);

        int cmp = strcmp(buffer, ACK);
        if(cmp == 0){
            return 0;
        }
        if(timeout > TIMEOUT_LIMIT){
            printf("MSG sending timeout, please check server status");
            return -1;
        }
        timeout *= 2;
    }
}

int receive_message(Socket socket, char* buf, char* from, int from_buf_size, int* fromport){
    //remove timeout for receiving messages
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

    struct sockaddr_in6 addr;
    int len = sizeof(addr);

    int b = recvfrom((int)socket, buf, MAX_MSG_SIZE, 0, (struct sockaddr*)&addr, (socklen_t*)&len);
    if(b == -1){
        printf("Failed to receive a message");
        return -1;
    }

    b = sendto((int)socket, ACK, 4, 0, (struct sockaddr*)&addr, (socklen_t) len);
    if(b == -1){
        printf("Failed to send ack");
        return -1;
    }

    char fromport_s[10];
    getnameinfo((struct sockaddr*)&addr, (socklen_t)len, from, from_buf_size, fromport_s, sizeof(fromport_s), NI_DGRAM | NI_NUMERICHOST | NI_NUMERICSERV);

    *fromport = atoi(fromport_s);

    return 0;
}

int close_socket(Socket socket){
    return close(socket);
}
