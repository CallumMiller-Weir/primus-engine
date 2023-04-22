#ifndef REPOSITORY_HEADER
#define REPOSITORY_HEADER

#include <filesystem>
#include "../utility/logger.h"
#include "../utility/format.h"
#include "package.h"

namespace primus 
{
    class Repository
    {
    private:
        std::string m_name;
        std::unordered_map<std::string, Package *> m_packages;
    public:
        Repository(const std::string &name);

        void add(Package *package);
        void remove(const std::string &packageName);

        std::string listPackages();

        static Repository *empty(const std::string &name);
        static Repository *fromDirectory(const std::string &path);
    };
}

#endif //REPOSITORY_HEADER