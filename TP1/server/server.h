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
    
    struct Server;
    
    typedef struct Server Server;
    
    
    Server* create(char* addr, int port);
    Connection* accept(Server* server);
    int shutdown(Server* server);
    
    
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */

