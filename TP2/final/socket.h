/*
 * File:   server.h
 * Author: ivan
 *
 * Created on November 3, 2015, 11:02 AM
 */

#ifndef SOCKET_H
#define	SOCKET_H

#ifdef	__cplusplus
extern "C" {
#endif


    typedef int Socket;

    /**
     * Create a spcket
     * @return      The created socket
     */
    Socket create_socket();
    int bind_socket(Socket socket, int port);

    int send_message(Socket socket, char* to, int port, char* msg);

    int receive_message(Socket socket, char* buf, char* from, int from_buf_size, int* fromport);
    /**
     * Close the connection and shutdown the server
     * @param  server Pointer to server
     * @return        0 if success -1 if error
     */
    int close_socket(Socket socket);






#ifdef	__cplusplus
}
#endif

#endif	/* SOCKET_H */
