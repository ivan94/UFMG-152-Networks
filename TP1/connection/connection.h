/* 
 * File:   connection.h
 * Author: ivan
 *
 * Created on November 3, 2015, 11:19 AM
 */

#ifndef CONNECTION_H
#define	CONNECTION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <netinet/in.h>
    
    struct Connection;
    typedef struct Connection Connection;
    
    Connection* create_connection(int sock_id, struct sockaddr_in* addr);
    void receive_data(Connection* con, char* buffer, int buffer_size);
    void send_data(Connection* con, char* buffer, int buffer_size);
    int close_connection(Connection* con);


#ifdef	__cplusplus
}
#endif

#endif	/* CONNECTION_H */

