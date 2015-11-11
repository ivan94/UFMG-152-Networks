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

#include "../connection/connection.h"

    /**
     * Try to connect to the server specified. It supports both IPv4 and IPv6
     * @param  addr Server ip address
     * @param  port Port to connect to
     * @return      Pointer to connection object
     */
    Connection* connect_to_server(char* addr, int port);

#ifdef	__cplusplus
}
#endif

#endif	/* CLIENT_H */
