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

#ifndef PACKAGE_HEADER
#define PACKAGE_HEADER

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../utility/logger.h"
#include "../utility/format.h"

namespace primus
{
    using json = nlohmann::json;

    #define PROPERTY__PACKAGE_ID "package-id"

    /*
     * A package of properties used for component configuration.
     */
    class Package 
    {
    private:
        json m_properties;
    public:
        /*
         * Package constructor.
         *
         * @param properties a JSON object
         *
         * @warning usage of this constructor is not recommended as there it does not enforce the following mandatory properties:
         * - package-id: the name of the package
         */
        Package(const json &properties);

        /*
         * Retrieves a property.
         *
         * @param propertyId the name of the sought property
         * 
         * @throws std::invalid_argument if propertyId does not belong to an existing property.
         */
        template<typename T> 
        const T getProperty(const std::string &propertyId)
        {
            if (m_properties.find(propertyId) == m_properties.end())
            {
                std::string error = primus::format("Could not find property with id '{}'", propertyId);
                throw std::invalid_argument(error);
            }

            return m_properties[propertyId];
        }

        /*
         * Sets the value of an existing property.
         *
         * @param propertyId the name of the sought property
         * @param value the proposed new value for the sought property
         * 
         * @throws std::invalid_argument if propertyId does not belong to an existing property.
         */
        template<typename T>
        void setProperty(const std::string &propertyId, const T& value)
        {
            if (m_properties.find(propertyId) == m_properties.end())
            {
                std::string error = primus::format("Could not find property with id '{}'", propertyId);
                throw std::invalid_argument(error);
            }

            if (propertyId == PROPERTY__PACKAGE_ID)
            {
                throw std::invalid_argument("Cannot set property 'package-id'");
            }

            m_properties[propertyId] = value;
        }

        /*
         * Enumerates the properties within the package.
         */
        const std::string list();

        /*
         * Creates an empty package.
         *
         * @param name the name of the new package.
         */
        static Package *empty(const std::string &name);

        /*
         * Creates a package from a JSON string.
         *
         * @param jsonStr a string containing a JSON object.
         * 
         * @throws std::invalid_argument if propertyId does not belong to an existing property.
         */
        static Package *fromJSON(const std::string &jsonStr);

        /*
         * Creates a package from a JSON file.
         *
         * @param filename the name of the JSON file.
         * 
         * @throws std::ifstream::failure if filename does not belong to an existing file.
         * @throws std::invalid_argument if propertyId does not belong to an existing property.
         */
        static Package *fromFile(const std::string &filename);
    };
}

#endif //PACKAGE_HEADER