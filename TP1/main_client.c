/*
 * File:   main_client.c
 * Author: ivan
 *
 * Created on November 8, 2015, 4:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "client/client.h"
#include "connection/connection.h"

/*
 *
 */
int main(int argc, char** argv) {

    Connection* con = connect_to_server("127.0.0.1", 9998);

    if(con == NULL){
        printf("failed\n");
        return 1;
    }

    send_data(con, "Hey Grakks!", 11);

    char dump[5];

    scanf("%s", dump);

    int s = close_connection(con);

    printf("%d\n", s);

    return 0;
}
