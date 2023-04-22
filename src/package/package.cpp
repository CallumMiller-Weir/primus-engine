#include "package.h"
#include <iostream>

namespace primus
{
    Package::Package(const json& properties)
        : m_properties(properties)
    {
    }

    std::string Package::listProperties()
    {
        std::string propertyList = "";
        for (auto it = m_properties.begin(); it != m_properties.end(); it++)
        {
            std::string propertyName = it.key();
            auto propertyValue = m_properties[propertyName];
            std::string property = primus::format("{} - {}: {}{}", INDENT, propertyName, propertyValue, LINE_BREAK);
            propertyList += property;
        }

        return propertyList;
    }

    Package *Package::empty(const std::string& name) 
    {
        json properties;
        properties["package-id"] = name;
        return new Package(properties);
    }

    Package *Package::fromJSON(const std::string& jsonStr)
    {
        json properties = json::parse(jsonStr);
        if (properties.find("package-id") == properties.end())
        {
            throw std::invalid_argument("Package must contain 'package-id' field");
        }

        std::string name = properties["package-id"];
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
        if (properties.find("package-id") == properties.end())
        {
            throw std::invalid_argument("Package must contain 'package-id' field");
        }

        std::string name = properties["package-id"];
        return new Package(properties);
    }
}