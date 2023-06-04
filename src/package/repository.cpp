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

#include "repository.h"
#include <iostream>

namespace primus
{
    Repository::Repository(const std::string &name, Repository *parent)
        : mName(name), mParent(parent)
    {
    }

    void Repository::addPackage(Package *package)
    {
        if (!package)
        {
            throw std::invalid_argument("Package cannot be null");
        }

        std::string packageId = package->getProperty<std::string>(PROPERTY__PACKAGE_ID);
        mPackages.insert(std::pair<std::string, Package *>(packageId, package));
    }

    void Repository::removePackage(const std::string &packageId)
    {
        if (mPackages.find(packageId) == mPackages.end())
        {
            std::string error = primus::format("Could not find package with id '{}'", packageId);
            throw std::runtime_error(error);
        }

        mPackages.erase(packageId);
    }

    Package *Repository::findPackage(const std::string &packageId)
    {
        if (mPackages.find(packageId) == mPackages.end())
        {
            std::string error = primus::format("Could not find package with id '{}'", packageId);
            throw std::runtime_error(error);
        }

        return mPackages[packageId];
    }

    void Repository::addRepository(Repository *child)
    {
        if (!child)
        {
            throw std::invalid_argument("Child Repository cannot be null");
        }

        child->mParent = this;
        mChildren.insert(std::pair<std::string, Repository *>(child->getName(), child));
    }

    Repository *Repository::findRepository(const std::string &repositoryName)
    {
        if (mChildren.find(repositoryName) == mChildren.end())
        {
            std::string error = primus::format("Could not find child repository with name '{}'", repositoryName);
            throw std::runtime_error(error);
        }

        return mChildren[repositoryName];
    }

    const std::string Repository::list()
    {
        int index = 1;
        std::string packageList = primus::format("repository '{}'{}", mName, LINE_BREAK);
        for (auto it = mPackages.begin(); it != mPackages.end(); ++it)
        {
            Package *package = it->second;
            packageList += primus::format("{}{}. package '{}'{}", 
                INDENT, 
                index++, 
                package->getProperty<std::string>(PROPERTY__PACKAGE_ID), 
                LINE_BREAK);
            packageList += package->list();
        }

        for (auto it : mChildren)
        {
            Repository *child = it.second;
            packageList += child->list();
        }

        return packageList;
    }

    Repository *Repository::empty(const std::string &name)
    {
        return new Repository(name);
    }

    Repository *Repository::fromDirectory(const std::string &path)
    {
        std::string repositoryName = std::filesystem::path(path).string();
        Repository *repository = new Repository(repositoryName);
        for (auto entry : std::filesystem::directory_iterator(path))
        {
            if (entry.is_directory())
            {
                std::string directory = entry.path().string();
                Repository *child = Repository::fromDirectory(directory);
                repository->addRepository(child);
            }
            else
            {
                std::string file = entry.path().string();
                Package *package = Package::fromFile(file);
                repository->addPackage(package);   
            }            
        }

        return repository;
    }
}