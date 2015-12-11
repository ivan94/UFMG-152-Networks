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

#include "socket.h"

/**
 * Envia o comando MUTE
 * @param  s
 * @param  addr
 * @param  port
 * @param  username
 * @return          boolean se o cliente deve continuar rodando
 */
int mute_user(Socket s, char* addr, int port, char* username);
/**
 * Envia o comando UNMUTE
 * @param  s
 * @param  addr
 * @param  port
 * @param  username
 * @return          boolean se o cliente deve continuar rodando
 */
int unmute_user(Socket s, char* addr, int port, char* username);
/**
 * Envia o comando CLOSE
 * @param  s
 * @param  addr
 * @param  port
 * @return      boolean se o cliente deve continuar rodando
 */
int close_connection(Socket s, char* addr, int port);
/**
 * Envia o comando NICK
 * @param  s
 * @param  address
 * @param  port
 * @param  username
 * @return          boolean se o cliente deve continuar rodando
 */
int register_user(Socket s, char* address, int port, char* username);
/**
 * Processa o input do usuario
 * @param  s
 * @param  addr
 * @param  port
 * @param  input
 * @return       boolean se o cliente deve continuar rodando
 */
int process_user_input(Socket s, char* addr, int port, char* input);
/**
 * Processa a mensage recebida do servidor
 * @param msg [description]
 */
void process_received_msg(char* msg);

#ifdef	__cplusplus
}
#endif

#endif	/* CLIENT_H */
