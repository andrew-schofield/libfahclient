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

#include "libfahclient.h"

string WideToNarrow(wstring wide)
{
    //gah, not unicode safe!!
    string str;
    str.assign(wide.begin(), wide.end());
    return str;
}

FahClient::FahClient(string hostname, int port)
{
    interface = new Interface(hostname, port);
}

FahClient::~FahClient(void)
{
    delete interface;
}

string FahClient::Help(string option)
{
    return this->interface->Help(option);
}

bool FahClient::Auth(string password)
{
    string str;
    str = this->interface->Auth(password);
    if(str.find("OK") != string::npos)
        return true;
    if(str.find("FAILED") != string::npos)
        return false;
    return false;
}

string FahClient::Error(string message)
{
    PYONValue* value = this->interface->Error(message);
    return WideToNarrow(wstring(value->AsString()));
}

void FahClient::Exit()
{
    this->interface->Exit();
}

int FahClient::Heartbeat()
{
    PYONValue* value = this->interface->Heartbeat();
    return int(value->AsNumber());
}

void FahClient::Quit()
{
    this->interface->Quit();
}

void FahClient::Info()
{
    PYONValue* value = this->interface->Info();
}


