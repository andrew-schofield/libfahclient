/*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Library General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "connection.h"

Connection::Connection(string hostname, int port)
{
    Socket_Connect(hostname.c_str(), port);

    this->Socket_Recv();
}

Connection::~Connection()
{
}

bool Connection::Socket_Connect(const char *hostname, int port)
{

	struct sockaddr_in sin;
	struct hostent *hp;
	int	sd;
	
	if ((hp = gethostbyname(hostname)) == 0) {
		return false;
	}
	
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	sin.sin_port = htons(port);

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		return false;
	}
	
	if (connect(sd,(struct sockaddr *)  &sin, sizeof(sin)) == -1) {
		return false;
	}
	
	socket_descriptor =  sd;
	
	return true;

}

bool Connection::Socket_Send(const char *message)
{
	if (send(socket_descriptor, message, strlen(message), 0) == -1) {
		return false;
	}
	
	return true;
}

string Connection::Socket_Recv()
{
    fd_set g_ReadSet;
    struct timeval tv;
    FD_ZERO(&g_ReadSet);
    FD_SET(socket_descriptor, &g_ReadSet);
    tv.tv_sec = 0;
    tv.tv_usec = 50000;
    string out = "";
	static char buffer[RECV_BYTES];
	int recv_bytes = 0;
	int retval = 1;
	while(1) {
        retval = select(socket_descriptor+1, &g_ReadSet, NULL, NULL, &tv);
        if (retval < 1)
            break;
	    recv_bytes = recv(socket_descriptor, buffer, RECV_BYTES, 0);
        if (recv_bytes == -1) {
            return '\0';
        }
        
        buffer[recv_bytes] = '\0';
        out.append(buffer);
    }
    return out;
}

void Connection::Socket_Close()
{
	close(socket_descriptor);
}

string Connection::Command(string cmd)
{
    string s;
    
    Socket_Send(cmd.c_str());
        
    s = Socket_Recv();
    return s;
}
