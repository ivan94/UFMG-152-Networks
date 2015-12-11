#include <strings.h>
#include <stdio.h>
#include <string.h>

#include "../socket/socket.h"

int mute_user(Socket s, char* addr, int port, char* username){
    char buffer[2000];
    bzero(buffer, 2000);
    sprintf(buffer, "MUTE %s\n", username);

    send_message(s, addr, port, buffer);

    bzero(buffer, 2000);
    char from[50];
    int fromport;

    receive_message(s, buffer, from, 50, &fromport);

    if(!strcmp(buffer, "MUTE success\n")){
        printf("O usuario %s foi colocado no mudo\n", username);
        return 1;
    }else if((!strcmp(buffer, "MUTE already muted\n"))){
        printf("O usuário ja esta mudo");
        return 1;
    }if((!strcmp(buffer, "MUTE no user\n"))){
        printf("O usuário nao existe\n");
        return 1;
    }else{
        printf("Resposta invalida, verifique o endereco e porta\n");
        return 0;
    }
}
int unmute_user(Socket s, char* addr, int port, char* username){
    char buffer[2000];
    bzero(buffer, 2000);
    sprintf(buffer, "UNMUTE %s\n", username);

    send_message(s, addr, port, buffer);

    bzero(buffer, 2000);
    char from[50];
    int fromport;

    receive_message(s, buffer, from, 50, &fromport);

    if(!strcmp(buffer, "UNMUTE success\n")){
        printf("O usuario %s foi retirado do mudo\n", username);
        return 1;
    }else if((!strcmp(buffer, "UNMUTE not muted\n"))){
        printf("O usuário nao esta mudo\n");
        return 1;
    }if((!strcmp(buffer, "UNMUTE no user\n"))){
        printf("O usuário nao existe\n");
        return 1;
    }else{
        printf("Resposta invalida, verifique o endereco e porta\n");
        return 0;
    }
}
int close_connection(Socket s, char* addr, int port){
    char buffer[2000];
    bzero(buffer, 2000);
    sprintf(buffer, "CLOSE\n");

    send_message(s, addr, port, buffer);

    bzero(buffer, 2000);
    char from[50];
    int fromport;

    receive_message(s, buffer, from, 50, &fromport);

    if(!strcmp(buffer, "CLOSE success\n")){
        printf("Desconectado com sucesso\n");
        return 0;
    }else{
        printf("Resposta invalida, verifique o endereco e porta\n");
        return 0;
    }
}

int register_user(Socket s, char* address, int port, char* username){
    char buffer[2000];
    bzero(buffer, 2000);

    sprintf(buffer, "NICK %s\n", username);
    send_message(s, address, port, buffer);

    bzero(buffer, 2000);
    char from[50];
    int fromport;

    receive_message(s, buffer, from, 50, &fromport);

    if(!strcmp(buffer, "NICK success\n")){
        printf("Conectado como %s\n", username);
        return 0;
    }else if(!strcmp(buffer, "NICK taken\n")){
        printf("Username ja cadastrado\n");
        return -1;
    }else{
        printf("Resposta invalida, verifique o endereco e porta\n");
        return -1;
    }
}

int process_user_input(Socket s, char* addr, int port, char* input){
    if(input[0] == '/'){
        char command[100];
        bzero(command, 100);
        sscanf(input, "%s", command);
        if(!strcmp(command, "/mute")){
            char username[20];
            bzero(username, 20);
            sscanf(input,"%s%s", command, username);
            return mute_user(s, addr, port, username);
            
        }else if(!strcmp(command, "/unmute")){
            char username[20];
            bzero(username, 20);
            sscanf(input,"%s%s", command, username);
            return unmute_user(s, addr, port, username);
        }else if(!strcmp(command, "/close")){
            return close_connection(s, addr, port);
        }else{
            printf("Lista de comandos\n");
            printf("%-30s %s", "/mute <username>", "Para de receber mensagens do usuario\n");
            printf("%-30s %s", "/unmute <username>", "Volta a receber mensagens do usuario\n");
            printf("%-30s %s", "/close", "Se desconecta do servidor e termina o programa\n");
            printf("%-30s %s", "/help", "Mostra esta lista\n\n");
            return 1;
        }
    }else{
        char buffer[2000];
        bzero(buffer, 2000);
        sprintf(buffer, "POST %s", input);
        
        send_message(s, addr, port, buffer);
        
        bzero(buffer, 2000);
        char from[50];
        int fromport;
        
        receive_message(s, buffer, from, 50, &fromport);
        
        if(!strcmp(buffer, "POST success\n")){
            return 1;
        }else{
            printf("Resposta invalida, verifique o endereco e porta\n");
            return 0;
        }
        
    }
}

void process_received_msg(char* msg){
    char command[10];
    sscanf(msg, "%s", command);
    if(!strcmp(command, "NEW")){
        char username[18];
        sscanf(msg, "%s%s", command, username);
        char* buffer = strchr(strchr(msg, ' ')+1, ' ')+1;
        
        printf("%s: %s", username, buffer);
    }else{
        printf("Unsupported %s command\n", command);
    }
}