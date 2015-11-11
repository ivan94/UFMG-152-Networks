/*
 * File:   main_server.c
 * Author: ivan
 *
 * Created on November 3, 2015, 10:59 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server/server.h"
#include "connection/connection.h"
#include "protocol.h"

/*
 *
 */

/**
 * Waits for a greet message to arrive
 * @param con The connection pointer
 */
void receive_greet(Connection* con){
    char buffer[MAX_MSG];
    buffer[0] = '\0';

    while(strcmp(buffer, GREET_MSG) != 0){
        receive_data(con, buffer, MAX_MSG);
    }
}

/**
 * Send an acknowledgement of a received message
 * @param con The connection pointer
 */
void send_ack(Connection* con) {
    send_data(con, ACK, ACK_LEN);
}

/**
 * Send acknowledgement of a greet message
 * @param con The connection pointer
 */
void send_greet_ack(Connection* con){
    send_data(con, GREET_ACK, GREET_ACK_LEN);
}

/**
 * Receive a message sent from the client. It handles character stuffing
 * @param  con  The connection pointer
 * @param  dest The buffer where the message will be stored
 * @return      Return true if is a normal message and false if is a farewell message
 */
int receive_msg(Connection* con, char* dest){
    char buffer[MAX_MSG];
    buffer[0] = '\0';

    receive_data(con, buffer, MAX_MSG);

    //For handles character stuffing
    //State represents the position of the FAREWELL message that was read
    //If it gets to the last character of the FAREWELL message and no character was stuffed
    //then it is and actual farewell message
    int i;
    int state = 0, stuffed = 0;
    for(i = 0; buffer[i+stuffed] != '\0'; i++){
        if(state == (strlen(FAREWELL)-1) && buffer[i+stuffed] == STUFF_CHAR){
            stuffed++;
            state = 0;
        }else if(state == (strlen(FAREWELL)-1)){
            return 0;
        }
        if(buffer[i+stuffed] == FAREWELL[state]){
            state++;
        }else{
            state=0;
        }
        dest[i] = buffer[i+stuffed];
    }
    dest[i] = '\0';

    return 1;
}

int main(int argc, char** argv) {

    int port = atoi(argv[1]);

    Server* server = create_server(port);

    listen_port(server);

    Connection* con = accept_connection(server);

    char client_addr[50];
    get_connection_address(con, client_addr);

    printf("CLIENT %s CONNECTED\n", client_addr);

    receive_greet(con);
    send_greet_ack(con);

    char buffer[MAX_MSG];
    receive_msg(con, buffer);
    send_ack(con);

    char filename[MAX_MSG];
    strcpy(filename, client_addr);
    strcat(filename, buffer);

    int i;
    for(i = 0; filename[i] != '\0'; i++){
        filename[i] = filename[i] == '/'? '.': filename[i];
    }

    char filebuffer[MAX_MSG];

    receive_msg(con, filebuffer);
    send_ack(con);

    // char* filebuffer = (char*) malloc(sizeof(char)*1000);
    // int filebuffer_size = 1000;
    // filebuffer[0] = '\0';
    //
    // int usedbuffer = 0;
    //
    // while(receive_msg(con, buffer)){
    //     usedbuffer += strlen(buffer)+2;
    //     if(usedbuffer > filebuffer_size){
    //         filebuffer_size *= 2;
    //         filebuffer = (char*) realloc(filebuffer, sizeof(char)*filebuffer_size);
    //     }
    //     sprintf(filebuffer, "%s%s\n", filebuffer, buffer);
    //     send_ack(con);
    // }
    //

    char b[30];
    if(receive_msg(con, b)){
        printf("Protocol error: Expecting farewell message\n");
    }

    shutdown_server(server);

    FILE* f = fopen(filename, "w");
    fprintf(f, "%s", filebuffer);
    fclose(f);

    //free(filebuffer);


    return 0;
}
