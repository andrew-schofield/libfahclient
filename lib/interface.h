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

#include <string>

#include "connection.h"

using namespace std;

class Interface
{
protected:
    Connection *connection;
public:
    Interface(string hostname, int port, string password);
    ~Interface(void);

    string Help(string option);
    string Auth();
    string Error();
    string Heartbeat();
    string Exit();
    string Quit();
    string GetInfo();
    string Info();
    string Option();
    string GetOption();
    string SetOption();
    string Options();
    string DefaultOptions();
    string AllOptions();
    string GetOptions();
    string SetOptions();
    string ResetOptions();
    string QueueInfo();
    string SimulationInfo();
    string SlotAdd();
    string SlotDelete();
    string SlotInfo();
    string SlotModify();
    string SlotOptions();
    string DefaultSlotOptions();
    string AllSlotOptions();
    string Uptime();
    string Add();
    string Clear();
    string Date();
    string Div ();
    string Eval();
    string If();
    string Mul();
    string Not();
    string Sleep();
    string Sub();
};

#endif /* _INTERFACE_H */
