
/**
*  Crawl_Server.c
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Hero.h"
#include "Header.h"
#include "Crawl_Server.h"

static void exit_error(char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}
static void _destroy(Crawl_Server* this)
{
    if (NULL != this) {
        if (PRINT)
            printf("%p\n", this);
        free(this);
    }
}
static int connect_to_client(int port)
{
    struct sockaddr_in server_address;
    int fd_server, sock, opt;
    socklen_t addr_size;
    opt = 1;

    fd_server = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port        = htons(port);

    addr_size = sizeof(server_address);

    bind(fd_server, (struct sockaddr*)&server_address, addr_size);
    listen(fd_server, 5);
    printf("\nWaiting for response from client\n");

    sock = accept(fd_server, (struct sockaddr*)&server_address, &addr_size);

    return sock;
}

static Hero* _packet(Crawl_Server* this, Hero* send_hero, int sock)
{
    const char ser_buff[100];
    const char cli_buff[100];
    const char* ser_mess = "hey";
    const char* cli_mess = "you";
    if (!this->type) {
        send(sock, cli_mess, 100, 0);
    } else {
        recv(sock, ser_buff, 100, 0);
    }

    printf("type is: %s\n", ser_buff);
    return send_hero;
}
static int connect_to_server(int port)
{
    struct sockaddr_in server_address, client_address;
    int sock;
    unsigned int client_port;
    socklen_t addr_size, len;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    addr_size = sizeof(server_address);

    connect(sock, (struct sockaddr*)&server_address, addr_size);

    return sock;
}
Crawl_Server* CREATE_CRAWL_SERVER(int type)
{
    Crawl_Server* this = malloc(sizeof(*this));
    this->destroy      = _destroy;
    this->packet       = _packet;
    this->type         = type;

    if (type)
        this->connect = connect_to_client;
    else
        this->connect = connect_to_server;

    if (PRINT)
        printf("%p\n", this);

    return this;
}
int get_port(int argc, char** argv)
{
    int port = 0;
    if ((sscanf(argv[2], "%d", &port) != 1)) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return port;
}
int host_type(int argc, char** argv)
{
    int result = 0;
    if ((0 == strcmp(argv[1], "server"))) {
        result = 1;
    }
    return result;
}
