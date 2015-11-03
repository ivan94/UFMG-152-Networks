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

    struct Connection;
    typedef struct Connection Connection;
    
    Connection* create(int sock_id);
    char* receive(int buffer_size);
    char* send(char* buffer, int buffer_size);


#ifdef	__cplusplus
}
#endif

#endif	/* CONNECTION_H */

