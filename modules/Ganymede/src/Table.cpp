/*
 * Table.cpp
 *
 *  Created on: Aug 15, 2014
 *      Author: pavel
 */

#include "Ganymede/Table.h"

namespace ganymede
{

using namespace std;

Table::Table()
{
}

Table::~Table()
{
}

Table Table::getTable(const std::string& fieldName) const
{
	return Table();
}

Number Table::getNumber(const std::string& fieldName) const
{
	return Number();
}

String Table::getString(const std::string& fieldName) const
{
	return String();
}

Function Table::getFunction(const std::string& fieldName) const
{
	return Function();
}

Boolean Table::getBoolean(const std::string& fieldName) const
{
	return Boolean();
}

Nil Table::getNil(const std::string& fieldName) const
{
	return Nil();
}

ostream& operator<<(ostream& out, const Table& rho)
{
	out << "Table: " << endl;
	return out;
}

} /* namespace ganymede */
