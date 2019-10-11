#ifndef CRAWL_SERVER_H
#define CRAWL_SERVER_H
typedef struct _Hero Hero;
typedef struct sockaddr_in sockaddr_in;
int get_port(int argc, char** argv);  /* Get port from commnad line args */
int host_type(int argc, char** argv); /* client or server specified in command args */
typedef struct sockaddr sockaddr;
typedef struct _Crawl_Server {
    void (*destroy)(struct _Crawl_Server* this); /* Free Allocated Memory */
    int (*connect)(int port);
    Hero* (*packet)(struct _Crawl_Server* this, Hero* send_hero, int sock);
    int type;

} Crawl_Server;
Crawl_Server* CREATE_CRAWL_SERVER(int type);

#endif /* CRAWL_SERVER_H */
