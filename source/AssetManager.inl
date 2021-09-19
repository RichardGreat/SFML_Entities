#include <filesystem>

template<class Resource>
void AssetManager<Resource>::loadFromDirectory(const std::string& folder)
{
    for (auto& file : std::filesystem::recursive_directory_iterator(folder))
    {
        Resource resource;

        if (file.path().has_extension())
                if (resource.loadFromFile(file.path().string()))
                    m_resources.emplace(file.path().stem().string(), resource);
    }
}

template<class Resource>
Resource* AssetManager<Resource>::get(const std::string& name) const
{
    if (auto found = m_resources.find(name); found != m_resources.end())
        return &found->second;

    return nullptr;
}
