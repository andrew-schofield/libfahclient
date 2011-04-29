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

#include "interface.h"

Interface::Interface(string hostname, int port)
{
    connection = new Connection(hostname, port);
}

Interface::~Interface()
{
    delete connection;
}

string Interface::Preparse(string pyon)
{
    pyon.replace(pyon.find("PyON"), pyon.find("\n")+1, "");
    pyon.replace(pyon.find("\n---\n>"), 6, "");
    return pyon;
}

string Interface::Help(string option)
{
    string str;
    str.append("help ");
    str.append(option);
    str.append("\n");
    return this->connection->Command(str);
    
}

string Interface::Auth(string password)
{
    string str;
    str.append("auth ");
    str.append(password);
    str.append("\n");
    return this->connection->Command(str);
}

PYONValue* Interface::Error(string message)
{
    string str;
    str.append("error \"");
    str.append(message);
    str.append("\"\n");
    return PYON::Parse(Preparse(this->connection->Command(str)).c_str());
}

void Interface::Exit()
{
    this->connection->Command("exit");
}

PYONValue* Interface::Heartbeat()
{
    return PYON::Parse(Preparse(this->connection->Command("heartbeat\n")).c_str());
}

void Interface::Quit()
{
    this->connection->Command("quit");
}

PYONValue* Interface::Info()
{
    return PYON::Parse(Preparse(this->connection->Command("info\n")).c_str());
}

string Interface::Add(double num1, double num2)
{
    string str;
    str.append("add ");
    str.append(stringify(num1));
    str.append(" ");
    str.append(stringify(num2));
    str.append("\n");
    return this->connection->Command(str);
}

string Interface::Div(double num1, double num2)
{
    string str;
    str.append("div ");
    str.append(stringify(num1));
    str.append(" ");
    str.append(stringify(num2));
    str.append("\n");
    return this->connection->Command(str);
}

string Interface::Mul(double num1, double num2)
{
    string str;
    str.append("mul ");
    str.append(stringify(num1));
    str.append(" ");
    str.append(stringify(num2));
    str.append("\n");
    return this->connection->Command(str);
}

string Interface::Not(string expr)
{
    string str;
    str.append("not ");
    str.append(expr);
    str.append("\n");
    return this->connection->Command(str);
}

string Interface::Sub(double num1, double num2)
{
    string str;
    str.append("sub ");
    str.append(stringify(num1));
    str.append(" ");
    str.append(stringify(num2));
    str.append("\n");
    return this->connection->Command(str);
}

