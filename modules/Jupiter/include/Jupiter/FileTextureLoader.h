/*
 * FileTextureLoader.h
 *
 *  Created on: Dec 4, 2014
 *      Author: pavel
 */

#ifndef FILETEXTURELOADER_H_
#define FILETEXTURELOADER_H_

#include <string>

#include <png.h>

#include <Jupiter/TextureLoader.h>

namespace jupiter
{

class FileTextureLoader: public TextureLoader
{
public:
    FileTextureLoader(const std::string& fileName);
    virtual ~FileTextureLoader();

    virtual Image load();

private:
    std::string fileName;

    static void pngRwCallback(png_structp, png_bytep, png_size_t);
};

} /* namespace jupiter */

#endif /* FILETEXTURELOADER_H_ */
