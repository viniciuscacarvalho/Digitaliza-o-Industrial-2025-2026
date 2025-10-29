
#include <sys/socket.h> 
#include <sys/types.h> 
#include <resolv.h> 
#include <pthread.h> 
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>

void panic(char *msg);
#define panic(m) {perror (m); abort(); }

void *threadfuntion (void *arg) 
{
    int sd = *(int *)arg; 
    char buffer[256];
    /* get & convert the socket */
    recv(sd, buffer, sizeof (buffer),0);
    printf("Received: %s\n", buffer);
    
    send(sd, buffer, sizeof(buffer),0); 
    shutdown (sd, SHUT_RD); 
    shutdown (sd, SHUT_WR); 
    shutdown (sd, SHUT_RDWR);
    /* close the client's channel */ /* terminate the thread */
}
int main (int count, char* args[])
{
    struct sockaddr_in addr;
    int listen_sd, port;
    
    if (count != 2) {
        printf("usage: %s <protocol or portnum >\n", args[0]); exit(0);
    }
    /*-Get server's IP and standard service connection--*/ 
    if (!isdigit (args[1][0])) {
        struct servent *srv = getservbyname (args[1], "tcp"); 
        if (srv == NULL)
            panic (args[1]);
        printf("%s: port %d\n", srv->s_name, ntohs (srv->s_port)); 
        port = srv->s_port;
    
    }
    else
        port = htons (atoi(args[1]));
    /*--create socket --*/
    
    listen_sd = socket (PF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0)
        panic("socket");
    
        /*----bind port/address to socket---*/
    
    memset(&addr, 0, sizeof (addr));
    
    addr.sin_family = AF_INET;
    
    addr.sin_port = port;
    
    addr.sin_addr.s_addr = INADDR_ANY;
    
        /*any interface */
    
    if (bind(listen_sd, (struct sockaddr*)&addr, sizeof (addr)) != 0) 
        panic("bind");
    
    /*make into listener with 10 slots*/
    
    if (listen(listen_sd, 10) != 0) 
        panic("listen")
    
    /*- begin waiting for connections*/
    
    else {
        while (1) {
    
            int n = sizeof (addr);
            /* process all incoming clients */
            /* accept connection */
            int sd = accept (listen_sd, (struct sockaddr*)&addr, &n); 
            if (sd != -1){
                pthread_t child;

                printf("New connection\n");
                
                pthread_create(&child, 0, threadfuntion, &sd); 
                
                pthread_detach (child);
                
                /*start thread */
                /*don't track it */
            }
        }
    }
}
