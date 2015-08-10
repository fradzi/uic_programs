/*
Filip Radzikowski
U.Illinois at Chicago
CS 361 HWK 4
4.3.15

Personal Server
*/


#include <fnmatch.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>

#define BACKLOG (10)
#define MAXBUFSIZE (4096)

/* Created to pass two parameters though pthread_create */
struct args{
    int* sock;
    char* directoryName;
};

/* char* parseRequest(char* request)
 * Args: HTTP request of the form "GET /path/to/resource HTTP/1.X" 
 *
 * Return: the resource requested "/path/to/resource"
 *         0 if the request is not a valid HTTP request 
 * 
 * Does not modify the given request string. 
 * The returned resource should be free'd by the caller function. 
 */
char* parseRequest(char* request) {
  //assume file paths are no more than 256 bytes + 1 for null. 
  char *buffer = malloc(sizeof(char)*257);
  memset(buffer, 0, 257);
  
  if(fnmatch("GET * HTTP/1.*",  request, 0)) return 0; 

  sscanf(request, "GET %s HTTP/1.", buffer);
  return buffer; 
}// end parseRequest()

/* When user inputs a page that does not exist then a 404 page is printed to the 
browser screen */
void clienterror(int fd, char *cause,char *errnum, char* shortmsg, char* longmsg)
{
    int retval;
    char buf[256], body[512];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Error:</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>Filips Web Server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    retval = send(fd, buf, strlen(buf), 0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }
    sprintf(buf, "Content-Type: text/html\r\n");
    retval = send(fd, buf, strlen(buf), 0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }
    sprintf(buf, "Content-Length: %d\r\n\r\n",(int)strlen(body));
    retval = send(fd, buf, strlen(buf), 0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }
    retval = send(fd, body, strlen(body), 0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }
}// end clienterror()


/* Set HTTP header and body and send to the client. Build the contents of the 
directory using opendir() and readdir() */
void readDirectoryItems(int fd, char** filename, char* tempDirName, int* isfile){

    int retval = -1;
    char buf[256];
    char body[512];

    /* Build the HTTP response header */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sContent-Type: %s\r\n\r\n", buf, "text/html");

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Directory</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    
    // using <dirent.h> to open the directory 
    DIR *dir;
    struct dirent *dp;
    char * file_name;
    dir = opendir(*filename);
    while ((dp=readdir(dir)) != NULL) {
        // do not include the "." and ".." files in directory listing
        if( strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
            continue;
        file_name = dp->d_name; 

        sprintf(body,"%s<p><a href = %s\r\n> %s</a></p>",body, file_name, file_name );
       
    }// end while loop
    closedir(dir);

    sprintf(body, "%s<p>\r\n", body);
    sprintf(body, "%s<hr><em>Filips Web Server</em>\r\n", body);

    /* Send the HTTP header */
    retval = send(fd, buf, strlen(buf), 0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }
    /* Send HTTP body */
    retval = send(fd, body, strlen(body), 0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }
    // else if index.html exist in dir then set URI
    strcpy(tempDirName, *filename);
    *isfile = 0;
      
}// end readDirectoryItems()



/* Check if file exists. If file exits check if directory. If directory then 
based on whether index.html exist print index.html file and if not then print 
out the directory listing to the browser. */
int isFile(int fd, char** filename, char* directoryName, struct stat *statbuffer){
    
    int isfile = 1;
    //int retval;
    char tempDirName[256];
    /* Get new URI and append the root file */
    strcpy(tempDirName, directoryName);
    strcat(tempDirName, *filename);
    strcpy(*filename, tempDirName);

    /* Get Directory name from filename */ 
    if (stat(*filename, statbuffer) < 0) {
        
        clienterror(fd, *filename, "404", "Not Found", "Server Couldn't find file");
        isfile = 0;
        return isfile;
    }
    
    /* Check if given directory exists */
    if (S_ISDIR(statbuffer->st_mode)) {
        
        strcpy(tempDirName, *filename);
        strcat(tempDirName, "index.html");
        /* Check if index.html file exists in directory */
        if(stat(tempDirName, statbuffer) < 0){
            /* Read directory listings and print the browser */
            readDirectoryItems(fd, filename, tempDirName, &isfile); 
        }  
    }
    strcpy(*filename, tempDirName);  
    
    return isfile;
}// end isFile()


/* derive file type from file name provided by client */
void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".pdf"))
        strcpy(filetype, "application/pdf");
    else if (strstr(filename, ".png"))
        strcpy(filetype, "image/png");
    else if (strstr(filename, ".iso"))
        strcpy(filetype, "image/vnd.microsoft.icon");
    else
        strcpy(filetype, "text/plain");
}

/* Send html header and response to client for existing file */
void serve_static(int fd, char *filename, int filesize, int isFile)
{
    int retval;
    int srcfd;
    char *srcp, filetype[257], buf[257];

    /* Send response headers to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Filips Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-Type: %s\r\n\r\n", buf, filetype);
    retval = send(fd, buf, strlen(buf),0);
    if(retval < 0){
        perror("Error Sending Connection");
        exit(1);
    }

    /* Send response body to client */
    srcfd = open(filename, O_RDONLY, 0);
    srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    close(srcfd);
    retval = send(fd, srcp, filesize,0);
    if(retval < 0){
        perror("Error Sending Connection 1");
        exit(1);
    }
    munmap(srcp, filesize);
}// end serve_static()

