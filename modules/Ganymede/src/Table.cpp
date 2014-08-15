/*
 * Table.cpp
 *
 *  Created on: Aug 15, 2014
 *      Author: pavel
 */

#include <Ganymede/Table.h>

namespace ganymede
{

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

} /* namespace ganymede */
