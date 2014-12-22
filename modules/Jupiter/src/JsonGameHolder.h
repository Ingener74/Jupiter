/*
 * JsonGameHolder.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_SRC_JSONGAMEHOLDER_H_
#define MODULES_JUPITER_SRC_JSONGAMEHOLDER_H_

#include <boost/property_tree/ptree.hpp>

namespace jupiter
{

class JsonGameHolder
{
public:
    static std::shared_ptr<JsonGameHolder> instance();
    virtual ~JsonGameHolder();

    void setGame(const boost::property_tree::ptree&);
    const boost::property_tree::ptree& getGame()const;

    const boost::property_tree::ptree& findNode(const std::string& type, const std::string& name);

private:
    JsonGameHolder();

    boost::property_tree::ptree _pt;
};

} /* namespace jupiter */

#endif /* MODULES_JUPITER_SRC_JSONGAMEHOLDER_H_ */
