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

#include <iostream>

#include "client-interface.h"

int main()
{
    string hostname = "127.0.0.1";
    string password = "1";
    int port = 36330;

    FahClient *myfahclient = new FahClient(hostname, port);
    if (!myfahclient->Auth(password))
    {
        delete myfahclient;
        return 0;
    }
    
    struct info clientinfo;
    clientinfo = myfahclient->Info();
    cout << clientinfo.client.Website << endl;
    delete myfahclient;      
}

