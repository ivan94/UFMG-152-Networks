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

    Connection* connect_to_server(char* addr, int port);

#ifdef	__cplusplus
}
#endif

#endif	/* CLIENT_H */

