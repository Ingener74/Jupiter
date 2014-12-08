/*
 * PNGImageFactory.h
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#ifndef PNGIMAGEFACTORY_H_
#define PNGIMAGEFACTORY_H_

#include <png.h>

#include <Jupiter/ResourceManager.h>
#include <Jupiter/detail/ImageBuilder.h>

namespace jupiter
{

class PNGImageFactory: public ImageBuilder::Factory
{
public:
    PNGImageFactory();
    virtual ~PNGImageFactory();

    virtual Image create(const std::string& fileName);

private:
    ResourceManager::Resource file;

    static void pngRwCallback(png_structp, png_bytep, png_size_t);
};

} /* namespace jupiter */

#endif /* PNGIMAGEFACTORY_H_ */
