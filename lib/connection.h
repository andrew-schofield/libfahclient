#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>

#define RECV_BYTES 4096

using namespace std;

class Connection
{
private:
    int socket_descriptor;
public:
    Connection(string hostname, int port, string password);
    ~Connection();

    bool Socket_Connect(const char *hostname, int port, const char *password);

    bool Socket_Send(const char *message);

    string Socket_Recv();

    void Socket_Close();
    
    string Command(string cmd);

};
