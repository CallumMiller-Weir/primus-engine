/*
    Copyright (c) 2023 Callum Miller-Weir

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so.

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    @author Callum Miller-Weir
 */

#include "package.h"
#include <iostream>

namespace primus
{
    Package::Package(const json &properties)
        : mProperties(properties)
    {
        if (!mProperties.contains(PROPERTY__PACKAGE_ID))
        {
            throw std::runtime_error("Package must contain 'package-id' field");
        }
    }

    const std::string Package::list()
    {
        std::string propertyList = "";
        for (auto it = mProperties.begin(); it != mProperties.end(); it++)
        {
            std::string propertyName = it.key();
            if (propertyName != PROPERTY__PACKAGE_ID) 
            {
                auto propertyValue = mProperties[propertyName];
                std::string property = primus::format("{} - {}: {}{}", INDENT, propertyName, propertyValue, LINE_BREAK);
                propertyList += property;
            }
        }

        return propertyList;
    }

    Package *Package::empty(const std::string &name) 
    {
        json properties;
        properties[PROPERTY__PACKAGE_ID] = name;
        return new Package(properties);
    }

    Package *Package::fromJSON(const std::string &jsonStr)
    {
        json properties = json::parse(jsonStr);
        return new Package(properties);
    }

    Package *Package::fromFile(const std::filesystem::path &filePath)
    {
        std::ifstream file(filePath);
        if (!file)
        {
            std::string error = primus::format("Could not open file '{}'", filePath.c_str());
            throw std::ifstream::failure(error);
        }

        json properties = json::parse(file);
        return new Package(properties);
    }
}