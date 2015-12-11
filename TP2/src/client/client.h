/*
 * File:   client.h
 * Author: ivan
 *
 * Created on November 3, 2015, 11:28 AM
 */

#ifndef CLIENT_H
#define	CLIENT_H

#ifdef	__cplusplus
extern "C" {
#endif

int mute_user(Socket s, char* addr, int port, char* username);
int unmute_user(Socket s, char* addr, int port, char* username);
int close_connection(Socket s, char* addr, int port);

int register_user(Socket s, char* address, int port, char* username);

int process_user_input(Socket s, char* addr, int port, char* input);

void process_received_msg(char* msg);

#ifdef	__cplusplus
}
#endif

#endif	/* CLIENT_H */
