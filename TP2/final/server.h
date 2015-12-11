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

    /**
     * Aloca a estrutura server e a inicializa
     * @return Um ponteiro para a estrutura
     */
    Server* create_server();

    /**
     * Processa a mensagem enviada pelo cliente usando funções internas
     * @param  server    referencia para o servidor
     * @param  socket    socket de conexão
     * @param  msg       a mensagem recebida
     * @param  from_addr o endereço do remetente
     * @param  from_port a porta do remetente
     * @return           0 se a requisição é valida e -1 caso contrario
     */
    int process_request(Server* server, Socket socket, char* msg, char* from_addr, int from_port);

    /**
     * Desaloca a estrutura servidor e suas estruturas internas
     * @param server referencia para o servidor
     */
    void shutdown_server(Server* server);






#ifdef	__cplusplus
}
#endif

#endif	/* SERVER_H */
