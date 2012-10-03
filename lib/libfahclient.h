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

#ifndef _LIBFAHCLIENT_H
#define _LIBFAHCLIENT_H

#include <string>
#include <sstream>
#include <algorithm>

#include "PYON.h"
#include "PYONValue.h"
#include "interface.h"

using namespace std;

struct info {
    struct Client {
        string Website;
        string Copyright;
        string Author;
        string Args;
        string Config;        
    } client;
    struct Build {
        string Version;
        time_t Date;
        time_t Time;
        int SVNRev;
        string Branch;
        string Compiler;
        string Options;
        string Platform;
        int Bits;
        string Mode;        
    } build;
    struct System {
        string OS;
        string CPU;
        string CPUID;
        string CPUs;
        string Memory;
        string FreeMemory;
        string Threads;
        int GPUs;
        /*array of GPUs should be here*/
        double CUDA;
        double CUDADriver;
        bool OnBattery;
        double UTCoffset;
        int PID;
        string CWD;
        bool Win32Service;
    } system;
};

class FahClient
{
private:
    Interface *interface;
public:

    FahClient(string hostname, int port);
    ~FahClient(void);

//Basic Commands
    string Help(string option = "");
    bool Auth(string option = "");
    string Error(string message = "");
    void Exit();
    int Heartbeat();
    //void LogUpdates(string state);
    void Quit();
    //string Updates(string options);
//Folding@home client commands
    //string Bond(string options);
    //string DoCycle();
    //string DownloadCore(string options);
    //string Finish(string slot);
    //string GetInfo();
    struct info Info();
    //string Inject(string options);
    //string MaskUnitState();
    //string Option();
    //string Options();
    //string Pause(string slot);
    double PPD();
    //string Protein(string options);
    //string QueueInfo();
    //string RequestId();
    //string RequestWs();
    //string Save(string file);
    //string Shutdown();
    //string SimulationInfo(string slot);
    //string SlotAdd(string options);
    //string SlotDelete(string slot);
    //string SlotInfo();
    //string SlotModify(string options);
    //string SlotOptions(string options);
    //string UnPause(string slot);
    //string Uptime();
    //string WaitForUnits();
    double Add(double num1, double num2);
    //string Clear();
    //string Date(string format);
    double Div (double num1, double num2);
    //string Eval(string expr);
    //string If(string options);
    double Mul(double num1, double num2);
    bool Not(string expr);
    //string Sleep(int seconds);
    double Sub(double num1, double num2);
};

#endif /* _LIBFAHCLIENT_H */
