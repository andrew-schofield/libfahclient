#include <stdio.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif
#include <string>
#include <stdlib.h>
//#include <unistd.h>

#define RECV_BYTES 4096

class Connection
{
private:
    int socket_descriptor;
public:
    Connection(std::string hostname, int port);
    
    ~Connection();

    bool Socket_Connect(const char *hostname, int port);

    bool Socket_Send(const char *message);

    std::string Socket_Recv();

    void Socket_Close();
    
    std::string Command(std::string cmd);

};
