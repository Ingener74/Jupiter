/*
 * ImageBuilder.h
 *
 *  Created on: Dec 8, 2014
 *      Author: pavel
 */

#ifndef IMAGEBUILDER_H_
#define IMAGEBUILDER_H_

#include <map>
#include <memory>
#include <string>

#include <Jupiter/Image.h>

namespace jupiter
{

class ImageBuilder
{
public:
    friend class Image;

    class Factory
    {
    public:
        virtual std::shared_ptr<ImageImpl> create(const std::string& fileName) = 0;
    };

    static void addFactory(const std::string& extension, std::shared_ptr<Factory>);

private:
    static std::shared_ptr<ImageImpl> create(const std::string& fileName);

    static std::map<std::string, std::shared_ptr<Factory>>& factoryRegister();
    static std::map<std::string, std::shared_ptr<ImageImpl>>& imageRegister();

    static std::string getFileExtention(const std::string& fileName);

    ImageBuilder() = default;
    virtual ~ImageBuilder() = default;
};

} /* namespace jupiter */

#endif /* IMAGEBUILDER_H_ */
