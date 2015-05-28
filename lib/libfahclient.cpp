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

bool to_bool(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

FahClient::FahClient(string hostname, int port)
{
    clientInterface = new Interface(hostname, port);
}

FahClient::~FahClient(void)
{
    delete clientInterface;
}

string FahClient::Help(string option)
{
    return this->clientInterface->Help(option);
}

bool FahClient::Auth(string password)
{
    string str;
    str = this->clientInterface->Auth(password);
    if(str.find("OK") != string::npos)
        return true;
    if(str.find("FAILED") != string::npos)
        return false;
    return false;
}

string FahClient::Error(string message)
{
    PYONValue* value = this->clientInterface->Error(message);
    return WideToNarrow(wstring(value->AsString()));
}

void FahClient::Exit()
{
    this->clientInterface->Exit();
}

int FahClient::Heartbeat()
{
    PYONValue* value = this->clientInterface->Heartbeat();
    return int(value->AsNumber());
}

void FahClient::Quit()
{
    this->clientInterface->Quit();
}

void FahClient::Pause()
{
    this->clientInterface->Pause();
}

void FahClient::Pause(int slot)
{
    this->clientInterface->Pause(slot);
}

double FahClient::PPD()
{
    PYONValue* value = this->clientInterface->PPD();
    return double(value->AsNumber());
}

int FahClient::NumSlots()
{
    PYONValue* value = this->clientInterface->NumSlots();
    return int(value->AsNumber());
}

void FahClient::UnPause()
{
    this->clientInterface->UnPause();
}

void FahClient::UnPause(int slot)
{
    this->clientInterface->UnPause(slot);
}

struct tm FahClient::Uptime()
{
    struct tm uptime;
    int years = 0, months= 0, days = 0, hours = 0, minutes = 0, seconds = 0;
    sscanf(this->clientInterface->Uptime().c_str(), "%d %d %d %d", &days, &hours, &minutes, &seconds);
    uptime.tm_sec = seconds;
    uptime.tm_min = minutes;
    uptime.tm_hour = hours;
    uptime.tm_mday = days;
    uptime.tm_mon = hours;
    uptime.tm_year = years;
    uptime.tm_wday = 0;
    uptime.tm_yday = 0;
    uptime.tm_isdst = -1;
    return uptime;
}

struct info FahClient::Info()
{
    PYONValue* value = this->clientInterface->Info();
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
    return strtod(this->clientInterface->Add(num1, num2).c_str(), NULL);
}

double FahClient::Div(double num1, double num2)
{
    return strtod(this->clientInterface->Div(num1, num2).c_str(), NULL);
}

double FahClient::Mul(double num1, double num2)
{
    return strtod(this->clientInterface->Mul(num1, num2).c_str(), NULL);
}

bool FahClient::Not(string expr)
{
    return to_bool(this->clientInterface->Not(expr));
}

double FahClient::Sub(double num1, double num2)
{
    return strtod(this->clientInterface->Sub(num1, num2).c_str(), NULL);
}

