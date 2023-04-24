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
    Package::Package(const json& properties)
        : m_properties(properties)
    {
    }

    const std::string Package::list()
    {
        std::string propertyList = "";
        for (auto it = m_properties.begin(); it != m_properties.end(); it++)
        {
            std::string propertyName = it.key();
            if (propertyName != PROPERTY__PACKAGE_ID) 
            {
                auto propertyValue = m_properties[propertyName];
                std::string property = primus::format("{} - {}: {}{}", INDENT, propertyName, propertyValue, LINE_BREAK);
                propertyList += property;
            }
        }

        return propertyList;
    }

    Package *Package::empty(const std::string& name) 
    {
        json properties;
        properties[PROPERTY__PACKAGE_ID] = name;
        return new Package(properties);
    }

    Package *Package::fromJSON(const std::string& jsonStr)
    {
        json properties = json::parse(jsonStr);
        if (properties.find(PROPERTY__PACKAGE_ID) == properties.end())
        {
            throw std::invalid_argument("Package must contain 'package-id' field");
        }

        std::string name = properties[PROPERTY__PACKAGE_ID];
        return new Package(properties);
    }

    Package *Package::fromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            std::string error = primus::format("Could not open file '{}'", filename);
            throw std::ifstream::failure(error);
        }

        json properties = json::parse(file);
        if (properties.find(PROPERTY__PACKAGE_ID) == properties.end())
        {
            throw std::invalid_argument("Package must contain 'package-id' field");
        }

        std::string name = properties[PROPERTY__PACKAGE_ID];
        return new Package(properties);
    }
}