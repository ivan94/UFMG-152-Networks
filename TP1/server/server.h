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
    
    Server* create_server(int port);
    int  listen_port(Server* server);
    Connection* accept_connection(Server* server);
    int shutdown_server(Server* server);
    
    
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */

