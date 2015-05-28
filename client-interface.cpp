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

std::stringstream ParseInfo(info info)
{
    std::stringstream out;
    out << "**** Client ****" << std::endl
        << "Website: " << info.client.Website << std::endl
        << "Copyright: " << info.client.Copyright << std::endl
        << "Author: " << info.client.Author << std::endl
        << "Args: " << info.client.Args << std::endl
        << "Config: " << info.client.Config << std::endl
        << "**** Build ****" << std::endl
        << "Version: " << info.build.Version << std::endl
        << "Date: " << info.build.Date << std::endl
        << "Time: " << info.build.Time << std::endl
        << "SVN Revision: " << info.build.SVNRev << std::endl
        << "Branch: " << info.build.Branch << std::endl
        << "Compiler: " << info.build.Compiler << std::endl
        << "Options: " << info.build.Options << std::endl
        << "Platform: " << info.build.Platform << std::endl
        << "Bits: " << info.build.Bits << std::endl
        << "Mode: " << info.build.Mode << std::endl
        << "**** System ****" << std::endl
        << "OS: " << info.system.OS << std::endl
        << "CPU: " << info.system.CPU << std::endl
        << "CPUID: " << info.system.CPUID << std::endl
        << "CPUs: " << info.system.CPUs << std::endl
        << "Memory: " << info.system.Memory << std::endl
        << "Free Memory: " << info.system.FreeMemory << std::endl
        << "Threads: " << info.system.Threads << std::endl
        << "GPUs: " << info.system.GPUs << std::endl
        << "CUDA: " << info.system.CUDA << std::endl
        << "CUDA Driver: " << info.system.CUDADriver << std::endl
        << "On Battery: " << info.system.OnBattery << std::endl
        << "UTC Offset: " << info.system.UTCoffset << std::endl
        << "PID: " << info.system.PID << std::endl
        << "CWD: " << info.system.CWD << std::endl
        << "Windows Service: " << info.system.Win32Service << std::endl;
    return out;
}

int main()
{
    std::string hostname = "127.0.0.1";
    std::string password = "1";
    int port = 36330;

    FahClient *myfahclient = new FahClient(hostname.c_str(), port);
    std::cout << "Connected to Folding@home command server @ " << hostname << ":" << port << std::endl;
    std::cout << "Authenticating..." << std::endl;
    if (!myfahclient->Auth(password))
    {
        std::cout << "Authentication failed!" << std::endl;
        myfahclient->Quit();
        std::cout << "Closed connection to Folding@home command server" << std::endl;
        delete myfahclient;
        getchar();
        return 0;
    }
    std::cout << "Authentication successful" << std::endl;
    std::cout << "Slot count: " << myfahclient->NumSlots() << std::endl;
    std::cout << "PPD: " << myfahclient->PPD() << std::endl;
    std::cout << "Client Info:" << std::endl;
    std::cout << ParseInfo(myfahclient->Info()).str() << std::endl;
    std::cout << "Closed connection to Folding@home command server" << std::endl;
    delete myfahclient;  
    getchar();
    return 0;
}

