/*
 * Table.h
 *
 *  Created on: Aug 15, 2014
 *      Author: pavel
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <Ganymede/GanymedeCommon.h>

#include <Ganymede/String.h>
#include <Ganymede/Number.h>

namespace ganymede
{

class Table
{
public:
	Table();
	virtual ~Table();

	Table getTable(const std::string& fieldName) const ;
	Number getNumber(const std::string& fieldName) const ;
	String getString(const std::string& fieldName) const ;
};

} /* namespace ganymede */

#endif /* TABLE_H_ */
