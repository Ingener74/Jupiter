/*
 * Builder.h
 *
 *  Created on: Dec 20, 2014
 *      Author: ingener
 */

#ifndef MODULES_JUPITER_INCLUDE_JUPITER_BUILDER_H_
#define MODULES_JUPITER_INCLUDE_JUPITER_BUILDER_H_

#include <map>
#include <iostream>
#include <memory>
#include <string>

#include <boost/spirit/include/qi.hpp>

#include <Jupiter/JupiterError.h>

namespace jupiter
{

template<typename Product, typename ProductImpl>
class Builder
{
public:
    friend Product;

    class Factory
    {
    public:
        using ProductImplPtr = std::shared_ptr<ProductImpl>;

        virtual ProductImplPtr create(const std::string&) = 0;
    };

    static void addFactory(const std::string& type, std::shared_ptr<Factory> factory)
    {
        if (factoryRegister()[type])
            std::cerr << "warning: already have factory for that type " << type << std::endl;
        factoryRegister()[type] = factory;
    }

protected:
    static std::shared_ptr<ProductImpl> create(const std::string& product)
    {
        using namespace std;
        namespace q = boost::spirit::qi;

        vector<string> phrases;

        auto res = q::phrase_parse(
                begin(product),
                end(product),
                *q::lexeme[+~q::char_(":")],
                q::char_(":"),
                phrases
                );

        string type = phrases.size() > 1 ? phrases.front() : "file", parameter = phrases.back();

        return phrases.size() < 3 ? factoryRegister()[type]->create(parameter) : throw JupiterError(""
                "bad product " + product);

        auto factory = factoryRegister()[type];
        if (!factory)
            throw JupiterError("have no factory for type " + type);

        return factory->create(parameter);
    }

    using FactoryMap = std::map<std::string, std::shared_ptr<Factory>>;
    using ProductMap = std::map<std::string, std::shared_ptr<ProductImpl>>;

    static FactoryMap& factoryRegister()
    {
        static FactoryMap reg;
        return reg;
    }
    static ProductMap& productRegister()
    {
        static ProductMap reg;
        return reg;
    }

    Builder() = delete;
    virtual ~Builder() = delete;
};

}  // namespace jupiter

#endif /* MODULES_JUPITER_INCLUDE_JUPITER_BUILDER_H_ */
