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

#ifndef FORMAT_HEADER
#define FORMAT_HEADER

#include <string>
#include <string_view>
#include <sstream>

namespace primus
{
    /*
     * Replaces brackets with the specified value.
     * 
     * Code taken from Toby Speight on StackOverflow
     * https://shorturl.at/evLN0
     */
    template<typename T>
    void format_helper(std::ostringstream &oss, std::string_view &str, const T &value)
    {
        std::size_t openBracket = str.find('{');
        if (openBracket == std::string::npos) 
        { 
            return;
        }

        std::size_t closeBracket = str.find('}', openBracket + 1);
        if (closeBracket == std::string::npos) 
        { 
            return; 
        }

        oss << str.substr(0, openBracket) << value;
        str = str.substr(closeBracket + 1);
    }

    /*
     * Formats variables into a string.
     * 
     * Code taken from Toby Speight on StackOverflow
     * https://shorturl.at/evLN0
     */
    template<typename... Targs>
    std::string format(std::string_view str, Targs...args)
    {
        std::ostringstream oss;
        (format_helper(oss, str, args),...);
        oss << str;
        
        return oss.str();
    }
}

#endif //FORMAT_HEADER