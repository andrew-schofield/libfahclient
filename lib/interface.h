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
    std::string Preparse(std::string pyon);
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
    Interface(std::string hostname, int port);
    ~Interface(void);
//Basic Commands
    std::string Help(std::string option);
    std::string Auth(std::string option);
    PYONValue* Error(std::string message);
    void Exit();
    PYONValue* Heartbeat();
    void Quit();
    //std::string Updates(std::string options);
//Folding@home client commands
    //std::string Bond(std::string options);
    //std::string DoCycle();
    //std::string DownloadCore(std::string options);
    //std::string Finish(std::string slot);
    //std::string GetInfo();
    PYONValue* Info();
    //std::string MaskUnitState();
    PYONValue* NumSlots();
    //std::string Option();
    //std::string Options();
    void Pause();
    void Pause(int slot);
    PYONValue* PPD();
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
    std::string Uptime();
    void UnPause();
    void UnPause(int slot);
    //std::string WaitForUnits();
    std::string Add(double num1, double num2);
    //std::string Date(std::string format);
    std::string Div(double num1, double num2);
    //std::string Eval(std::string expr);
    //std::string If(std::string options);
    std::string Mul(double num1, double num2);
    std::string Not(std::string expr);
    //void Sleep(int seconds);
    std::string Sub(double num1, double num2);
};

#endif /* _INTERFACE_H */
