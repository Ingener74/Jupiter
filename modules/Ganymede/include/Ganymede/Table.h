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
#include <Ganymede/Function.h>
#include <Ganymede/Boolean.h>
#include <Ganymede/Nil.h>

namespace ganymede
{

class Table
{
public:
	Table();
	virtual ~Table();

	Table getTable(const std::string& fieldName) const;
	Number getNumber(const std::string& fieldName) const;
	String getString(const std::string& fieldName) const;
	Function getFunction(const std::string& fieldName) const;
	Boolean getBoolean(const std::string& fieldName) const;
	Nil getNil(const std::string& fieldName) const;

	friend std::ostream& operator<<(std::ostream& out, const Table& rho);
};

} /* namespace ganymede */

#endif /* TABLE_H_ */
