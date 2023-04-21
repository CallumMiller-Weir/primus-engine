#include "package.h"

namespace primus
{
    Package::Package(const std::string& name, const json& properties)
        : m_name(name), m_properties(properties)
    {
        m_properties["package-id"] = name;
    }

    Package *Package::empty(const std::string& name) 
    {
        json properties;
        properties["package-empty"] = true;
        return new Package(name, properties);
    }

    Package *Package::fromJSON(const std::string& jsonStr)
    {
        json properties = json::parse(jsonStr);
        properties["package-empty"] = false;

        std::string name = properties["package-id"];
        return new Package(name, properties);
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
        properties["package-empty"] = false;

        std::string name = properties["package-id"];
        return new Package(name, properties);
    }
}