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

using namespace std;

class Connection
{
private:
    int socket_descriptor;
public:
    Connection(string hostname, int port);
    
    ~Connection();

    bool Socket_Connect(const char *hostname, int port);

    bool Socket_Send(const char *message);

    string Socket_Recv();

    void Socket_Close();
    
    string Command(string cmd);

};
