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

    /**
     * Create a connection given a socket and an address
     * @param  sock_id The socket number returned by the socket function
     * @param  addr    Pointer to the address object
     * @return         Pointer to the connection
     */
    Connection* create_connection(int sock_id, struct sockaddr_in6* addr);

    /**
     * Reads the stream for data sent from the other end
     * @param con         Pointer to connection
     * @param buffer      Buffer to put the read strem on
     * @param buffer_size Size of the buffer
     */
    void receive_data(Connection* con, char* buffer, int buffer_size);
    /**
     * Sends an array of characters to the server
     * @param con         Pointer to connection
     * @param buffer      Buffer containing bytes to send
     * @param buffer_size Size of the buffer
     */
    void send_data(Connection* con, char* buffer, int buffer_size);
    /**
     * Close the connection
     * @param  con Pointer to connection
     * @return     0 if success, -1 if error
     */
    int close_connection(Connection* con);

    /**
     * Get the connection address in readable format
     * @param con  Pointer to connecton
     * @param dest Pointer to array where the readable address will be saved
     */
    void get_connection_address(Connection* con, char* dest);


#ifdef	__cplusplus
}
#endif

#endif	/* CONNECTION_H */
