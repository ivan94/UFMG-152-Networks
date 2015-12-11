/*
 * File:   main.c
 * Author: ivan
 *
 * Created on December 10, 2015, 5:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#include "socket/socket.h"
#include "client/client.h"

/*
 *
 */

int main(int argc, char** argv) {
    if(argc != 4){
        printf("Usage: %s <ip/name> <port> <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Socket s = create_socket();
    
    fd_set set;
    
    if(register_user(s, argv[1], atof(argv[2]), argv[3])){
        return EXIT_FAILURE;
    }
    
    printf("Digite a mensagem a ser enviada, ou /help para listar os comandos\n");
    
    char buffer[2000];
    char from[50];
    int port;
    
    while(1){
        bzero(buffer, 2000);
        bzero(from, 50);
        
        FD_ZERO(&set);
        FD_SET(s, &set);
        FD_SET(STDIN_FILENO, &set);
        
        select(FD_SETSIZE, &set, NULL, NULL, NULL);
        
        if(FD_ISSET(s, &set)){
            receive_message(s, buffer, from, 100, &port);
            process_received_msg(buffer);
        }else if(FD_ISSET(STDIN_FILENO, &set)){
            fgets(buffer, 2000, stdin);
            if(!process_user_input(s, argv[1], atoi(argv[2]), buffer)){
                break;
            }
        }
    }


    return (EXIT_SUCCESS);
}
