/*
 * File:   server.h
 * Author: ivan
 *
 * Created on November 3, 2015, 11:02 AM
 */

#ifndef SERVER_H
#define	SERVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "socket.h"

    typedef struct Server Server;

    Server* create_server();

    int process_request(Server* server, Socket socket, char* msg, char* from_addr, int from_port);

    void shutdown_server(Server* server);






#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */
