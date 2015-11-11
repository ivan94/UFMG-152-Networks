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

#include "../connection/connection.h"

    typedef struct Server Server;

    /**
     * Create a server struct
     * @param  port The port to bind the socket to
     * @return      The pointer the created server struct
     */
    Server* create_server(int port);
    /**
     * Start listening to the bound port
     * @param  server The server pointer
     * @return        0 if success and -1 if error
     */
    int  listen_port(Server* server);
    /**
     * Awaits for a connection from a client and create a connection struct to represent that connection
     * @param  server Pointer to server
     * @return        Pointer to the new connection
     */
    Connection* accept_connection(Server* server);
    /**
     * Close the connection and shutdown the server
     * @param  server Pointer to server
     * @return        0 if success -1 if error
     */
    int shutdown_server(Server* server);






#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */
