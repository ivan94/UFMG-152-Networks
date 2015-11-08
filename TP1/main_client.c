/*
 * File:   main_client.c
 * Author: ivan
 *
 * Created on November 8, 2015, 4:37 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "client/client.h"

/*
 *
 */
int main(int argc, char** argv) {

    Connection* con = connect_to_server("52.10.163.167", 9998);

    char dump[5];

    scanf("%s", dump);

    close_connection(con);
}
