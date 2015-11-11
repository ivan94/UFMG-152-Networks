/*
 * File:   client.h
 * Author: ivan
 *
 * Created on November 3, 2015, 11:28 AM
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#ifdef	__cplusplus
extern "C" {
#endif

char* GREET_MSG = "CONECTAR";
int GREET_MSG_LEN = 9;

char* GREET_ACK = "CONECTAR ACK";
int GREET_ACK_LEN = 13;

char* ACK = "ACK";
int ACK_LEN = 4;

char STUFF_CHAR = 'a';

char* FAREWELL = "TCHAU";

int MAX_MSG = (1<<16)+1;
#ifdef	__cplusplus
}
#endif

#endif	/* PROTOCOL_H */