/* Recieve buffer from client, parse, check if valid request and
send request back to client */
void* doit (void* param)
{
    //detach parent
    pthread_detach(pthread_self());

    /* retrieve struct data including sock file descriptor 
     and directory name provided on the command line*/
    int retval;
    int sock = *(((struct args*)param)->sock);
    char* directoryName = ((struct args*)param)->directoryName;
    //free memory from struct
    free(((struct args*)param)->sock);
    free(param);

    // buffer hold all recieved messages
    char buffer[MAXBUFSIZE];
    struct stat statbuffer;
    // ptr iterates by size of sock file descriptor
    char* ptr = buffer; 
    
    do{

        retval = recv(sock,ptr,MAXBUFSIZE,0);
        if(retval < 0){
            perror("Error recieving connection");
            exit(1);
        }
        //inprement ptr to end of previous ptr buffer info
        ptr+=retval; 
    
    } while(strstr(buffer,"\r\n\r\n") == NULL);

    /* Parse the clients request and returns filename*/
    char* filename = parseRequest(buffer);
    
    /* checks if existing directory or file exist. Returns true is directory
    input by user exists with index.html file. */
    int isfile = isFile(sock, &filename, directoryName, &statbuffer);
    
    // if file exits then send to client
    if(isfile)
        serve_static(sock, filename, statbuffer.st_size, isfile);

    /* Tell the OS to clean up the resources associated with that client
     * connection, now that we're done with it. */ 
    close(sock);
    
    return NULL;
    
}


/* Your program should take two arguments:
 * 1) The port number on which to bind and listen for connections, and
 * 2) The directory out of which to serve files.
 */
int main(int argc, char** argv) {
    /* Check command line args */
    if (argc != 3) {
        fprintf(stderr, "Required Usage: %s <port> <filename>\n", argv[0]);
        exit(1);
    }
    
    /* For checking return values. */
    int retval;

    /* Read the port number from the first command line argument. */
    int port = atoi(argv[1]);
    /* Read the filename */
    char* directoryName = argv[2];
     
    /* Create a socket to which clients will connect. */
    int server_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if(server_sock < 0) {
        perror("Creating socket failed");
        exit(1);
    }

    /* A server socket is bound to a port, which it will listen on for incoming
     * connections.  By default, when a bound socket is closed, the OS waits a
     * couple of minutes before allowing the port to be re-used.  This is
     * inconvenient when you're developing an application, since it means that
     * you have to wait a minute or two after you run to try things again, so
     * we can disable the wait time by setting a socket option called
     * SO_REUSEADDR, which tells the OS that we want to be able to immediately
     * re-bind to that same port. See the socket(7) man page ("man 7 socket")
     * and setsockopt(2) pages for more details about socket options. */
    int reuse_true = 1;
    retval = setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_true,
                        sizeof(reuse_true));
    if (retval < 0) {
        perror("Setting socket option failed");
        exit(1);
    }

    /* Create an address structure.  This is very similar to what we saw on the
     * client side, only this time, we're not telling the OS where to connect,
     * we're telling it to bind to a particular address and port to receive
     * incoming connections.  Like the client side, we must use htons() to put
     * the port number in network byte order.  When specifying the IP address,
     * we use a special constant, INADDR_ANY, which tells the OS to bind to all
     * of the system's addresses.  If your machine has multiple network
     * interfaces, and you only wanted to accept connections from one of them,
     * you could supply the address of the interface you wanted to use here. */

    struct sockaddr_in6 addr;   // internet socket address data structure
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port); // byte order is significant
    addr.sin6_addr = in6addr_any; // listen to all interfaces

    
    /* As its name implies, this system call asks the OS to bind the socket to
     * address and port specified above. */
    retval = bind(server_sock, (struct sockaddr*)&addr, sizeof(addr));
    if(retval < 0) {
        perror("Error binding to port");
        exit(1);
    }

    /* Now that we've bound to an address and port, we tell the OS that we're
     * ready to start listening for client connections.  This effectively
     * activates the server socket.  BACKLOG (#defined above) tells the OS how
     * much space to reserve for incoming connections that have not yet been
     * accepted. */
    retval = listen(server_sock, BACKLOG);
    if(retval < 0) {
        perror("Error listening for connections");
        exit(1);
    }

    while(1) {
        
        struct args* args = (struct args*)malloc(sizeof(struct args));


        /* Declare a socket for the client connection. */
        args->sock = (int*)malloc(sizeof(int));
        args->directoryName = directoryName;

        /* Another address structure.  This time, the system will automatically
         * fill it in, when we accept a connection, to tell us where the
         * connection came from. */
        struct sockaddr_in remote_addr;
        unsigned int socklen = sizeof(remote_addr); 

        /* Accept the first waiting connection from the server socket and
         * populate the address information.  The result (sock) is a socket
         * descriptor for the conversation with the newly connected client.  If
         * there are no pending connections in the back log, this function will
         * block indefinitely while waiting for a client connection to be made.
         * */
        *(args->sock) = accept(server_sock, (struct sockaddr*) &remote_addr, &socklen);
        if(*(args->sock) < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        pthread_t *thread = malloc(sizeof(pthread_t));
        // will call echo multiple times
        retval = pthread_create(thread,NULL,doit,(void*)args);
        /* Error check Send() */
        if(retval < 0){
            perror("Error creating pthread");
            exit(1); 
        }
    }
    
    close(server_sock);
}
