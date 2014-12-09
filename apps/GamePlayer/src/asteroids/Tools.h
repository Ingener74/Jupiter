/*
 * Tools.h
 *
 *  Created on: Dec 9, 2014
 *      Author: ingener
 */

#ifndef APPS_GAMEPLAYER_SRC_ASTEROIDS_TOOLS_H_
#define APPS_GAMEPLAYER_SRC_ASTEROIDS_TOOLS_H_

#include <memory>
#include <string>
#include <functional>
#include <Jupiter/Jupiter.h>

struct GameTools
{
    std::function<std::string()>                                     gameLocation;
    std::function<std::shared_ptr<jupiter::Scene>( std::string )>    getScene;
    std::function<void( std::shared_ptr<jupiter::Scene> )>           setScene;
};

#endif /* APPS_GAMEPLAYER_SRC_ASTEROIDS_TOOLS_H_ */
