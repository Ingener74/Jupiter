/*
 * Boolean.h
 *
 *  Created on: Aug 15, 2014
 *      Author: pavel
 */

#ifndef BOOLEAN_H_
#define BOOLEAN_H_

namespace ganymede
{

class Boolean
{
public:
	Boolean();
	virtual ~Boolean();

	operator bool() const ;
};

} /* namespace ganymede */

#endif /* BOOLEAN_H_ */
