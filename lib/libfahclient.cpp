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

struct info FahClient::Info()
{
    PYONValue* value = this->interface->Info();
    PYONArray root;
    PYONArray section;
    PYONArray subsection;
    struct info infoholder;
    //struct info::Client client;
    //struct info::Build build;
    //struct info::System system;
    
    root = value->AsArray();
    
    //Folding@home Client
    section = root[0]->AsArray();
    for (unsigned int i = 1; i < section.size(); i++)
	{
	    subsection = section[i]->AsArray();
	    for (unsigned int j = 0; j < subsection.size(); j+=2)
	    { 
		    if(WideToNarrow(subsection[j]->AsString()).compare("Website") == 0)
		        infoholder.client.Website = WideToNarrow(subsection[j+1]->AsString());
		    else if(WideToNarrow(subsection[j]->AsString()).compare("Copyright") == 0)
		        infoholder.client.Copyright = WideToNarrow(subsection[j+1]->AsString());
		    else if(WideToNarrow(subsection[j]->AsString()).compare("Author") == 0)
		        infoholder.client.Author = WideToNarrow(subsection[j+1]->AsString());
		    else if(WideToNarrow(subsection[j]->AsString()).compare("Args") == 0)
		        infoholder.client.Args = WideToNarrow(subsection[j+1]->AsString());
		    else if(WideToNarrow(subsection[j]->AsString()).compare("Config") == 0)
		        infoholder.client.Config = WideToNarrow(subsection[j+1]->AsString());
		}
	}

	
	//Build
    section = root[1]->AsArray();
    for (unsigned int i = 1; i < section.size(); i++)
	{
	    subsection = section[i]->AsArray();
	    for (unsigned int j = 0; j < subsection.size(); j+=2)
	    {
		    if(WideToNarrow(subsection[j]->AsString()).compare("Version") == 0)
		        infoholder.build.Version = WideToNarrow(subsection[j+1]->AsString());
		    //if(WideToNarrow(subsection[j]->AsString()).compare("Date") == 0)
		    //    infoholder.build.Date = WideToNarrow(subsection[j+1]->AsString());
		    //if(WideToNarrow(subsection[j]->AsString()).compare("Time") == 0)
		    //    infoholder.build.Time = WideToNarrow(subsection[j+1]->AsString());
		    if(WideToNarrow(subsection[j]->AsString()).compare("SVNRev") == 0)
		        infoholder.build.SVNRev = atoi(WideToNarrow(subsection[j+1]->AsString()).c_str());
		    if(WideToNarrow(subsection[j]->AsString()).compare("Branch") == 0)
		        infoholder.build.Branch = WideToNarrow(subsection[j+1]->AsString());
		    if(WideToNarrow(subsection[j]->AsString()).compare("Compiler") == 0)
		        infoholder.build.Compiler = WideToNarrow(subsection[j+1]->AsString());
		    if(WideToNarrow(subsection[j]->AsString()).compare("Options") == 0)
		        infoholder.build.Options = WideToNarrow(subsection[j+1]->AsString());
		    if(WideToNarrow(subsection[j]->AsString()).compare("Platform") == 0)
		        infoholder.build.Platform = WideToNarrow(subsection[j+1]->AsString());
		    if(WideToNarrow(subsection[j]->AsString()).compare("Bits") == 0)
		        infoholder.build.Bits = atoi(WideToNarrow(subsection[j+1]->AsString()).c_str());
		    if(WideToNarrow(subsection[j]->AsString()).compare("Mode") == 0)
		        infoholder.build.Mode = WideToNarrow(subsection[j+1]->AsString());
		}
	}
	
	//System
    section = root[2]->AsArray();
    for (unsigned int i = 1; i < section.size(); i++)
	{
	    subsection = section[i]->AsArray();
	    for (unsigned int j = 0; j < subsection.size(); j+=2)
	    { 
		   // wcout << L"[" << j << L"] => " << subsection[j]->Stringify() << L"\r\n";
		}
	}
	return infoholder;
}

double FahClient::Add(double num1, double num2)
{
    return strtod(this->interface->Add(num1, num2).c_str(), NULL);
}

double FahClient::Div(double num1, double num2)
{
    return strtod(this->interface->Div(num1, num2).c_str(), NULL);
}

double FahClient::Mul(double num1, double num2)
{
    return strtod(this->interface->Mul(num1, num2).c_str(), NULL);
}

double FahClient::Sub(double num1, double num2)
{
    return strtod(this->interface->Sub(num1, num2).c_str(), NULL);
}

