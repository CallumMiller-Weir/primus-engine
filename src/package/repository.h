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

#ifndef REPOSITORY_HEADER
#define REPOSITORY_HEADER

#include <filesystem>
#include "../utility/logger.h"
#include "../utility/format.h"
#include "package.h"

namespace primus 
{
    /*
     * A collection of configuration packages.
     */
    class Repository
    {
    private:
        std::string m_name;
        std::unordered_map<std::string, Package *> m_packages;

        Repository *m_parent;
        std::unordered_map<std::string, Repository *> m_children;
    public:
        Repository(const std::string &name, Repository *parent = nullptr);

        /*
         * Adds a package to the repository.
         *
         * @param package the package to add to the repository.
         * 
         * @throws std::invalid_argument if package is null.
         */
        void addPackage(Package *package);

        /*
         * Removes a package from the repository.
         *
         * @param packageId the name of an existing package to remove.
         * 
         * @throws std::runtime_error if packageId does not belong to an existing package.
         */
        void removePackage(const std::string &packageId);

        /*
         * Retrieves a package given an id.
         *
         * @param packageId the id of the sought package.
         *
         * @throws std::runtime_error if packageId does not belong to a package in the repository.
         */
        Package *findPackage(const std::string &packageId);

        /*
         * Adds a child repository.
         *
         * @param child another repository.
         * 
         * @throws std::invalid_argument if child is null.
         */
        void addRepository(Repository *child);

        /*
         * Retrieves a child repository given a name.
         *
         * @param repositoryName the name of an existing repository.
         * 
         * @throws std::runtime_error if repositoryName does not belong to a child of the repository.
         */
        Repository *findRepository(const std::string &repositoryName);

        /*
         * Enumerates all child repositories and packages.
         */
        const std::string list();

        /*
         * Creates an empty repository.
         * 
         * @param name the name of the new repository.
         */
        static Repository *empty(const std::string &name);

        /*
         * Creates a new repository from the specified folder.
         *
         * @param path the path of a folder.
         */
        static Repository *fromDirectory(const std::string &path);

        const std::string &getName() { return m_name; }

        const Repository *getParent() { return m_parent; }
    };
}

#endif //REPOSITORY_HEADER