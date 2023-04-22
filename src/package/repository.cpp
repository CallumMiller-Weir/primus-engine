#include "repository.h"

namespace primus
{
    Repository::Repository(const std::string &name)
        : m_name(name)
    {
    }

    void Repository::add(Package *package)
    {
        if (!package)
        {
            throw std::invalid_argument("Package cannot be null");
        }

        std::string packageName = package->getProperty<std::string>("package-id");
        m_packages.insert(std::pair<std::string, Package *>(packageName, package));
    }

    void Repository::remove(const std::string &packageName)
    {
        if (m_packages.find(packageName) == m_packages.end())
        {
            std::string error = primus::format("Could not find package with id '{}'", packageName);
            throw std::invalid_argument(error);
        }

        m_packages.erase(packageName);
    }

    std::string Repository::listPackages()
    {
        std::string packageList = primus::format("Repository '{}' contains {} packages: {}", m_name, m_packages.size(), LINE_BREAK);

        int index = 1;
        for (auto it : m_packages)
        {
            Package *package = it.second;

            std::string packageName = package->getProperty<std::string>("package-id");
            packageList += primus::format("{}{}. {}{}", INDENT, index++, packageName, LINE_BREAK);
            packageList += package->listProperties();
        }

        return packageList;
    }

    Repository *Repository::empty(const std::string &name)
    {
        return new Repository(name);
    }

    Repository *Repository::fromDirectory(const std::string &path)
    {
        std::string repositoryName = std::filesystem::path(path).parent_path().string();
        Repository *repository = new Repository(repositoryName);
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            std::string filePath = entry.path().string();
            Package *package = Package::fromFile(filePath);
            repository->add(package);            
        }

        return repository;
    }
}