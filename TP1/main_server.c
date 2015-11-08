/* 
 * File:   main.c
 * Author: ivan
 *
 * Created on November 3, 2015, 10:59 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "server/server.h"
#include "connection/connection.h"

/*
 * 
 */
int main(int argc, char** argv) {

    Server* server = create_server(9889);
    
    int s = listen_port(server);
    
    int* c = (int*)accept_connection(server);
    
    char dump[5];
    
    scanf("%s", dump);
    
    shutdown_server(server);
}

