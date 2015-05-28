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
#include <time.h>

#include "PYON.h"
#include "PYONValue.h"
#include "interface.h"

struct info {
    struct Client {
        std::string Website;
        std::string Copyright;
        std::string Author;
        std::string Args;
        std::string Config;
    } client;
    struct Build {
        std::string Version;
        std::string Date;
        std::string Time;
        int SVNRev;
        std::string Branch;
        std::string Compiler;
        std::string Options;
        std::string Platform;
        int Bits;
        std::string Mode;
    } build;
    struct System {
        std::string OS;
        std::string CPU;
        std::string CPUID;
        unsigned int CPUs;
        std::string Memory;
        std::string FreeMemory;
        std::string Threads;
        unsigned int GPUs;
        /*array of GPUs should be here*/
        std::string CUDA;
        std::string CUDADriver;
        bool HasBattery;
        bool OnBattery;
        double UTCoffset;
        int PID;
        std::string CWD;
        bool Win32Service;
        double OSVersion;
        std::string OSArch;

    } system;
};

class FahClient
{
private:
    Interface* clientInterface;
public:

    FahClient(std::string hostname, int port);
    ~FahClient(void);
    std::string error;

//Basic Commands
    std::string Help(std::string option = "");
    bool Auth(std::string option = "");
    std::string Error(std::string message = "");
    void Exit();
    int Heartbeat();
    //void LogUpdates(std::string state);
    void Quit();
    //std::string Updates(std::string options);
//Folding@home client commands
    //std::string Bond(std::string options);
    //std::string DoCycle();
    //std::string DownloadCore(std::string options);
    //std::string Finish(std::string slot);
    //std::string GetInfo();
    struct info Info();
    //std::string Inject(std::string options);
    //std::string MaskUnitState();
    int NumSlots();
    //std::string Option();
    //std::string Options();
    void Pause();
    void Pause(int slot);
    double PPD();
    //std::string Protein(std::string options);
    //std::string QueueInfo();
    //std::string RequestId();
    //std::string RequestWs();
    //std::string Save(std::string file);
    //std::string Shutdown();
    //std::string SimulationInfo(std::string slot);
    //std::string SlotAdd(std::string options);
    //std::string SlotDelete(std::string slot);
    //std::string SlotInfo();
    //std::string SlotModify(std::string options);
    //std::string SlotOptions(std::string options);
    void UnPause();
    void UnPause(int slot);
    struct tm Uptime();
    //std::string WaitForUnits();
    double Add(double num1, double num2);
    //std::string Clear();
    //std::string Date(std::string format);
    double Div (double num1, double num2);
    //std::string Eval(std::string expr);
    //std::string If(std::string options);
    double Mul(double num1, double num2);
    bool Not(std::string expr);
    //std::string Sleep(int seconds);
    double Sub(double num1, double num2);
};

#endif /* _LIBFAHCLIENT_H */
