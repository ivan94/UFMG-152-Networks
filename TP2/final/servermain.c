/*
 * File:   servermain.c
 * Author: ivan
 *
 * Created on December 10, 2015, 6:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "socket.h"
#include "server.h"

/*
 *
 */
int main(int argc, char** argv) {

    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Socket s = create_socket();
    if(bind_socket(s, atoi(argv[1]))){
        printf("%s\n", strerror(errno));
        return 0;
    }

    Server* serv = create_server();

    //start listening
    while(1){
        char clientaddr[100];
        char buffer[2000];
        int port;

        receive_message(s, buffer, clientaddr, 100, &port);

        printf("Received <%s:%d> => %s", clientaddr, port, buffer);

        if(process_request(serv, s, buffer, clientaddr, port)){
            send_message(s, clientaddr, port, "ERROR invalid command\n");
        }

    }

    return (EXIT_SUCCESS);
}
