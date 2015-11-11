/*
 * File:   main_client.c
 * Author: ivan
 *
 * Created on November 8, 2015, 4:37 PM
 */

#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "client/client.h"
#include "connection/connection.h"
#include "protocol.h"
/*
 *
 */


void send_greeting(Connection* con){
    send_data(con, GREET_MSG, GREET_MSG_LEN);
}

int receive_ack(Connection* con) {
    char buffer[100];
    receive_data(con, buffer, 100);

    return strcmp(buffer, ACK) == 0;
}

int receive_greet_ack(Connection* con){
    char buffer[100];
    receive_data(con, buffer, 100);

    return strcmp(buffer, GREET_ACK) == 0;
}

void send_stuffed_msg(Connection* con, char* msg){
    char buffer[strlen(msg)+50];
    int i;
    int state = 0;
    int stuffed = 0;
    for(i = 0; msg[i] != '\0'; i++){
        if(msg[i] == FAREWELL[state]){
            if(state == (strlen(FAREWELL)-1)){
                buffer[i+stuffed] = STUFF_CHAR;
                stuffed++;
            }else{
                state++;
            }
        }else{
            state = 0;
        }

        buffer[i+stuffed] = msg[i];
    }

    buffer[i+stuffed] = '\0';
    send_data(con, buffer, i+stuffed+1);
}

void send_farewell(Connection* con){
    send_data(con, FAREWELL, strlen(FAREWELL)+1);
}

int main(int argc, char** argv) {
    if(argc != 4){
        printf("Usage: %s <server-ip> <port> <directory\n", argv[0]);
        return 0;
    }

    char buffer[(1<<16)+1];
    buffer[0] = '\0';

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (argv[3])) != NULL) {
        //read all files in the directory specified
        while ((ent = readdir (dir)) != NULL) {
            // send_stuffed_msg(con, ent->d_name);
            // if(!receive_ack(con)){
            //     printf("The server don't seem to support our protocol\n");
            //     close_connection(con);
            //     return EXIT_FAILURE;
            // }
            // bytesTransfered += strlen(ent->d_name)+1;
            // bytesTransfered += ACK_LEN;
            if(ent->d_name[0] != '.'){
                sprintf(buffer, "%s%s\n", buffer, ent->d_name);
            }
        }
        closedir (dir);
    } else {
        printf("We couldn't open the specified directory\n");
        return EXIT_FAILURE;
    }

    char* address = argv[1];
    int port = atoi(argv[2]);

    Connection* con = connect_to_server(address, port);

    if(con == NULL){
        printf("Couldn't connect to the server. Is the address correct? (only ip addesses are supported)\n");
        return EXIT_FAILURE;
    }

    struct timespec beginTime, endTime;

    int bytesTransfered = 0;


    send_greeting(con);
    if(!receive_greet_ack(con)){
        printf("The server don't seem to support our protocol\n");
        close_connection(con);
        return EXIT_FAILURE;
    }

    send_stuffed_msg(con, argv[3]);
    if(!receive_ack(con)){
        printf("The server don't seem to support our protocol\n");
        close_connection(con);
        return EXIT_FAILURE;
    }

    clock_gettime(CLOCK_REALTIME, &beginTime);

    send_stuffed_msg(con, buffer);
    if(!receive_ack(con)){
        printf("The server don't seem to support our protocol\n");
        close_connection(con);
        return EXIT_FAILURE;
    }

    bytesTransfered = strlen(buffer);

    clock_gettime(CLOCK_REALTIME, &endTime);

    send_farewell(con);
    close_connection(con);

    double ellapsedTime = (endTime.tv_sec - beginTime.tv_sec) + (endTime.tv_nsec - beginTime.tv_nsec) / 1E9;




    printf("The file names were successfully sent %d B to server in %f seconds at %f B/s.\n", bytesTransfered, ellapsedTime, (bytesTransfered/ellapsedTime));

    return 0;
}
