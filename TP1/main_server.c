/*
 * File:   main_server.c
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

    Server* server = create_server(9998);

    listen_port(server);
    Connection* con = accept_connection(server);

    char dump[20];

    receive_data(con, dump, 20);

    printf("%s\n", dump);

    scanf("%s", dump);

    shutdown_server(server);

    return 0;
}
