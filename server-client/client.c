#include <resolv.h> 
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>

void panic(char *msg);
#define panic(m) {perror (m); abort(); }

int main(int count, char *args[]) 
{  
    struct hostent* host; 
    struct sockaddr_in addr;
    int sd, port;

    if (count != 3) {
        printf("usage: %s <servername> <protocol or portnum>\n", args[0]); 
        exit(0);
    }
    /*---Get server's IP and standard service connection--*/
    
    host = gethostbyname (args[1]);
    
    printf("Server %s has IP address = %d\n", args[1], inet_ntoa (*(long*) host->h_addr_list[0]));
    if (!isdigit(args[2][0])) {
        
        struct servent *srv = getservbyname (args[2], "tcp");    
        if (srv == NULL)
            panic(args[2]);
        printf("%s: port=%d\n", srv->s_name, ntohs (srv->s_port)); 
        port = srv->s_port;
    }
    else
        port = htons (atoi(args[2]));
    /*----Create socket and connect to server---*/ 
    sd = socket (PF_INET, SOCK_STREAM, 0);
    
    if ( sd < 0)
        panic("socket");
    
    memset(&addr, 0, sizeof(addr)); 

    addr.sin_family= AF_INET;
    addr.sin_port = port;
    /* create socket */
    /* create & zero struct */
    /* select internet protocol */
    /* set the port # */
    addr.sin_addr.s_addr= *(long*) (host->h_addr_list[0]); 
    
    /* set the addr */ 
    /*If connection successful, send the message and read results---*/ 
    if (connect (sd, (struct sockaddr*)&addr, sizeof (addr)) == 0) {
    
        char buffer[256]="Hello";
        send(sd, buffer, sizeof (buffer),0);
        recv(sd, buffer, sizeof(buffer),0);
        printf("%s\n", buffer);
    /* send message */
    }
    else
    {
        panic("connect");
    }
}