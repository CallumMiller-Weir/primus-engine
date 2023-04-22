#ifndef FORMAT_HEADER
#define FORMAT_HEADER

#include <string>
#include <string_view>
#include <sstream>

namespace primus
{
    /*
     * format_helper(oss, str, value)
     * Replaces brackets with a variable value.
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
     * format(str, args)
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