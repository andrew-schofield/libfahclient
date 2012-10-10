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

#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <stdexcept>

#include "connection.h"
#include "PYONValue.h"

using namespace std;

class BadConversion : public std::runtime_error
{
public:
    BadConversion(std::string const& s)
    : std::runtime_error(s)
    { }
};

class Interface
{
private:
    string Preparse(string pyon);
    std::string stringify(double x)
    {
        std::ostringstream o;
        if (!(o << x))
            throw BadConversion("stringify(double)");
        return o.str();
    }
protected:
    Connection *connection;
public:
    Interface(string hostname, int port);
    ~Interface(void);
//Basic Commands
    string Help(string option);
    string Auth(string option);
    PYONValue* Error(string message);
    void Exit();
    PYONValue* Heartbeat();
    void Quit();
    //string Updates(string options);
//Folding@home client commands
    //string Bond(string options);
    //string DoCycle();
    //string DownloadCore(string options);
    //string Finish(string slot);
    //string GetInfo();
    PYONValue* Info();
    //string MaskUnitState();
    PYONValue* NumSlots();
    //string Option();
    //string Options();
    void Pause();
    void Pause(int slot);
    PYONValue* PPD();
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
    string Uptime();
    void UnPause();
    void UnPause(int slot);
    //string WaitForUnits();
    string Add(double num1, double num2);
    //string Date(string format);
    string Div (double num1, double num2);
    //string Eval(string expr);
    //string If(string options);
    string Mul(double num1, double num2);
    string Not(string expr);
    //void Sleep(int seconds);
    string Sub(double num1, double num2);
};

#endif /* _INTERFACE_H */
