#include "server.h"
#include "../socket/socket.h"
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Client Client;
typedef struct MuteNode MuteNode;

struct MuteNode{
    Client* c;
    MuteNode* next;
};

struct Client{
    char username[20];
    char host[50];
    int port;
    Client* next;
    MuteNode* mute_list;
};

struct Server{
    Client* client_list;
};

Server* create_server(){
    Server* s = malloc(sizeof(Server));
    if(s != NULL)
        s->client_list = NULL;
    
    return s;
}

Client* new_client(char* username, char* host, int port){
    Client* c = malloc(sizeof(Client));
    strcpy(c->host, host);
    strcpy(c->username, username);
    c->port = port;
    c->next = NULL;
    c->mute_list = NULL;
    
    return c;
}

Client* find_user_by_host_port(Client* client_list, char* host, int port){
    Client* cur;
    for(cur = client_list; cur != NULL; cur = cur->next){
        if(strcmp(host, cur->host) == 0 && port == cur->port){
            break;
        }
    }
    return cur;
}

Client* find_user_by_username(Client* client_list, char* username){
    Client* cur;
    for(cur = client_list; cur != NULL; cur = cur->next){
        if(strcmp(username, cur->username) == 0){
            break;
        }
    }
    return cur;
}

int is_muted(Client* muter, Client* muted){
    MuteNode* cur = muter->mute_list;
    for(cur = muter->mute_list; cur != NULL; cur = cur->next){
        if(cur->c == muted)
            break;
    }
    return cur != NULL;
}

void free_mute_list(MuteNode* list){
    MuteNode* c = list;
    while(c != NULL){
        MuteNode* aux = c;
        c = c->next;
        free(aux);
    }
}

void free_clients(Client* first){
    Client* c = first;
    while(c != NULL){
        Client* aux = c;
        c = c->next;
        free_mute_list(aux->mute_list);
        free(aux);
    }
}

void run_nick(Server* server, Socket socket, char* msg, char* addr, int port){
    char username[20];
    char command[10];
    
    sscanf(msg, "%s%s", command, username);
    
    Client* c = new_client(username, addr, port);
    
    Client** last;
    for(last = &server->client_list; *last != NULL; last = &(*last)->next){
        if(strcmp(username, (*last)->username) == 0){
            send_message(socket, addr, port, "NICK taken\n");
            free_clients(c);
            return;
        }
    }
    *last = c;
    send_message(socket, addr, port, "NICK success\n");
}

void run_post(Server* server, Socket socket, char* msg, char* addr, int port){
    Client* from = find_user_by_host_port(server->client_list, addr, port);
    if(from == NULL){
        send_message(socket, addr, port, "POST not registered\n");
        return;
    }
    
    char buf[2000];
    sprintf(buf, "NEW %s %s", from->username, strchr(msg, ' ')+1);
    
    Client* cur;
    for(cur = server->client_list; cur != NULL; cur = cur->next){
        if(strcmp(cur->username, from->username) && !is_muted(cur, from)){
            send_message(socket, cur->host, cur->port, buf);
        }
    }
    
    send_message(socket, from->host, from->port, "POST success\n");
}

void run_mute(Server* server, Socket socket, char* msg, char* addr, int port){
    Client* from = find_user_by_host_port(server->client_list, addr, port);
    if(from == NULL){
        send_message(socket, addr, port, "MUTE not registered\n");
        return;
    }
    
    MuteNode* cur;
    char username[20];
    char command[10];
    sscanf(msg, "%s%s", command, username);
    Client* muted = find_user_by_username(server->client_list, username);
    if(muted == NULL){
        send_message(socket, addr, port, "MUTE no user\n");
        return;
    }
    for(cur = from->mute_list; cur != NULL; cur = cur->next){
        if(muted == cur->c){
            send_message(socket, addr, port, "MUTE already muted\n");
            return;
        }
        if(cur->next == NULL){
            break;
        }
    }
    
    MuteNode* newnode = malloc(sizeof(MuteNode));
    newnode->c = muted;
    newnode->next = NULL;
    if(cur == NULL){
        from->mute_list = newnode;
    }else{
        cur->next = newnode;
    }
    
    
    send_message(socket, addr, port, "MUTE success\n");
}

void run_unmute(Server* server, Socket socket, char* msg, char* addr, int port){
    MuteNode* cur;
    MuteNode* prev = NULL;
    
    char username[20];
    char command[10];
    sscanf(msg, "%s%s", command, username);
    
    Client* from = find_user_by_host_port(server->client_list, addr, port);
    if(from == NULL){
        send_message(socket, addr, port, "UNMUTE not registered\n");
        return;
    }
    Client* client = find_user_by_username(server->client_list, username);
    if(client == NULL){
        send_message(socket, addr, port, "UNMUTE no user\n");
        return;
    }
    for(cur = from->mute_list; cur != NULL; cur = cur->next){
        if(cur->c == client){
            break;
        }
        prev = cur;
    }
    if(cur == NULL){
        send_message(socket, addr, port, "UNMUTE not muted\n");
        return;
    }else if(prev == NULL){
        from->mute_list = cur->next;
        free(cur);
    }else{
        prev->next = cur->next;
        free(cur);
    }
    
    send_message(socket, addr, port, "UNMUTE success\n");
}

void run_close(Server* server, Socket socket, char* msg, char* addr, int port){
    Client* from = find_user_by_host_port(server->client_list, addr, port);
    if(from == NULL){
        send_message(socket, addr, port, "CLOSE not registered\n");
        return;
    }
    
    Client* prev;
    for(prev = server->client_list; prev->next != NULL; prev = prev->next){
        if(prev->next == from){
            break;
        }
    }
    
    if(server->client_list == from){
        server->client_list = from->next;
        from->next = NULL;
    }else{
        prev->next = from->next;
        from->next = NULL;
    }
    free_clients(from);
    
    send_message(socket, addr, port, "CLOSE success\n");
}


int process_request(Server* server, Socket socket, char* msg, char* from_addr, int from_port){
    char command[10];
    
    sscanf(msg, "%s", command);
    
    if(!strcmp(command, "NICK")){
        run_nick(server, socket, msg, from_addr, from_port);
    }else if(!strcmp(command, "POST")){
        run_post(server, socket, msg, from_addr, from_port);
    }else if(!strcmp(command, "MUTE")){
        run_mute(server, socket, msg, from_addr, from_port);
    }else if(!strcmp(command, "UNMUTE")){
        run_unmute(server, socket, msg, from_addr, from_port);
    }else if(!strcmp(command, "CLOSE")){
        run_close(server, socket, msg, from_addr, from_port);
    }else{
        return -1;
    }
    return 0;
}

void shutdown_server(Server* server){
    free_clients(server->client_list);
    free(server);
}
