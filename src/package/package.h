#ifndef PACKAGE_HEADER
#define PACKAGE_HEADER

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../utility/format.h"

namespace primus
{
    using json = nlohmann::json;

    class Package 
    {
    private:
        std::string m_name;
        json m_properties;
    public:
        Package(const std::string& name, const json& properties);

        template<typename T> 
        T getProperty(const std::string propertyName)
        {
            if (m_properties.find(propertyName) == m_properties.end())
            {
                std::string error = primus::format("Could not find property with id '{}'", propertyName);
                throw std::invalid_argument(error);
            }

            return m_properties[propertyName];
        }

        static Package *empty(const std::string& name);
        static Package *fromJSON(const std::string& jsonStr);
        static Package *fromFile(const std::string& filename);
    };
}

#endif //PACKAGE_HEADER