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

#include "PYON.h"
#include "PYONValue.h"
#include "interface.h"

using namespace std;

class FahClient
{
private:
    Interface *interface;
public:
    FahClient(string hostname, int port, string password);
    ~FahClient(void);

//Basic Commands
    string Help(string option = "");
    bool Auth(string option = "");
    string Error(string message = "");
    void Exit();
    int Heartbeat();
    void Quit();
    string Updates(string options);
//Folding@home client commands
    string Bond(string options);
    string DoCycle();
    string DownloadCore(string options);
    string Finish(string slot);
    string GetInfo();
    void Info();
    string MaskUnitState();
    string Option();
    string Options();
    string Pause(string slot);
    string Protein(string options);
    string QueueInfo();
    string RequestId();
    string RequestWs();
    string Save(string file);
    string Shutdown();
    string SimulationInfo(string slot);
    string SlotAdd(string options);
    string SlotDelete(string slot);
    string SlotInfo();
    string SlotModify(string options);
    string SlotOptions(string options);
    string Uptime();
    string WaitForUnits();
    string Add(double num1, double num2);
    string Clear();
    string Date(string format);
    string Div (double num1, double num2);
    string Eval(string expr);
    string If(string options);
    string Mul(double num1, double num2);
    string Not(string expr);
    string Sleep(int seconds);
    string Sub(double num1, double num2);
};

#endif /* _LIBFAHCLIENT_H */
