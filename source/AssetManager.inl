#include <filesystem>

template<class Resource>
void AssetManager<Resource>::loadFromDirectory(const std::string& folder)
{
    std::list<std::filesystem::path> file_pathes;

    for (auto& file : std::filesystem::recursive_directory_iterator(folder))
    {
        Resource resource;

        if (resource.loadFromFile(file.path().string()))
            m_resources.emplace(file.path().stem(), resource);
    }
}

template<class Resource>
Resource* AssetManager<Resource>::get(const std::string& name)
{
    if (auto found = m_resources.find(name); found != m_resources.end())
        return &found->second;

    return nullptr;
}
